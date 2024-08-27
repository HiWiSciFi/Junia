/*******************************************************************************
 *
 * @file      Monitor.cpp
 * @brief     Contains the Monitor class implementation
 * @author    Max Hager
 * @date      2024-07-17
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Rendering/Monitor.hpp>

#include <Junia/Core/Strings.hpp>
#include <Junia/Exceptions/ExWindows.hpp>

#include <iostream>
#include <sstream>

static constexpr const char* CURRENT_FILE_NAME = "Junia/src/Junia/Rendering/Monitor.cpp";

namespace Junia {

std::vector<Monitor> Monitor::monitors = std::vector<Monitor>();

struct Monitor::Impl {
	HMONITOR monitor = nullptr;
};

void Monitor::Init() {
	UINT32 pathCount, modeCount;

	if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount) != ERROR_SUCCESS)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
	std::vector<DISPLAYCONFIG_PATH_INFO> paths(pathCount);
	std::vector<DISPLAYCONFIG_MODE_INFO> modes(modeCount);
	if (QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount, paths.data(), &modeCount, modes.data(), nullptr) != ERROR_SUCCESS)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));

	for (UINT32 i = 0; i < paths.size(); i++) {
		const DISPLAYCONFIG_PATH_INFO& path = paths[i];

		DISPLAYCONFIG_TARGET_DEVICE_NAME targetDevice {
			.header = {
				.type      = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME,
				.size      = sizeof(targetDevice),
				.adapterId = path.targetInfo.adapterId,
				.id        = path.targetInfo.id }
		};

		if (DisplayConfigGetDeviceInfo(&targetDevice.header) != ERROR_SUCCESS)
			continue;

		DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceDevice {
			.header = {
				.type      = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME,
				.size      = sizeof(sourceDevice),
				.adapterId = path.targetInfo.adapterId,
				.id        = path.sourceInfo.id }
		};

		if (DisplayConfigGetDeviceInfo(&sourceDevice.header) != ERROR_SUCCESS)
			continue;

		struct MonitorDataStruct {
			const WCHAR* inSourceName;
			const WCHAR* inPath;

			bool queryFallbackName;

			std::uint32_t outIndex;
			utf8_string   outFallbackName;
			HMONITOR      outMonitor;
			RECT          outMonitorDim;
			RECT          outMonitorWorkDim;
		};

		bool requireFallbackName = targetDevice.monitorFriendlyDeviceName[0] == L'\x0000';

		MonitorDataStruct query = {
			.inSourceName      = sourceDevice.viewGdiDeviceName,
			.inPath            = targetDevice.monitorDevicePath,
			.queryFallbackName = requireFallbackName
		};

		// Iterate monitors
		if (EnumDisplayMonitors(NULL, NULL, [](HMONITOR monitor, HDC, LPRECT rect, LPARAM data) -> BOOL {
			MonitorDataStruct& query = *reinterpret_cast<MonitorDataStruct*>(data);

			MONITORINFOEX info { };
			info.cbSize = sizeof(info);
			if (GetMonitorInfoW(monitor, &info) == 0)
				throw Exception(u8"Failed to get monitor information", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));

			// continue to next item in the enumeration if the device does not match the queried device
			if (memcmp(info.szDevice, query.inSourceName, CCHDEVICENAME * sizeof(WCHAR)) != 0) return TRUE;

			query.outMonitor = monitor;
			query.outMonitorDim = info.rcMonitor;
			query.outMonitorWorkDim = info.rcWork;

			// Iterate display devices
			DISPLAY_DEVICEW sourceDevice { .cb = sizeof(sourceDevice) };
			for (DWORD monitorId = 0; EnumDisplayDevicesW(NULL, monitorId, &sourceDevice, 0); monitorId++) {

				// Get device; skip to next if none was found or device is not active
				DISPLAY_DEVICEW targetDevice { .cb = sizeof(targetDevice) };
				if (EnumDisplayDevicesW(sourceDevice.DeviceName, 0, &targetDevice, EDD_GET_DEVICE_INTERFACE_NAME) == 0
					|| !(targetDevice.StateFlags & DISPLAY_DEVICE_ACTIVE)) continue;

				// skip to next if the device does not match the queried device
				if (memcmp(query.inPath, targetDevice.DeviceID, sizeof(DISPLAY_DEVICEW::DeviceID) / sizeof(WCHAR)) != 0) continue;

				if (query.queryFallbackName)
					query.outFallbackName = StringConvert::U16ToU8(targetDevice.DeviceString);
				query.outIndex = monitorId + 1;
				return FALSE;
			}

			return TRUE; }, reinterpret_cast<LPARAM>(&query)) != 0) continue; // continue if no match was found

		auto impl     = std::make_shared<Impl>();
		impl->monitor = query.outMonitor;
		monitors.push_back(
			Monitor(
				query.outIndex,
				requireFallbackName ? query.outFallbackName : StringConvert::U16ToU8(targetDevice.monitorFriendlyDeviceName),
				impl));
	}
}

const std::vector<Monitor>& Monitor::GetMonitors() {
	return monitors;
}

Monitor::Monitor(std::uint32_t index, const utf8_string& name, std::shared_ptr<Impl> impl)
	: index(index), name(name), impl(impl) { }

Monitor::~Monitor() = default;

const utf8_string& Monitor::GetName() const {
	return this->name;
}

std::uint32_t Monitor::GetIndex() const {
	return this->index;
}

HMONITOR Monitor::GetWin32Monitor() {
	return this->impl->monitor;
}

} // namespace Junia

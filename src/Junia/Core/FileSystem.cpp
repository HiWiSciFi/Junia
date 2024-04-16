/*******************************************************************************
 *
 * @file      FileSystem.cpp
 * @brief     Contains the FileSystem abstraction implementation
 * @author    Max Hager
 * @date      28.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/FileSystem.hpp>

#include <Junia/Core/Exceptions/ExExepath.hpp>
#include <Junia/Core/Exceptions/ExWin32.hpp>
#include <Junia/Core/StringConvert.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef ERROR
#undef IGNORE

#include <filesystem>
#include <iostream>

static constexpr const char* CURRENT_FILE_NAME = "Junia/src/Junia/Core/FileSystem.cpp";

namespace Junia {

utf8_string FileSystem::executablePath;

void FileSystem::Init() {
	WCHAR shortPath[MAX_PATH];
	WCHAR longPath[MAX_PATH];

	SetLastError(ERROR_SUCCESS);
	if (GetModuleFileNameW(NULL, shortPath, MAX_PATH) == 0 || GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		throw ExExepath(u8"", Exception::GetAsPtr<ExWin32>(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__)), CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
		return;
	}

	GetLongPathNameW(shortPath, longPath, MAX_PATH);
	std::filesystem::path path = std::filesystem::path(longPath);
	path.remove_filename();

	executablePath = path.generic_u8string();
}

} // namespace Junia

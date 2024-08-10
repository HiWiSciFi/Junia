/*******************************************************************************
 *
 * @file      Monitor.hpp
 * @brief     Contains the Monitor class definition
 * @author    Max Hager
 * @date      2024-07-17
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_RENDERING_MONITOR
#define __HEADER_JUNIA_RENDERING_MONITOR

#include "../Core/Core.hpp"
#include "../Core/Strings.hpp"
#include "../Platform.hpp"

#include <memory>
#include <vector>

namespace Junia {

class JUNIA_SYMBOL Monitor {
public:
	static void                        Init();
	static const std::vector<Monitor>& GetMonitors();

	~Monitor();

	const utf8_string& GetName() const;
	std::uint32_t      GetIndex() const;

#ifdef JUNIA_EXPOSE_NATIVE_WIN32
	HMONITOR GetWin32Monitor();
#endif

private:
	static std::vector<Monitor> monitors;

	struct Impl;
	std::shared_ptr<Impl> impl;

	std::uint32_t index;
	utf8_string   name;

	Monitor(std::uint32_t index, const utf8_string& name, std::shared_ptr<Impl> impl);
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_RENDERING_MONITOR)

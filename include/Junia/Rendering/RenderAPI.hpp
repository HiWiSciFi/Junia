/*******************************************************************************
 *
 * @file      RenderAPI.hpp
 * @brief     Contains the RenderAPI enum class definition
 * @author    Max Hager
 * @date      2024-07-11
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_RENDERING_RENDERAPI
#define __HEADER_JUNIA_RENDERING_RENDERAPI

#include "../Core/Core.hpp"

#include <cstdint>

namespace Junia {

enum class JUNIA_SYMBOL RenderAPI : std::uint8_t {
	NONE   = 0,
	OPENGL = 1,
	VULKAN = 2
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_RENDERING_RENDERAPI)

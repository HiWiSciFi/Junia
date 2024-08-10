/*******************************************************************************
 *
 * @file      Vulkan.hpp
 * @brief     Contains the definition for the Junia Vulkan subsystem
 * @author    Max Hager
 * @date      06.07.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/Strings.hpp>
#include <Junia/Core/Version.hpp>

namespace Junia::Vulkan {

class Vulkan {
public:
	static void Init(const utf8_string& applicationName, Version applicationVersion);
};

} // namespace Junia::Vulkan

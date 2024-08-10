/*******************************************************************************
 *
 * @file      Vulkan.cpp
 * @brief     Contains the implementation for the Junia Vulkan subsystem
 * @author    Max Hager
 * @date      06.07.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include "Vulkan.hpp"

#include "../Core/Globals.hpp"

#include <vulkan/vulkan.hpp>

namespace Junia::Vulkan {

void Vulkan::Init(const utf8_string& applicationName, Version applicationVersion) {
	VkApplicationInfo applicationInfo = {
		.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext              = NULL,
		.pApplicationName   = reinterpret_cast<const char*>(applicationName.c_str()),
		.applicationVersion = applicationVersion.GetVersionNumber(),
		.pEngineName        = reinterpret_cast<const char*>(Globals::ENGINE_NAME.c_str()),
		.engineVersion      = Globals::ENGINE_VERSION.GetVersionNumber(),
		.apiVersion         = VK_API_VERSION_1_3
	};

	VkInstanceCreateInfo instanceCreateInfo = {
		.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &applicationInfo
	};

	VkInstance instance;
	vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
}

} // namespace Junia::Vulkan

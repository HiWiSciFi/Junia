/*******************************************************************************
 *
 * @file      Globals.hpp
 * @brief     Contains global constants and configuration values for Junia
 * @author    Max Hager
 * @date      2024-07-10
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/Version.hpp>

namespace Junia {

struct Globals final {
	static Version     ENGINE_VERSION;
	static utf8_string ENGINE_NAME;
};

} // namespace Junia

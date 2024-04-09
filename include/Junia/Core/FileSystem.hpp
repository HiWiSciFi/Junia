/*******************************************************************************
 *
 * @file      FileSystem.hpp
 * @brief     Contains the FileSystem abstraction definition
 * @author    Max Hager
 * @date      28.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_CORE_FILESYSTEM
#define __HEADER_JUNIA_CORE_FILESYSTEM

#include "Core.hpp"
#include "Strings.hpp"

namespace Junia {

class JUNIA_SYMBOL FileSystem final {
public:
	static void Init();

private:
	static utf8_string executablePath;

	FileSystem()                  = delete;
	FileSystem(const FileSystem&) = delete;
	~FileSystem()                 = delete;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_FILESYSTEM)

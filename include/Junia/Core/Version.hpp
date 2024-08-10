/*******************************************************************************
 *
 * @file      Version.hpp
 * @brief     Contains the Version class definition
 * @author    Max Hager
 * @date      2024-07-09
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_CORE_VERSION
#define __HEADER_JUNIA_CORE_VERSION

#include "Core.hpp"
#include "Strings.hpp"

#include <cstdint>

namespace Junia {

class JUNIA_SYMBOL Version {
public:
	/**
	 * @brief Create a version struct
	 * @param major The major version number (7 bit)
	 * @param minor The minor version number (10 bit)
	 * @param patch The patch version number (12 bit)
	 */
	explicit Version(std::uint8_t major, std::uint16_t minor, std::uint16_t patch);

	/**
	 * @brief Get the version number
	 * @return 32-Bit Version number according to Vulkan 1.3 Spec 43.2.1
	 *         (variant as 0)
	 */
	[[nodiscard]] std::uint32_t GetVersionNumber() const;

	/**
	 * @brief Get the major version number
	 * @return 8-Bit major version number
	 */
	[[nodiscard]] std::uint8_t GetMajor() const;

	/**
	 * @brief Get the minor version number
	 * @return 16-Bit minor version number
	 */
	[[nodiscard]] std::uint16_t GetMinor() const;

	/**
	 * @brief Get the patch version number
	 * @return 16-Bit patch version number
	 */
	[[nodiscard]] std::uint16_t GetPatch() const;

	/**
	 * @brief Alias for Version::GetPatch
	 * @return 16-Bit patch version number
	 */
	[[nodiscard]] std::uint16_t GetRevision() const;

	/**
	 * @brief Get the version as a string
	 * @return A string formatted as <major>.<minor>.<patch>
	 */
	[[nodiscard]] utf8_string GetVersionString() const;

private:
	/**
	 * @brief Version number according to Vulkan 1.3 Spec 43.2.1 (excluding
	 *        variant)
	 */
	std::uint32_t version;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_VERSION)

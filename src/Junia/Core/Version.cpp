/*******************************************************************************
 *
 * @file      Version.cpp
 * @brief     Contains the Version class implementation
 * @author    Max Hager
 * @date      2024-07-09
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/Version.hpp>

#include <sstream>

namespace Junia {

constexpr std::uint32_t MAJOR_OFFSET = 22;
constexpr std::uint32_t MINOR_OFFSET = 12;

constexpr std::uint32_t MAJOR_MASK = 0x7FU;
constexpr std::uint32_t MINOR_MASK = 0x3FFU;
constexpr std::uint32_t PATCH_MASK = 0xFFFU;

Version::Version(std::uint8_t major, std::uint16_t minor, std::uint16_t patch)
	: version(static_cast<std::uint32_t>(0) | (static_cast<std::uint32_t>(major) << MAJOR_OFFSET) | (static_cast<std::uint32_t>(minor) << MINOR_OFFSET) | static_cast<std::uint32_t>(patch)) { }

std::uint32_t Version::GetVersionNumber() const {
	return this->version;
}

std::uint8_t Version::GetMajor() const {
	return static_cast<std::uint8_t>((this->version >> MAJOR_OFFSET) & MAJOR_MASK);
}

std::uint16_t Version::GetMinor() const {
	return static_cast<std::uint16_t>((this->version >> MINOR_OFFSET) & MINOR_MASK);
}

std::uint16_t Version::GetPatch() const {
	return static_cast<std::uint16_t>(this->version & PATCH_MASK);
}

std::uint16_t Version::GetRevision() const {
	return this->GetPatch();
}

utf8_string Version::GetVersionString() const {
	std::stringstream stream;
	stream << static_cast<std::uint16_t>(this->GetMajor()) << '.' << this->GetMinor() << '.' << this->GetPatch();
	std::string str = stream.str();
	return utf8_string(str.begin(), str.end());
}

} // namespace Junia

/*******************************************************************************
 *
 * @file      Strings.hpp
 * @brief     Contains the specification for UTF8-String printing
 * @author    Max Hager
 * @date      22.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/
#ifndef __HEADER_JUNIA_CORE_STRINGS
#define __HEADER_JUNIA_CORE_STRINGS

#include "Core.hpp"

#include <ostream>
#include <string>

namespace Junia {

using utf8_string = std::u8string;

#ifdef _WIN32
using utf16_string = std::wstring;
#else
using utf16_string = std::u16string;
#endif

using utf32_string = std::u32string;

} // namespace Junia

namespace std {

JUNIA_SYMBOL ostream& operator<<(ostream& os, const Junia::utf8_string& val);
JUNIA_SYMBOL ostream& operator<<(ostream& os, const Junia::utf8_string::value_type* val);

} // namespace std

#endif // !defined(__HEADER_JUNIA_CORE_STRINGS)

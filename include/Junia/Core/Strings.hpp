/*******************************************************************************
 *
 * @file      Strings.hpp
 * @brief     Contains the class definition for Junia String classes
 * @author    Max Hager
 * @date      22.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/
#ifndef __HEADER_JUNIA_CORE_STRINGS
#define __HEADER_JUNIA_CORE_STRINGS

#include <sstream>
#include <string>

namespace Junia {

using ucodepoint_t = char32_t;

using utf8_string        = std::string;
using utf8_stringstream  = std::stringstream;
using u_string           = std::basic_string<ucodepoint_t, std::char_traits<ucodepoint_t>, std::allocator<ucodepoint_t>>;
using u_stringstream     = std::basic_stringstream<ucodepoint_t, std::char_traits<ucodepoint_t>, std::allocator<ucodepoint_t>>;
using utf16_string       = std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;
using utf16_stringstream = std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_STRINGS)

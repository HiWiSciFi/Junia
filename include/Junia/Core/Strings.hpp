/*******************************************************************************
 *
 * @file      Strings.hpp
 * @brief     Contains the specification for UTF8-String string handling
 * @author    Max Hager
 * @date      2024-03-22
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/
#ifndef __HEADER_JUNIA_CORE_STRINGS
#define __HEADER_JUNIA_CORE_STRINGS

#include "Core.hpp"

#include <ostream>
#include <string>

namespace Junia {

/// @brief A UTF8-String
using utf8_string = std::u8string;

#ifdef _WIN32
/// @brief A UTF16-String
using utf16_string = std::wstring;
#else
/// @brief A UTF16-String
using utf16_string = std::u16string;
#endif

/// @brief A Unicode codepoint string
using utf32_string = std::u32string;

class JUNIA_SYMBOL StringUtil final {
public:
	[[nodiscard]] static std::size_t GetCodepointCount(const utf8_string& str);
	[[nodiscard]] static std::size_t GetCodepointCount(const utf16_string& str);
	[[nodiscard]] static std::size_t GetCodepointCount(const utf32_string& str);

private:
	StringUtil()  = delete;
	~StringUtil() = delete;
};

} // namespace Junia

namespace std {

JUNIA_SYMBOL ostream& operator<<(ostream& os, const Junia::utf8_string& val);
JUNIA_SYMBOL ostream& operator<<(ostream& os, const Junia::utf8_string::value_type* val);

} // namespace std

namespace Junia {

/**
 *
 * @class StringConvert
 * @brief static class to convert strings between encodings
 *
 */
class JUNIA_SYMBOL StringConvert final {
public:
	/**
	 * @brief        convert a UTF-8 encoded string to a UTF-16 encoded string
	 * @param   utf8 the UTF-8 string to convert
	 * @returns      a UTF-16 encoded string
	 *
	 * @throws ExUtf8StringEncoding    if the UTF-8 string was invalid
	 * @throws ExUtf32StringEncoding   if the generated Unicode codepoint string
	 *                                 was invalid
	 */
	[[nodiscard]] static utf16_string U8ToU16(const utf8_string& utf8);

	/**
	 * @brief        decode a UTF-8 string to a string of unicode codepoints
	 * @param   utf8 the UTF-8 string to decode
	 * @returns      a string of unicode codepoints
	 *
	 * @throws ExUtf8StringEncoding if the UTF-8 string was invalid
	 */
	[[nodiscard]] static utf32_string U8ToU32(const utf8_string& utf8);

	/**
	 * @brief         convert a UTF-16 encoded string to a UTF-8 encoded string
	 * @param   utf16 the UTF-16 string to convert
	 * @returns       a UTF-8 encoded string
	 *
	 * @throws ExUtf16StringEncoding   if the UTF-16 string was invalid
	 * @throws ExUtf32StringEncoding   if the gererated Unicode codepoint string
	 *                                 was invalid
	 */
	[[nodiscard]] static utf8_string U16ToU8(const utf16_string& utf16);

	/**
	 * @brief         decode a UTF-16 string to a string of unicode codepoints
	 * @param   utf16 the UTF-16 string to decode
	 * @returns       a string of unicode codepoints
	 *
	 * @throws ExUtf16StringEncoding if the UTF-16 string was invalid
	 */
	[[nodiscard]] static utf32_string U16ToU32(const utf16_string& utf16);

	/**
	 * @brief           encode a string of unicode codepoints in UTF-8
	 * @param   unicode the string of unicode codepoints to encode
	 * @returns         a UTF-8 encoded string
	 *
	 * @throws ExUtf32StringEncoding if a unicode codepoint was invalid
	 */
	[[nodiscard]] static utf8_string U32ToU8(const utf32_string& unicode);

	/**
	 * @brief           encode a string of unicode codepoints in UTF-16
	 * @param   unicode the string of unicode codepoints to encode
	 * @returns         a UTF-16 encoded string
	 *
	 * @throws ExUtf32StringEncoding if a unicode codepoint was invalid
	 */
	[[nodiscard]] static utf16_string U32ToU16(const utf32_string& unicode);

private:
	StringConvert()                     = delete;
	StringConvert(const StringConvert&) = delete;
	~StringConvert()                    = delete;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_STRINGS)

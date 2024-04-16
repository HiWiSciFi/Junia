/*******************************************************************************
 *
 * @file      StringConvert.hpp
 * @brief     Contains the class definition for the string conversion class
 * @author    Max Hager
 * @date      22.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_CORE_STRINGCONVERT
#define __HEADER_JUNIA_CORE_STRINGCONVERT

#include "Core.hpp"

#include "Exceptions/ExUtf16StringEncoding.hpp"
#include "Exceptions/ExUtf32StringEncoding.hpp"
#include "Exceptions/ExUtf8StringEncoding.hpp"
#include "Strings.hpp"

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

#endif // !defined(__HEADER_JUNIA_CORE_STRINGCONVERT)

/*******************************************************************************
 *
 * @file      Strings.cpp
 * @brief     Contains the specification for UTF8-String string handling
 * @author    Max Hager
 * @date      2024-04-09
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/Strings.hpp>

#include <Junia/Core/Exception.hpp>

static constexpr const char* CURRENT_FILE_NAME = "Junia/src/Junia/Core/Strings.cpp";

namespace Junia {

std::size_t StringUtil::GetCodepointCount(const utf8_string& str) {
	std::size_t                    length  = 0;
	std::size_t                    cLength = str.size();
	const utf8_string::value_type* cstr    = str.c_str();
	std::size_t                    i       = 0;

	while (i < cLength) {
		if ((cstr[i] & 0b1000'0000u) == 0b0000'0000u)
			i++;
		else if (
			(cstr[i] & 0b1110'0000u) == 0b1100'0000u)
			i += 2;
		else if ((cstr[i] & 0b1111'0000u) == 0b1110'0000u)
			i += 3;
		else if ((cstr[i] & 0b1111'1000u) == 0b1111'0000u)
			i += 4;
		else
			throw Exception(u8"Invalid UTF8 string", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
		length++;
	}

	if (i > cLength) throw Exception(u8"Invalid UTF8 string", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));

	return length;
}

std::size_t StringUtil::GetCodepointCount(const utf16_string& str) {
	std::size_t                     length  = 0;
	std::size_t                     cLength = str.size();
	const utf16_string::value_type* cstr    = str.c_str();
	std::size_t                     i       = 0;

	while (i < cLength) {
		if (cstr[i] >= u'\xD800' && cstr[i] <= u'\xDFFF')
			i += 2;
		else
			i++;
		length++;
	}

	if (i > cLength) throw Exception(u8"Invalid UTF16 string", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));

	return length;
}

std::size_t StringUtil::GetCodepointCount(const utf32_string& str) {
	return str.size();
}

} // namespace Junia

#include <Junia/Core/Exceptions/ExUtf16StringEncoding.hpp>
#include <Junia/Core/Exceptions/ExUtf32StringEncoding.hpp>
#include <Junia/Core/Exceptions/ExUtf8StringEncoding.hpp>

namespace std {

JUNIA_SYMBOL ostream& operator<<(ostream& os, const Junia::utf8_string& val) {
	if constexpr (sizeof(char) == sizeof(Junia::utf8_string::value_type)) {
		os.write(reinterpret_cast<const char*>(val.data()), val.size());
	} else {
		for (std::size_t i = 0; i < val.size(); i++)
			os.put(static_cast<char>(val[i]));
	}
	return os;
}

JUNIA_SYMBOL ostream& operator<<(ostream& os, const Junia::utf8_string::value_type* val) {
	os.write(reinterpret_cast<const char*>(val), strlen(reinterpret_cast<const char*>(val)));
	return os;
}

} // namespace std

namespace Junia {

utf16_string StringConvert::U8ToU16(const utf8_string& utf8) {
	// may throw ExUtf8StringEncoding or ExUtf32StringEncoding
	return U32ToU16(U8ToU32(utf8));
}

utf32_string StringConvert::U8ToU32(const utf8_string& utf8) {
	utf32_string unicode;

	for (std::size_t i = 0; i < utf8.size(); i++) {
		utf8_string::value_type c = utf8[i];

		if (c >= 0x00 && c <= 0x7F) {
			unicode += c & 0x7F;
		} else if (c >= 0xC0 && c <= 0xDF) {
			if (i + 1 >= utf8.size()) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Not enough characters.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i);
			utf32_string::value_type point = c & 0x1F;
			c                              = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			unicode += point;
		} else if (c >= 0xE0 && c <= 0xEF) {
			if (i + 2 >= utf8.size()) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Not enough characters.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i);
			utf32_string::value_type point = c & 0x0F;
			c                              = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			c     = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			unicode += point;
		} else if (c >= 0xF0 && c <= 0xF7) {
			if (i + 3 >= utf8.size()) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Not enough characters.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i);
			utf32_string::value_type point = c & 0x07;
			c                              = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			c     = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			c     = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			unicode += point;
		} else {
			throw ExUtf8StringEncoding(u8"Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i);
		}
	}

	return unicode;
}

utf8_string StringConvert::U16ToU8(const utf16_string& utf16) {
	// may throw ExUtf16StringEncoding or ExUtf32StringEncoding
	return U32ToU8(U16ToU32(utf16));
}

utf32_string StringConvert::U16ToU32(const utf16_string& utf16) {
	utf32_string unicode;

	for (std::size_t i = 0; i < utf16.size(); i++) {
		utf16_string::value_type c = utf16[i];

		if (c >= 0xD800 && c <= 0xDBFF) {
			if (utf16.size() <= i + 1) throw ExUtf16StringEncoding(u8"Invalid UTF-16 string. Not enough characters.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf16, i);
			utf32_string::value_type point = (c - 0xD800) << 10;

			c = utf16[++i];
			if (c < 0xDC00 || c > 0xDFFF) throw ExUtf16StringEncoding(u8"Invalid UTF-16 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf16, i - 1);
			point += c - 0xDC00;

			point += 0x10000;
			unicode += point;
		} else {
			unicode += c;
		}
	}

	return unicode;
}

utf8_string StringConvert::U32ToU8(const utf32_string& unicode) {
	utf8_string utf8;

	for (std::size_t i = 0; i < unicode.size(); i++) {
		utf32_string::value_type point = unicode[i];

		if (point >= 0 && point <= 0x007F) {
			utf8 += static_cast<utf8_string::value_type>(point & 0xFF);
		} else if (point >= 0x80 && point <= 0x07FF) {
			utf8 += static_cast<utf8_string::value_type>(0xC0 | (point >> 6));
			utf8 += static_cast<utf8_string::value_type>(0x80 | (point & 0x3F));
		} else if (point >= 0x800 && point <= 0xFFFF) {
			utf8 += static_cast<utf8_string::value_type>(0xE0 | (point >> 12));
			utf8 += static_cast<utf8_string::value_type>(0x80 | ((point >> 6) & 0x3F));
			utf8 += static_cast<utf8_string::value_type>(0x80 | (point & 0x3F));
		} else if (point >= 0x10000 && point <= 0x10FFFF) {
			utf8 += static_cast<utf8_string::value_type>(0xF0 | (point >> 18));
			utf8 += static_cast<utf8_string::value_type>(0x80 | ((point >> 12) & 0x3F));
			utf8 += static_cast<utf8_string::value_type>(0x80 | ((point >> 6) & 0x3F));
			utf8 += static_cast<utf8_string::value_type>(0x80 | (point & 0x3F));
		} else
			throw ExUtf32StringEncoding(u8"Invalid Unicode codepoint encountered", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), unicode, i);
	}

	return utf8;
}

utf16_string StringConvert::U32ToU16(const utf32_string& unicode) {
	utf16_string utf16;

	for (std::size_t i = 0; i < unicode.size(); i++) {
		utf32_string::value_type point = unicode[i];

		if (point < 0xD800 || (point > 0xDFFF && point < 0x10000)) {
			utf16 += static_cast<utf16_string::value_type>(point & 0xFFFF);
		} else {
			point -= 0x10000;
			utf16 += (point >> 10) + 0xD800;
			utf16 += (point & 0x3FF) + 0xDC00;
		}
	}

	return utf16;
}

} // namespace Junia

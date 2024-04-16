/*******************************************************************************
 *
 * @file      ExWin32.cpp
 * @brief     Contains the ExWin32 exception class implementation
 * @author    Max Hager
 * @date      13.04.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/Exceptions/ExWin32.hpp>

#include <Junia/Core/StringConvert.hpp>

#define _WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef _WIN32_LEAN_AND_MEAN

namespace Junia {

ExWin32::ExWin32(unsigned long code, std::exception_ptr previous, CodePos location) noexcept
	: code(code), Exception(u8"", previous, location) {
	LPWSTR buf;
	DWORD  strLen = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        code,
        LANG_USER_DEFAULT,
        reinterpret_cast<LPWSTR>(&buf),
        1024,
        NULL);

	if (strLen == 0) {
		std::string codeStr = std::to_string(code);
		Exception::message  = u8"Win32 Error Code "; // short string
		// should stay a short string because error codes only go up to 15999
		for (std::size_t i = 0; i < codeStr.size(); i++) Exception::message += codeStr[i];
		return;
	}

	Exception::message = StringConvert::U16ToU8(buf);
	LocalFree(buf);
}

} // namespace Junia

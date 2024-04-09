/*******************************************************************************
 *
 * @file      FileSystem.cpp
 * @brief     Contains the FileSystem abstraction implementation
 * @author    Max Hager
 * @date      28.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/FileSystem.hpp>

#include <Junia/Core/StringConvert.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef ERROR
#undef IGNORE

#include <iostream>

namespace Junia {

utf8_string FileSystem::executablePath;

void FileSystem::Init() {
	WCHAR shortPath[MAX_PATH];
	WCHAR longPath[MAX_PATH];

	if (GetModuleFileNameW(NULL, shortPath, MAX_PATH) == 0 || GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		return;
	}

	GetLongPathNameW(shortPath, longPath, MAX_PATH);

	executablePath = StringConvert::UTF16ToUTF8(utf16_string(longPath));
}

} // namespace Junia

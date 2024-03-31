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
	// executablePath = ;
	WCHAR filename[MAX_PATH];
	GetModuleFileNameW(NULL, filename, MAX_PATH);

	executablePath = StringConvert::UTF16ToUTF8(utf16_string(filename));
}

} // namespace Junia

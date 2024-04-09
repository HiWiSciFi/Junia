/*******************************************************************************
 *
 * @file      Junia.cpp
 * @brief     Contains the implementation for the Junia initialization and
 *            termination functions
 * @author    Max Hager
 * @date      17.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Junia.hpp>

#include <Junia/Core/FileSystem.hpp>

#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN

namespace Junia {

void Init() {
	SetConsoleOutputCP(CP_UTF8);
	FileSystem::Init();
	std::cout << u8"Hello World!" << std::endl;
}

void Terminate() {
	std::cout << u8"Bye World!" << std::endl;
}

} // namespace Junia

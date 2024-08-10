/*******************************************************************************
 *
 * @file      Platform.hpp
 * @brief     Contains the Platform native function imports
 * @author    Max Hager
 * @date      2024-08-03
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_PLATFORM
#define __HEADER_JUNIA_PLATFORM

#ifdef _WIN32

#define JUNIA_PLATFORM_WIN32

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef GetMessage

#else

#error Junia only supports windows at this time

#endif // defined(_WIN32)

#ifdef BUILD_JUNIA
#define JUNIA_EXPOSE_NATIVE
#endif // defined(BUILD_JUNIA)

#ifdef JUNIA_EXPOSE_NATIVE
#ifdef JUNIA_PLATFORM_WIN32
#define JUNIA_EXPOSE_NATIVE_WIN32
#endif // defined(JUNIA_PLATFORM_WIN32)
#endif // defined(JUNIA_EXPOSE_NATIVE)

#endif // !defined(__HEADER_JUNIA_PLATFORM)

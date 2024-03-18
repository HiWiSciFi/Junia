/*******************************************************************************
 *
 * @file      Core.hpp
 * @brief     A collection of preprocessor macros and other definitions that are
 *            used across the whole codebase
 * @author    Max Hager
 * @date      17.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_CORE_CORE
#define __HEADER_JUNIA_CORE_CORE

namespace Junia {

#ifdef BUILD_JUNIA

/**
 * @def   JUNIA_SYMBOL
 * @brief Declare a symbol to be exported from the dll
 */
#define JUNIA_SYMBOL __declspec(dllexport)

#else

/**
 * @def   JUNIA_SYMBOL
 * @brief Declare a symbol to be imported from the dll
 */
#define JUNIA_SYMBOL __declspec(dllimport)

#endif

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_CORE)

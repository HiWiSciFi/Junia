/*******************************************************************************
 *
 * @file      Junia.hpp
 * @brief     Contains the function definition for Junia initialization and
 *            termination functions
 * @author    Max Hager
 * @date      17.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_JUNIA
#define __HEADER_JUNIA_JUNIA

#include "Core/Core.hpp"

namespace Junia {

/**
 * @brief Initialize the Junia Engine
 */
void JUNIA_SYMBOL Init();

/**
 * @brief Terminate the Junia Enine
 */
void JUNIA_SYMBOL Terminate();

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_JUNIA)

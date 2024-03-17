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

#include <iostream>

namespace Junia {

void Init() {
	std::cout << "Hello World!" << std::endl;
}

void Terminate() {
	std::cout << "Bye World!" << std::endl;
}

} // namespace Junia

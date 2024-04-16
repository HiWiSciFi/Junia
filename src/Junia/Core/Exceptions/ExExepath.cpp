/*******************************************************************************
 *
 * @file      ExExepath.cpp
 * @brief     Contains the ExExepath exception class implementation
 * @author    Max Hager
 * @date      16.04.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/Exceptions/ExExepath.hpp>

namespace Junia {

ExExepath::ExExepath(const utf8_string& msg, std::exception_ptr previous, CodePos location)
	: Exception(msg, previous, location) { }

} // namespace Junia

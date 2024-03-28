/*******************************************************************************
 *
 * @file      ExStringEncoding.cpp
 * @brief     Contains the ExStringEncoding exception class implementation
 * @author    Max Hager
 * @date      27.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Exceptions/ExStringEncoding.hpp>

namespace Junia {

ExStringEncoding::ExStringEncoding(const utf8_string& msg, std::exception_ptr previous, CodePos location)
	: Exception(msg, previous, location) { }

} // namespace Junia

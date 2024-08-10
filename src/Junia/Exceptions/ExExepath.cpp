/*******************************************************************************
 *
 * @file      ExExepath.cpp
 * @brief     Contains the ExExepath class implementation
 * @author    Max Hager
 * @date      2024-07-10
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Exceptions/ExExepath.hpp>

namespace Junia {

ExExepath::ExExepath(const utf8_string& msg, std::exception_ptr previous, CodePos location)
	: Exception(msg, previous, location) { }

} // namespace Junia

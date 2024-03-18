/*******************************************************************************
 *
 * @file      Exception.cpp
 * @brief     Contains the implementation of the base exception class
 * @author    Max Hager
 * @date      18.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/Exception.hpp>

namespace Junia {

CodePos::CodePos() : file(""), line(-1) { }

CodePos::CodePos(const char* file, int line) : file(file), line(line) { }

bool CodePos::IsProvided() const { return line >= 0; }

CodePos CodePos::NotProvided() { return CodePos(); }

Exception::Exception(const char* msg, CodePos location) : location(location), std::runtime_error(msg) { }

} // namespace Junia

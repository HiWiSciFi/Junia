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

CodePos::CodePos() noexcept : file(""), function(""), line(-1) { }

CodePos::CodePos(const char* file, const char* function, int line) noexcept
	: file(file), function(function), line(line) { }

bool CodePos::IsProvided() const noexcept { return line >= 0; }

CodePos CodePos::NotProvided() noexcept { return CodePos(); }

Exception::Exception(const utf8_string& msg, std::exception_ptr previous, CodePos location) noexcept
	: message(msg), previous(previous), location(location), std::runtime_error(nullptr) { }

const char* Exception::what() const {
	return this->GetMessage().c_str();
}

bool Exception::CodePosProvided() const noexcept {
	return this->location.IsProvided();
}

const utf8_string& Exception::GetMessage() const noexcept {
	return this->message;
}

const CodePos& Exception::Where() const noexcept {
	return this->location;
}

std::exception_ptr Exception::GetPrevious() const noexcept {
	return this->previous;
}

utf8_string Exception::GetText(bool recursive) const {
	if (!recursive || this->previous == nullptr) return this->GetMessage();

	utf8_string message;
	try {
		std::rethrow_exception(this->previous);
	} catch (const Exception& ex) {
		message += ex.GetText(true);
	} catch (const std::exception& ex) {
		message += ex.what();
	}
	message += '\n';
	message += this->GetMessage();

	return message;
}

} // namespace Junia

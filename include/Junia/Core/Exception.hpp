/*******************************************************************************
 *
 * @file      Exception.hpp
 * @brief     Contains the definition of the Base exception class
 * @author    Max Hager
 * @date      18.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_CORE_EXCEPTION
#define __HEADER_JUNIA_CORE_EXCEPTION

#include "Core.hpp"

#include "Strings.hpp"

#include <stdexcept>

namespace Junia {

/**
 * @struct CodePos
 * @brief  a structure to hold information about a position in code
 */
struct JUNIA_SYMBOL CodePos {
	const char* file;
	const char* function;
	int         line;

	/**
	 * @brief CodePos object constructor (=NotProvided)
	 */
	CodePos() noexcept;

	/**
	 * @brief          CodePos object constructor
	 * @param file     the file (__FILE__)
	 * @param function the function (__FUNCTION__)
	 * @param line     the line number (__LINE__). This must be positive
	 */
	CodePos(const char* file, const char* function, int line) noexcept;

	/**
	 * @brief   check if the Code position was provided
	 * @returns true if the Code position is provided, false otherwise
	 */
	[[nodiscard]] bool IsProvided() const noexcept;

	/**
	 * @brief   get a CodePos that will return false in IsProvided()
	 * @returns an empty CodePos (line = -1)
	 */
	[[nodiscard]] static CodePos NotProvided() noexcept;
};

/**
 * @def   JUNIA_CODEPOS
 * @brief inserts a Junia::CodePos instantiation with information of the current
 *        code line
 */
#define JUNIA_CODEPOS (::Junia::CodePos(__FILE__, __FUNCTION__, __LINE__))

/**
 *
 * @class Exception
 * @brief the base class for all Junia exceptions
 *
 * @note  all Junia exceptions have to inherit from this class either directly
 *        or indirectly. Junia Methods or Functions may not throw any other
 *        exceptions.
 *
 */
class JUNIA_SYMBOL Exception : public std::runtime_error {
public:
	/**
	 * @brief          Exception object constructor
	 * @param msg      a text message explaining the exception
	 * @param previous an exception that led to this exception or a nullptr
	 * @param location the code position this exception was thrown in (see
	 *                 JUNIA_CODEPOS)
	 */
	explicit Exception(const utf8_string& msg, std::exception_ptr previous = nullptr, CodePos location = CodePos::NotProvided()) noexcept;

	/**
	 * @brief   do not use. Use GetMessage() instead.
	 * @returns a c string containing the error message with the lifetime of the
	 *          exception
	 */
	[[nodiscard]] virtual const char* what() const override final;

	/**
	 * @brief   check if the code position was provided when throwing
	 * @returns true if it was provided, false otherwise
	 */
	[[nodiscard]] bool CodePosProvided() const noexcept;

	/**
	 * @brief   get the message text of the exception
	 * @returns a reference to the message string
	 */
	[[nodiscard]] virtual const utf8_string& GetMessage() const noexcept;

	/**
	 * @brief   get the code position of the exception occurrance
	 * @returns the location in code where the exception occurred
	 */
	[[nodiscard]] const CodePos& Where() const noexcept;

	/**
	 * @brief   get the exception that lead to this exception
	 * @returns an exception pointer to the previous exception or a nullptr if
	 *          there wasn't a previous exception
	 */
	[[nodiscard]] std::exception_ptr GetPrevious() const noexcept;

	/**
	 * @brief         creates a new exception as a pointer
	 * @tparam  T     the type of the exception to create
	 * @tparam  TArgs the constructor argument types of the exception
	 * @param   args  the constructor arguments of the exception
	 * @returns       an exception pointer with the exception
	 */
	template <typename T, typename... TArgs>
		requires std::derived_from<T, std::exception> && std::constructible_from<T, TArgs...>
	[[nodiscard]] static std::exception_ptr GetAsPtr(TArgs... args);

	/**
	 * @brief             get the message text of the exception and previous
	 *                    exceptions
	 * @param   recursive if the message texts of the previous messages should
	 *                    be appended to this one (seperated by a newline
	 *                    character)
	 * @returns           a string with the message text and previous message
	 *                    texts
	 */
	[[nodiscard]] utf8_string GetText(bool recursive) const;

protected:
	utf8_string        message;
	CodePos            location;
	std::exception_ptr previous;
};

template <typename T, typename... TArgs>
	requires std::derived_from<T, std::exception> && std::constructible_from<T, TArgs...>
std::exception_ptr Exception::GetAsPtr(TArgs... args) {
	return std::make_exception_ptr<T>(T(args...));
}

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_EXCEPTION)

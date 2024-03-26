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
 * @brief  A structure to hold information about a position in code
 */
struct JUNIA_SYMBOL CodePos {
	const char* file;
	const char* function;
	int         line;

	/**
	 * @brief CodePos object constructor (NotProvided)
	 */
	CodePos() noexcept;

	/**
	 * @brief          CodePos object constructor
	 * @param file     The file (__FILE__)
	 * @param function The function (__FUNCTION__)
	 * @param line     The line number (__LINE__). This must be positive
	 */
	CodePos(const char* file, const char* function, int line) noexcept;

	/**
	 * @brief   Check if the Code position was provided
	 * @returns true if the Code position is provided, false otherwise
	 */
	[[nodiscard]] bool IsProvided() const noexcept;

	/**
	 * @brief   Get a CodePos that will return false in IsProvided()
	 * @returns An empty CodePos (line = -1)
	 */
	[[nodiscard]] static CodePos NotProvided() noexcept;
};

/**
 * @def   JUNIA_CODEPOS
 * @brief Inserts a Junia::CodePos instantiation with information of the current
 *        code line
 */
#define JUNIA_CODEPOS (::Junia::CodePos(__FILE__, __FUNCTION__, __LINE__))

/**
 *
 * @class Exception
 * @brief The base class for all Junia exceptions
 *
 * @note  All Junia exceptions have to inherit from this class either directly
 *        or indirectly. Junia Methods or Functions may not throw any other
 *        exceptions.
 *
 */
class JUNIA_SYMBOL Exception : public std::runtime_error {
public:
	/**
	 * @brief          Exception object constructor
	 * @param msg      A text message explaining the exception
	 * @param previous An exception that led to this exception or a nullptr
	 * @param location The code position this exception was thrown in (see
	 *                 JUNIA_CODEPOS)
	 */
	explicit Exception(const utf8_string& msg, std::exception_ptr previous = nullptr, CodePos location = CodePos::NotProvided()) noexcept;

	/**
	 * @brief   Do not use. Use GetMessage() instead.
	 * @returns A c string containing the error message with the lifetime of the
	 *          exception
	 */
	[[nodiscard]] virtual const char* what() const override final;

	/**
	 * @brief   Check if the code position was provided when throwing
	 * @returns true if it was provided, false otherwise
	 */
	[[nodiscard]] bool CodePosProvided() const noexcept;

	/**
	 * @brief   Get the message text of the exception
	 * @returns A reference to the message string
	 */
	[[nodiscard]] virtual const utf8_string& GetMessage() const noexcept;

	/**
	 * @brief   Get the code position of the exception occurrance
	 * @returns The location in code where the exception occurred
	 */
	[[nodiscard]] const CodePos& Where() const noexcept;

	/**
	 * @brief   Get the exception that lead to this exception
	 * @returns An exception pointer to the previous exception or a nullptr if
	 *          there wasn't a previous exception
	 */
	[[nodiscard]] std::exception_ptr GetPrevious() const noexcept;

	/**
	 * @brief         Creates a new exception as a pointer
	 * @tparam  T     The type of the exception to create
	 * @tparam  TArgs The constructor argument types of the exception
	 * @param   args  The constructor arguments of the exception
	 * @returns       An exception pointer with the exception
	 */
	template <typename T, typename... TArgs>
		requires std::derived_from<T, std::exception> && std::constructible_from<T, TArgs...>
	[[nodiscard]] static std::exception_ptr GetAsPtr(TArgs... args);

	/**
	 * @brief             Get the message text of the exception and previous
	 *                    exceptions
	 * @param   recursive If the message texts of the previous messages should
	 *                    be appended to this one (seperated by a newline
	 *                    character)
	 * @returns           A string with the message text and previous message
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

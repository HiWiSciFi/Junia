################################################################################
#
# @file      CMakeLists.txt
# @brief     Contains the build instructions for project files for Junia
# @author    Max Hager
# @date      17.03.2024
# @copyright © Max Hager, 2024. All right reserved.
#
################################################################################

cmake_minimum_required(VERSION 3.26)

project(Junia VERSION 0.1.1 LANGUAGES CXX)

add_library(Junia SHARED)

set( JUNIA_FOUND          ON                                    CACHE     BOOL "" )
set( JUNIA_SOURCE_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/src"     CACHE     PATH "" )
set( JUNIA_INCLUDE_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE     PATH "" )
set( JUNIA_LIBRARY_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/lib"     CACHE     PATH "" )
set( JUNIA_LIBRARY        "${JUNIA_LIBRARY_DIR}/Junia.lib"      CACHE FILEPATH "" )
set( JUNIA_SHARED_LIBRARY "${JUNIA_LIBRARY_DIR}/Junia.dll"      CACHE FILEPATH "" )

set_target_properties(Junia PROPERTIES
	CXX_STANDARD_REQUIRED            ON
	CXX_STANDARD                     20
	FOLDER                           "Junia"
	LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${JUNIA_LIBRARY_DIR}"
	LIBRARY_OUTPUT_DIRECTORY_RELEASE "${JUNIA_LIBRARY_DIR}"
	LIBRARY_OUTPUT_DIRECTORY         "${JUNIA_LIBRARY_DIR}"
	LIBRARY_OUTPUT_NAME_DEBUG        "Junia"
	LIBRARY_OUTPUT_NAME_RELEASE      "Junia"
	LIBRARY_OUTPUT_NAME              "Junia"
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${JUNIA_LIBRARY_DIR}"
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${JUNIA_LIBRARY_DIR}"
	ARCHIVE_OUTPUT_DIRECTORY         "${JUNIA_LIBRARY_DIR}"
	ARCHIVE_OUTPUT_NAME_DEBUG        "Junia"
	ARCHIVE_OUTPUT_NAME_RELEASE      "Junia"
	ARCHIVE_OUTPUT_NAME              "Junia"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${JUNIA_LIBRARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${JUNIA_LIBRARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY         "${JUNIA_LIBRARY_DIR}"
	RUNTIME_OUTPUT_NAME_DEBUG        "Junia"
	RUNTIME_OUTPUT_NAME_RELEASE      "Junia"
	RUNTIME_OUTPUT_NAME              "Junia"
)

target_compile_definitions(Junia PRIVATE BUILD_JUNIA)

# Vulkan
find_package(Vulkan)
if(NOT ${Vulkan_FOUND})
	message(FATAL_ERROR "Vulkan could not be found! Make sure $VULKAN_SDK environment variable is set if the problem persists.")
endif()

target_include_directories(Junia PUBLIC
	"${JUNIA_INCLUDE_DIR}"
	"${Vulkan_INCLUDE_DIR}"
)

target_link_libraries(Junia PRIVATE
	"${Vulkan_LIBRARY}"
)

set(SRC_JUNIA
	"${JUNIA_SOURCE_DIR}/Junia/Junia.cpp"
)

set(SRC_JUNIA_CORE
	"${JUNIA_SOURCE_DIR}/Junia/Core/Exception.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Core/StringConvert.cpp"
)

set(SRC_JUNIA_EXCEPTIONS
	"${JUNIA_SOURCE_DIR}/Junia/Exceptions/ExStringEncoding.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Exceptions/ExUnicodeStringEncoding.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Exceptions/ExUtf8StringEncoding.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Exceptions/ExUtf16StringEncoding.cpp"
)

set(INCLUDE_JUNIA
	"${JUNIA_INCLUDE_DIR}/Junia/Junia.hpp"
)

set(INCLUDE_JUNIA_CORE
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Core.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Exception.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/StringConvert.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Strings.hpp"
)

set(INCLUDE_JUNIA_EXCEPTIONS
	"${JUNIA_INCLUDE_DIR}/Junia/Exceptions/ExStringEncoding.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Exceptions/ExUnicodeStringEncoding.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Exceptions/ExUtf16StringEncoding.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Exceptions/ExUtf8StringEncoding.hpp"
)

target_sources(Junia PRIVATE
	${SRC_JUNIA}
	${SRC_JUNIA_CORE}
	${SRC_JUNIA_EXCEPTIONS}
	${INCLUDE_JUNIA}
	${INCLUDE_JUNIA_CORE}
	${INCLUDE_JUNIA_EXCEPTIONS}
)

source_group( "src"            FILES ${SRC_JUNIA}            )
source_group( "src/Core"       FILES ${SRC_JUNIA_CORE}       )
source_group( "src/Exceptions" FILES ${SRC_JUNIA_EXCEPTIONS} )

source_group( "include"            FILES ${INCLUDE_JUNIA}            )
source_group( "include/Core"       FILES ${INCLUDE_JUNIA_CORE}       )
source_group( "include/Exceptions" FILES ${INCLUDE_JUNIA_EXCEPTIONS} )

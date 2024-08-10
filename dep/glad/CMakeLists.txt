################################################################################
#
# @file      CMakeLists.txt
# @brief     Contains the build instructions for project files for the generated
#            GLAD OpenGL interface
# @author    Max Hager
# @date      2024-07-11
# @copyright © Max Hager, 2024. All right reserved.
#
################################################################################

cmake_minimum_required(VERSION 3.26)

project(glad VERSION 4.6 LANGUAGES C)

add_library(glad STATIC)

set( GLAD_FOUND       ON                                    CACHE     BOOL "" )
set( GLAD_SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src"     CACHE     PATH "" )
set( GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE     PATH "" )
set( GLAD_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib"     CACHE     PATH "" )
set( GLAD_LIBRARY     "${GLAD_LIBRARY_DIR}/glad.lib"        CACHE FILEPATH "" )

set_target_properties(glad PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${GLAD_LIBRARY_DIR}"
	LIBRARY_OUTPUT_DIRECTORY_RELEASE "${GLAD_LIBRARY_DIR}"
	LIBRARY_OUTPUT_DIRECTORY         "${GLAD_LIBRARY_DIR}"
	LIBRARY_OUTPUT_NAME_DEBUG        "glad"
	LIBRARY_OUTPUT_NAME_RELEASE      "glad"
	LIBRARY_OUTPUT_NAME              "glad"
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${GLAD_LIBRARY_DIR}"
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${GLAD_LIBRARY_DIR}"
	ARCHIVE_OUTPUT_DIRECTORY         "${GLAD_LIBRARY_DIR}"
	ARCHIVE_OUTPUT_NAME_DEBUG        "glad"
	ARCHIVE_OUTPUT_NAME_RELEASE      "glad"
	ARCHIVE_OUTPUT_NAME              "glad"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${GLAD_LIBRARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${GLAD_LIBRARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY         "${GLAD_LIBRARY_DIR}"
	RUNTIME_OUTPUT_NAME_DEBUG        "glad"
	RUNTIME_OUTPUT_NAME_RELEASE      "glad"
	RUNTIME_OUTPUT_NAME              "glad"
)

target_include_directories(glad PRIVATE
	"${GLAD_INCLUDE_DIR}"
)

target_link_libraries(glad PUBLIC
	"opengl32"
)

set(SRC_GLAD
	"${GLAD_SOURCE_DIR}/gl.c"
	"${GLAD_SOURCE_DIR}/wgl.c"
)

set(INCLUDE_GLAD
	"${GLAD_INCLUDE_DIR}/glad/gl.h"
	"${GLAD_INCLUDE_DIR}/glad/wgl.h"
)

set(INCLUDE_KHR
	"${GLAD_INCLUDE_DIR}/KHR/khrplatform.h"
)

target_sources(glad PRIVATE
	${SRC_GLAD}

	${INCLUDE_GLAD}
	${INCLUDE_KHR}
)

source_group( "src"          FILES ${SRC_GLAD}     )
source_group( "include/glad" FILES ${INCLUDE_GLAD} )
source_group( "include/KHR"  FILES ${INCLUDE_KHR}  )

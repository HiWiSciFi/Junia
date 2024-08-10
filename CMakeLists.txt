################################################################################
#
# @file      CMakeLists.txt
# @brief     Contains the build instructions for project files for Junia
# @author    Max Hager
# @date      2024-03-17
# @copyright © Max Hager, 2024. All right reserved.
#
################################################################################

cmake_minimum_required(VERSION 3.26)

project(Junia VERSION 0.1.1 LANGUAGES CXX)

add_library(Junia SHARED)

set( JUNIA_FOUND          ON                                    CACHE     BOOL "" )
set( JUNIA_SOURCE_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/src"     CACHE     PATH "" )
set( JUNIA_INCLUDE_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE     PATH "" )
set( JUNIA_DEP_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/dep"     CACHE     PATH "" )
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

# GLAD
add_subdirectory("${JUNIA_DEP_DIR}/glad")
if(NOT ${GLAD_FOUND})
	message(FATAL_ERROR "GLAD could not be found!")
endif()

set_target_properties(glad PROPERTIES
	FOLDER "Junia/dep"
)

# OpenGL
set( GL_LIBRARY "opengl32" )

target_include_directories(Junia PUBLIC
	"${JUNIA_INCLUDE_DIR}"
	"${Vulkan_INCLUDE_DIR}"
	"${GLAD_INCLUDE_DIR}"
)

target_link_libraries(Junia PRIVATE
	"${Vulkan_LIBRARY}"
	"${GLAD_LIBRARY}"
	"${GL_LIBRARY}"
)

set(SRC_JUNIA
	"${JUNIA_SOURCE_DIR}/Junia/Junia.cpp"
)

set(SRC_JUNIA_CORE
	"${JUNIA_SOURCE_DIR}/Junia/Core/Exception.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Core/Strings.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Core/Globals.hpp"
	"${JUNIA_SOURCE_DIR}/Junia/Core/Globals.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Core/Version.cpp"
)

set(SRC_JUNIA_CORE_EXCEPTIONS
	"${JUNIA_SOURCE_DIR}/Junia/Core/Exceptions/ExStringEncoding.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Core/Exceptions/ExUtf8StringEncoding.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Core/Exceptions/ExUtf16StringEncoding.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Core/Exceptions/ExUtf32StringEncoding.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Exceptions/ExWindows.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Exceptions/ExExepath.cpp"
)

set(SRC_JUNIA_RENDERING
	"${JUNIA_SOURCE_DIR}/Junia/Rendering/Window.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Rendering/Vulkan.hpp"
	"${JUNIA_SOURCE_DIR}/Junia/Rendering/Vulkan.cpp"
	"${JUNIA_SOURCE_DIR}/Junia/Rendering/Monitor.cpp"
)

set(SRC_JUNIA_RENDERING_VULKAN
	"${JUNIA_SOURCE_DIR}/Junia/Rendering/Vulkan/JVK_Instance.hpp"
	"${JUNIA_SOURCE_DIR}/Junia/Rendering/Vulkan/JVK_Instance.cpp"
)

set(SRC_JUNIA_RENDERING_OPENGL
	"${JUNIA_SOURCE_DIR}/Junia/Rendering/OpenGL/JGL_Instance.hpp"
	"${JUNIA_SOURCE_DIR}/Junia/Rendering/OpenGL/JGL_Instance.cpp"
)

set(INCLUDE_JUNIA
	"${JUNIA_INCLUDE_DIR}/Junia/Junia.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Platform.hpp"
)

set(INCLUDE_JUNIA_MATH
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Types.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Vectors.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Vector2.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Vector3.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Matrices.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Matrix3x3.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Matrix4x4.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Quaternion.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Math/Rect.hpp"
)

set(INCLUDE_JUNIA_CORE
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Core.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Exception.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Strings.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Version.hpp"
)

set(INCLUDE_JUNIA_CORE_EXCEPTIONS
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Exceptions/ExStringEncoding.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Exceptions/ExUtf16StringEncoding.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Exceptions/ExUtf8StringEncoding.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Core/Exceptions/ExUtf32StringEncoding.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Exceptions/ExWindows.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Exceptions/ExExepath.hpp"
)

set(INCLUDE_JUNIA_RENDERING
	"${JUNIA_INCLUDE_DIR}/Junia/Rendering/Window.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Rendering/RenderAPI.hpp"
	"${JUNIA_INCLUDE_DIR}/Junia/Rendering/Monitor.hpp"
)

target_sources(Junia PRIVATE
	${SRC_JUNIA}
	${SRC_JUNIA_CORE}
	${SRC_JUNIA_CORE_EXCEPTIONS}
	${SRC_JUNIA_RENDERING}
	${SRC_JUNIA_RENDERING_VULKAN}
	${SRC_JUNIA_RENDERING_OPENGL}

	${INCLUDE_JUNIA}
	${INCLUDE_JUNIA_MATH}
	${INCLUDE_JUNIA_CORE}
	${INCLUDE_JUNIA_CORE_EXCEPTIONS}
	${INCLUDE_JUNIA_RENDERING}
)

source_group( "src"                  FILES ${SRC_JUNIA}                  )
source_group( "src/Core"             FILES ${SRC_JUNIA_CORE}             )
source_group( "src/Core/Exceptions"  FILES ${SRC_JUNIA_CORE_EXCEPTIONS}  )
source_group( "src/Rendering"        FILES ${SRC_JUNIA_RENDERING}        )
source_group( "src/Rendering/Vulkan" FILES ${SRC_JUNIA_RENDERING_VULKAN} )
source_group( "src/Rendering/OpenGL" FILES ${SRC_JUNIA_RENDERING_OPENGL} )

source_group( "include"                 FILES ${INCLUDE_JUNIA}                 )
source_group( "include/Math"       FILES ${INCLUDE_JUNIA_MATH}       )
source_group( "include/Core"            FILES ${INCLUDE_JUNIA_CORE}            )
source_group( "include/Core/Exceptions" FILES ${INCLUDE_JUNIA_CORE_EXCEPTIONS} )
source_group( "include/Rendering"  FILES ${INCLUDE_JUNIA_RENDERING}  )

add_dependencies(Junia glad)

if(DEFINED JUNIA_DLL_COPY_TARGET_DIR)
	add_custom_command(TARGET Junia
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${JUNIA_SHARED_LIBRARY}"
			"${JUNIA_DLL_COPY_TARGET_DIR}"
		COMMENT "Copying DLLs"
		VERBATIM
	)
endif()

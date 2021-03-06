depsloc = "../Testing/dependencies/"

group "Dependencies"
	include "dependencies/premake-dependencies.lua"

group ""
project "Testing"
	location "."
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("../out/%{prj.name}/" .. buildtargetname)
	objdir ("../out-obj/%{prj.name}/" .. buildtargetname)

	files {
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs {
		"../Junia/src",
		"%{Dependency.GLM.include}"
	}

	libdirs {

	}

	links {
		"Junia"
	}

	--REMOVE
	filter "options:opengl"
		defines "JE_GAPI_SUPPORTED_OPENGL"
	--END

	filter "system:windows"
		systemversion "latest"
		defines {
			"JE_TARGETPLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
			"JE_CONFIG_DEBUG",
			"JELOG_MAX_TRACE"
		}

	filter "configurations:Optimized"
		defines {
			"JE_CONFIG_OPTIMIZED",
			"JELOG_MAX_WARN"
		}

	filter "configurations:Release"
		defines {
			"JE_CONFIG_RELEASE",
			"JELOG_MAX_ERROR"
		}

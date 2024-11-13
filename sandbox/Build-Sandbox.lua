project "Sandbox"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++latest"
	staticruntime "on"

	targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("../bin/int/" .. OutputDir .. "/%{prj.name}")

	files { "Source/**.cpp", "Source/**.h" }

	includedirs {
		"Source",
		"../Universe/Source",
		"../Universe/Vendor/spdlog/include",
		"../Universe/Vendor/glm",
		"../Universe/Vendor/imgui",
	}

	links
	{
		"Universe"
	}

    filter "system:windows"
		systemversion "latest"
		defines {"UE_PLATFORM_WINDOWS"}

	filter "configurations:Debug"
		defines "UE_DEBUG"
        runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "UE_RELEASE"
        runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		defines "UE_DIST"
		runtime "Release"
		optimize "on"
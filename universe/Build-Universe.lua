project "Universe"
    kind "StaticLib"
	language "C++"
    cppdialect "C++latest"
    staticruntime "on"

    targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../bin/int/" .. OutputDir .. "/%{prj.name}")

    files {
        "Source/**.cpp",
        "Source/**.h",
        "Vendor/glm/glm/**.hpp",
        "Vendor/glm/glm/**.inl"
    }

    IncludeDir = {}
    IncludeDir["spdlog"] = "Vendor/spdlog/include"
    IncludeDir["GLFW"] = "Vendor/GLFW/include"
    IncludeDir["glad"] = "Vendor/glad/include"
    IncludeDir["ImGui"] = "Vendor/imgui"
    IncludeDir["glm"] = "Vendor/glm"

    includedirs {
        "Source",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}" ,
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "opengl32.lib",
        "glad",
        "ImGui"
    }

    pchheader "UEpch.h"
    pchsource "Source/UEpch.cpp"

	filter "system:windows"
        systemversion "latest"
		defines { "UE_PLATFORM_WINDOWS", "_CRT_SECURE_NO_WARNINGS" }



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
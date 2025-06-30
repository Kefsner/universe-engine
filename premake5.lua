workspace "UniverseEngine"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "./"
    startproject "Sandbox"

    filter "configurations:Debug"
        defines { "DEBUG", "UE_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "UE_RELEASE" }
        optimize "On"

    filter "system:windows"
        defines { "UE_PLATFORM_WINDOWS" }

    filter "system:linux"
        defines { "UE_PLATFORM_LINUX" }

-- Sub-projects
include "universe/vendor/glfw"
include "universe"
include "forge"
include "sandbox"
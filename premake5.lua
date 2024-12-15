workspace "UniverseEngine"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "./"
    startproject "Forge"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"

-- Sub-projects
include "universe/vendor/glfw"
include "universe"
include "forge"
include "sandbox"
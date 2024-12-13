workspace "UniverseEngine"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "./"
    startproject "UniverseEngine"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

-- Sub-projects
include "universe"
include "forge"
include "sandbox"
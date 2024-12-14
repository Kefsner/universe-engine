project "Universe"
   location "%{wks.location}/universe"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   staticruntime "off"

   targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}/%{prj.name}")
   objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}/%{prj.name}")

   files {
      "%{prj.location}/src/**.cpp",
      "%{prj.location}/src/**.hpp",
      "%{prj.location}/vendor/glad/src/glad.c"
   }

   includedirs {
      "%{prj.location}/src",
      "%{prj.location}/vendor/spdlog/include",
      "%{prj.location}/vendor/glfw/include",
      "%{prj.location}/vendor/glad/include"
   }

   links {
      "OpenGL32",
      "glfw"
   }

   pchheader "%{prj.location}/src/pch.hpp"
   pchsource "%{prj.location}/src/pch.cpp"

   filter { "files:vendor/glad/src/glad.c" }
      flags { "NoPCH" }

   filter "configurations:Debug"
      defines { "UE_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "UE_RELEASE" }
      optimize "On"


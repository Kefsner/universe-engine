project "Universe"
   location "%{wks.location}/universe"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   staticruntime "off"

   targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}/%{prj.name}")
   objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}/%{prj.name}")

   includedirs {
      "src",
      "vendor/spdlog/include",
      "vendor/glad/include"
   }

   files {
      "src/**.cpp",
      "src/**.hpp",
      "vendor/glad/src/glad.c"
   }

   links {
      "OpenGL32"
   }

   pchheader "src/pch.hpp"
   pchsource "src/pch.cpp"

   filter { "files:vendor/glad/src/glad.c" }
      flags { "NoPCH" }

   filter "configurations:Debug"
      defines { "UE_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "UE_RELEASE" }
      optimize "On"


project "Universe"
   location "%{wks.location}/universe"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   staticruntime "off"

   targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}/%{prj.name}")
   objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}/%{prj.name}")

   files {
      "src/**.cpp",
      "src/**.hpp"
   }

   includedirs {
      "src",
   }

   filter "configurations:Debug"
   defines { "UE_DEBUG" }
   symbols "On"

   filter "configurations:Release"
   defines { "UE_RELEASE" }
   optimize "On"


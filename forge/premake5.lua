project "Forge"
   location "%{wks.location}/forge"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++23"
   staticruntime "off"

   targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}/%{prj.name}")
   objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}/%{prj.name}")

   files {
      "%{prj.location}/src/**.cpp",
      "%{prj.location}/src/**.hpp"
   }

   includedirs {
      "%{prj.location}/src",
      "%{wks.location}/universe/src",
      "%{wks.location}/universe/vendor/spdlog/include",
      "%{wks.location}/universe/vendor/glfw/include",
      "%{wks.location}/universe/vendor/glad/include",
      "%{wks.location}/universe/vendor/imgui",
      "%{wks.location}/universe/vendor/glm",
      "%{wks.location}/universe/vendor/stb"
   }

   links {
      "Universe",
      "GLFW",
      "gdi32",
      "user32",
      "shell32",
      "kernel32",
      "opengl32"
   }

   filter "configurations:Debug"
      defines { "UE_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "UE_RELEASE" }
      optimize "On"

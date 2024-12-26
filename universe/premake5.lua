project "Universe"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   staticruntime "off"
   location "%{wks.location}/universe"

   pchheader "%{prj.location}/src/pch.hpp"
   pchsource "%{prj.location}/src/pch.cpp"

   targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}/%{prj.name}")
   objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}/%{prj.name}")

   includedirs {
      "%{prj.location}/src",
      "%{prj.location}/vendor/spdlog/include",
      "%{prj.location}/vendor/glad/include",
      "%{prj.location}/vendor/glfw/include",
      "%{prj.location}/vendor/glm",
      "%{prj.location}/vendor/imgui",
      "%{prj.location}/vendor/stb"
   }

   files {
      "%{prj.location}/src/**.cpp",
      "%{prj.location}/src/**.hpp",
      "%{prj.location}/vendor/glad/src/glad.c",
      "%{prj.location}/vendor/imgui/imgui.cpp",
      "%{prj.location}/vendor/imgui/imgui_draw.cpp",
      "%{prj.location}/vendor/imgui/imgui_widgets.cpp",
      "%{prj.location}/vendor/imgui/imgui_tables.cpp",
      "%{prj.location}/vendor/imgui/backends/imgui_impl_glfw.cpp",
      "%{prj.location}/vendor/imgui/backends/imgui_impl_opengl3.cpp",
      -- "%{prj.location}/vendor/imgui/imgui_demo.cpp",
      "%{prj.location}/vendor/stb/stb_image.cpp"
   }

   defines {
      "GLFW_INCLUDE_NONE"
   }

   links {
      "GLFW",
      "OpenGL32"
   }

   filter { "files:vendor/glad/src/glad.c" }
      flags { "NoPCH" }

   filter "configurations:Debug"
      defines { "UE_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "UE_RELEASE" }
      optimize "On"


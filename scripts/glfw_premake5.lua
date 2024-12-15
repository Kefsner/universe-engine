project "GLFW"
   location "%{wks.location}/universe/vendor/glfw"
   kind "StaticLib"
   language "C"
   architecture "x64"
   staticruntime "off"

   targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}/%{prj.name}")
   objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}/%{prj.name}")

   files {
      -- Headers
      "%{prj.location}/include/GLFW/glfw3.h",
      "%{prj.location}/include/GLFW/glfw3native.h",

      -- Core
      "%{prj.location}/src/context.c",
      "%{prj.location}/src/init.c",
      "%{prj.location}/src/input.c",
      "%{prj.location}/src/monitor.c",
      "%{prj.location}/src/window.c",
      "%{prj.location}/src/vulkan.c",
      -- Careful from here
      "%{prj.location}/src/platform.c",

   }

   filter "system:windows"
      systemversion "latest"
      
      files {
         "%{prj.location}/src/win32_thread.c",
         "%{prj.location}/src/win32_time.c",
         "%{prj.location}/src/win32_module.c",
         "%{prj.location}/src/win32_init.c",
         "%{prj.location}/src/win32_monitor.c",
         "%{prj.location}/src/win32_joystick.c",
         "%{prj.location}/src/wgl_context.c",
         "%{prj.location}/src/win32_window.c",
         -- Why null stuff?
         "%{prj.location}/src/null_init.c",
         "%{prj.location}/src/null_monitor.c",
         "%{prj.location}/src/osmesa_context.c",
         "%{prj.location}/src/egl_context.c",
         "%{prj.location}/src/null_window.c",
         "%{prj.location}/src/null_joystick.c",
      }

      links {
         "gdi32",
         "user32",
         "shell32",
         "kernel32"
      }

      defines {
         "_GLFW_WIN32",
      }
      
   filter "configurations:Debug"
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      runtime "Release"
      optimize "On"

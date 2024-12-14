project "GLFW"
   location "%{wks.location}/universe/vendor/glfw"
   kind "StaticLib"
   language "C"
   staticruntime "off"

   targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}/%{prj.name}")
   objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}/%{prj.name}")

   files {
      "%{prj.location}/include/GLFW/glfw3.h",
      "%{prj.location}/include/GLFW/glfw3native.h",
      "%{prj.location}/src/context.c",
      "%{prj.location}/src/egl_context.c",
      "%{prj.location}/src/init.c",
      "%{prj.location}/src/input.c",
      "%{prj.location}/src/monitor.c",
      "%{prj.location}/src/osmesa_context.c",
      "%{prj.location}/src/vulkan.c",
      "%{prj.location}/src/window.c",
      "%{prj.location}/src/wgl_context.c",
      "%{prj.location}/src/win32_init.c",
      "%{prj.location}/src/win32_joystick.c",
      "%{prj.location}/src/win32_monitor.c",
      "%{prj.location}/src/win32_time.c",
      "%{prj.location}/src/win32_thread.c",
      "%{prj.location}/src/win32_window.c"
   }

   includedirs {
      "%{prj.location}/include"
   }

   filter "configurations:Debug"
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      runtime "Release"
      optimize "On"

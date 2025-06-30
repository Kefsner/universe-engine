project "GLFW"
   location "%{wks.location}/universe/vendor/glfw"
   kind "StaticLib"
   language "C"
   architecture "x64"
   staticruntime "off"

   targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}/%{prj.name}")
   objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}/%{prj.name}")

   files {
      "%{prj.location}/include/GLFW/glfw3.h",
      "%{prj.location}/include/GLFW/glfw3native.h",
      "%{prj.location}/src/init.c",
      "%{prj.location}/src/window.c",
      "%{prj.location}/src/context.c",
      "%{prj.location}/src/input.c",
      "%{prj.location}/src/monitor.c",
      "%{prj.location}/src/vulkan.c",
      "%{prj.location}/src/platform.c",
      "%{prj.location}/src/null_init.c",
      "%{prj.location}/src/null_monitor.c",
      "%{prj.location}/src/osmesa_context.c",
      "%{prj.location}/src/egl_context.c",
      "%{prj.location}/src/null_window.c",
      "%{prj.location}/src/null_joystick.c",
   }

   filter "system:windows"     
      files {
         "%{prj.location}/src/win32_thread.c",
         "%{prj.location}/src/win32_time.c",
         "%{prj.location}/src/win32_module.c",
         "%{prj.location}/src/win32_init.c",
         "%{prj.location}/src/win32_monitor.c",
         "%{prj.location}/src/win32_joystick.c",
         "%{prj.location}/src/wgl_context.c",
         "%{prj.location}/src/win32_window.c",
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
   
   filter "system:linux"
      files {
         "%{prj.location}/src/x11_init.c",
         "%{prj.location}/src/x11_monitor.c",
         "%{prj.location}/src/x11_window.c",
         "%{prj.location}/src/posix_time.c",
         "%{prj.location}/src/posix_thread.c",
         "%{prj.location}/src/glx_context.c",
         "%{prj.location}/src/linux_joystick.c",
         "%{prj.location}/src/xkb_unicode.c",
         "%{prj.location}/src/glx_context.c",
         "%{prj.location}/src/posix_module.c",
         "%{prj.location}/src/posix_poll.c",
      }

      links {
         "GL",
         "X11",
         "pthread",
         "dl",
         "m"
      }

      defines {
         "_GLFW_X11"
      }

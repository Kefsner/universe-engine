#pragma once
#include "Universe/Core/Window.h"
#include "Universe/Renderer/GraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Universe {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		inline void* GetNativeWindow() const override { return m_Window; }
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
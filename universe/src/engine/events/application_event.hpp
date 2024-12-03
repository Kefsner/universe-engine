#pragma once

#include <sstream>
#include "engine/events/event.hpp"

namespace Universe {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		static EventType GetStaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WindowClose"; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WindowResize"; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

	private:
		int m_Width;
		int m_Height;
	};
}
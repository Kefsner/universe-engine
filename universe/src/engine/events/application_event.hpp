#pragma once

#include <sstream>
#include "engine/events/event.hpp"

namespace Universe {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EventType GetEventType() const override { return EventType::WindowClose; }
		const char* GetName() const override { return "WindowClose"; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		EventType GetEventType() const override { return EventType::WindowResize; }
		const char* GetName() const override { return "WindowResize"; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

	private:
		int m_Width;
		int m_Height;
	};
}
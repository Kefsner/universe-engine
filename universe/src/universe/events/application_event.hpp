#pragma once

#include <sstream>

#include "universe/events/event.hpp"

namespace Universe {

	class WindowCloseEvent : public Event
	{
	public:
		// Constructor and Destructor
		WindowCloseEvent() = default;
		~WindowCloseEvent() = default;

		// Virtual functions
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WindowClose"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }

		// Static functions
		static EventType GetStaticType() { return EventType::WindowClose; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		// Constructor and Destructor
		WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}
		~WindowResizeEvent() = default;

		// Virtual functions
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WindowResize"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		// Static functions
		static EventType GetStaticType() { return EventType::WindowResize; }

		// Getters
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

	private:
		int m_Width, m_Height; // New window size
	};
}
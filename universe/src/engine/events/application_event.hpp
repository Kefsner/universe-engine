#pragma once

#include "engine/events/event.hpp"

namespace Universe {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		static EventType GetStaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return EventType::WindowClose; }
	};
}
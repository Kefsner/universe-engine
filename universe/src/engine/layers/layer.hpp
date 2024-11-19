#pragma once

#include "engine/events/event.hpp"

namespace Universe {
    
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer")
            : m_DebugName(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return m_DebugName; }
        
    protected:
        std::string m_DebugName;
    };
}
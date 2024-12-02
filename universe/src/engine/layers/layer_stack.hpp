#pragma once

#include "engine/layers/layer.hpp"

namespace Universe {

    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer*> m_Layers; ///< The collection of Layers managed by the stack.
        unsigned int m_LayerInsertIndex = 0; ///< Tracks where the next Layer should be inserted.
    };

}

#pragma once

#include "universe/layers/layer.hpp"

namespace Universe
{
    class LayerStack
    {
    public:
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
        std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
        std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }

    private:
        std::vector<Layer*> m_Layers;
        uint32_t m_LayerInsertIndex = 0;
    };
}
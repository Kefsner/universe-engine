#pragma once

#include <vector>

#include "universe/layers/layer.hpp"

namespace Universe {

    class LayerStack
    {
    public:
        // Constructor and Destructor
        LayerStack() = default;
        ~LayerStack();

        // Layer Management
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        // Layer Iterators for range-based loops
        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer*> m_Layers;           // Vector of layers
        unsigned int m_LayerInsertIndex = 0;    // Index to insert layers
    };

}

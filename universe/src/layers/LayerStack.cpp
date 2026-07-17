#include "layers/LayerStack.hpp"

namespace Universe
{
    LayerStack::LayerStack()
    {
    }

    void LayerStack::AddLayer(std::shared_ptr<Layer> layer)
    {
        m_Layers.push_back(layer);
    }
}
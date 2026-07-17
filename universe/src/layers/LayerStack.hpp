#pragma once

#include "layers/Layer.hpp"

#include <vector>
#include <memory>

namespace Universe
{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack() = default;

        void AddLayer(std::shared_ptr<Layer> layer);

        using ConstIterator = std::vector<std::shared_ptr<Layer>>::const_iterator;
        ConstIterator Begin() { return m_Layers.begin(); }
        ConstIterator End() { return m_Layers.end(); }

    private:
        std::vector<std::shared_ptr<Layer>> m_Layers;
    };
}
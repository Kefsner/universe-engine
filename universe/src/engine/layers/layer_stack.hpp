#pragma once

#include "engine/layers/layer.hpp"

namespace Universe {

    /**
     * @class LayerStack
     * @brief Manages a collection of Layers in a stack-like structure.
     * 
     * The `LayerStack` class allows for adding and iterating through Layers in
     * a specific order. Layers are typically updated and rendered in the order
     * they were added, while events are propagated in reverse order.
     */
    class LayerStack {
    public:
        /**
         * @brief Constructs the LayerStack.
         * 
         * Initializes the internal data structures used to manage Layers.
         */
        LayerStack();

        /**
         * @brief Destroys the LayerStack.
         * 
         * Cleans up all Layers managed by the stack.
         */
        ~LayerStack();

        /**
         * @brief Adds a Layer to the stack.
         * 
         * Layers added via this method are inserted at the correct position in the stack
         * and are fully managed by the LayerStack. Typically, new Layers are inserted
         * at the beginning of the `m_Layers` vector, before overlays.
         * 
         * @param layer The Layer to be added to the stack.
         */
        void PushLayer(Layer* layer);

        /**
         * @brief Returns an iterator to the beginning of the LayerStack.
         * 
         * Useful for iterating over all Layers in the stack.
         * 
         * @return An iterator pointing to the first Layer in the stack.
         */
        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

        /**
         * @brief Returns an iterator to the end of the LayerStack.
         * 
         * Useful for iterating over all Layers in the stack.
         * 
         * @return An iterator pointing past the last Layer in the stack.
         */
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer*> m_Layers; ///< The collection of Layers managed by the stack.
        unsigned int m_LayerInsertIndex = 0; ///< Tracks where the next Layer should be inserted.
    };

}

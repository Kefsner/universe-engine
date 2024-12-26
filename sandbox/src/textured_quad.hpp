#pragma once

#include <universe.hpp>

class TexturedQuad : public Universe::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    Universe::Ref<Universe::VertexArray> m_VertexArray;
    uint32_t m_IndexBufferCount;

    // Necessary maintain the texture and shader as member variables
    // Because their destructors are called if they go out of scope in the OnAttach() method
    // and their destructor respectively deletes the resources from the GPU
    Universe::Ref<Universe::Texture2D> m_Texture;
    Universe::Ref<Universe::Shader> m_Shader;
};
#pragma once

#include <universe.hpp>

class RawTexturedQuad : public Universe::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    GLuint m_VertexArray;
};
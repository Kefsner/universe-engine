#pragma once

#include <universe.hpp>

class Renderer2DTexturedQuad : public Universe::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& e) override;

private:
    Universe::Ref<Universe::Texture2D> m_Texture;
};
#pragma once

#include <universe.hpp>

class Sandbox2D : public Universe::Layer
{
public:
    Sandbox2D() = default;
    ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;
};
#pragma once

#include <universe.hpp>

class Quad : public Universe::Layer
{
public:
    Quad() = default;
    ~Quad() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    Universe::Ref<Universe::VertexArray> m_VertexArray;
    uint32_t m_IndexBufferCount;
};
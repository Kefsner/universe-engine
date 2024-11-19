#include "universe.hpp"

class ExampleLayer : public Universe::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        UE_TRACE("ExampleLayer::Update");
    }

    void OnEvent(Universe::Event& event) override
    {
        UE_TRACE("{0}", event.ToString());
    }
};

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        UE_TRACE("Sandbox created!");
        PushLayer(new ExampleLayer());
    }
};

Universe::Application* Universe::CreateApplication()
{
    return new Sandbox();
}

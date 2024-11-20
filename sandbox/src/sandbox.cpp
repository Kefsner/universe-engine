#include "universe.hpp"

class ExampleLayer : public Universe::Layer
{
public:
    ExampleLayer()
    {
    }

    void OnUpdate() override
    {
        if (Universe::Input::IsKeyPressed(UE_KEY_TAB))
            UE_TRACE("Tab key is pressed!");

        Universe::Renderer::BeginScene();
        Universe::Renderer::Submit();
        Universe::Renderer::EndScene();
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
        PushLayer(new ExampleLayer());
    }
};

Universe::Application* Universe::CreateApplication()
{
    return new Sandbox();
}

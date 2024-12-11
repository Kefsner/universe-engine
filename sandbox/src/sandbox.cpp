#include "universe.hpp"
#include "sandbox2D.hpp"

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        PushLayer(new Sandbox2D());
    }
};

Universe::Application* Universe::CreateApplication()
{
    return new Sandbox();
}

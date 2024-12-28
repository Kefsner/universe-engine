#include <universe.hpp>
#include <universe/base/entrypoint.hpp>
#include "sandbox2D.hpp"

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        PushLayer(new Sandbox2D());
    }
};

Universe::Application* Universe::Create()
{
    return new Sandbox();
}
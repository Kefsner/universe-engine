#include <universe.hpp>
#include <universe/base/entrypoint.hpp>
#include "sandbox2D.hpp"
#include "raw_quad.hpp"

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        // PushLayer(new Sandbox2D());
        PushLayer(new RawQuad());
    }
};

Universe::Application* Universe::Create()
{
    return new Sandbox();
}
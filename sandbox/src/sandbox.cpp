#include <universe.hpp>
#include <universe/base/entrypoint.hpp>
#include "sandbox2D.hpp"
#include "raw_quad.hpp"
#include "raw_triangle.hpp"

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        // PushLayer(new Sandbox2D());
        // PushLayer(new RawTriangle());
        PushLayer(new RawQuad());
    }
};

Universe::Application* Universe::Create()
{
    return new Sandbox();
}
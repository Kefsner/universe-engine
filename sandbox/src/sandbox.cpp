#include <universe.hpp>
#include <universe/base/entrypoint.hpp>
#include "sandbox2D.hpp"
#include "raw_triangle.hpp"
#include "raw_quad.hpp"
#include "triangle.hpp"
#include "quad.hpp"
#include "renderer2D_quad.hpp"

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        // PushLayer(new Sandbox2D());
        // PushLayer(new RawTriangle());
        // PushLayer(new RawQuad());
        // PushLayer(new Triangle());
        // PushLayer(new Quad());
        PushLayer(new Renderer2DQuad());
    }
};

Universe::Application* Universe::Create()
{
    return new Sandbox();
}
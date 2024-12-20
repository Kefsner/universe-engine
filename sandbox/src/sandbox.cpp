#include "universe.hpp"
#include "universe/base/entrypoint.hpp"

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        // Initialize the application
    }

    ~Sandbox()
    {
        // Shutdown the application
    }
};

Universe::Application* Universe::Create()
{
    UE_CORE_INFO("Creating Sandbox");
    return new Sandbox();
}
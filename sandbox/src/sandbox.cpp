#include "universe.hpp"

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
    return new Sandbox();
}
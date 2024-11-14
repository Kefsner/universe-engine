#include "universe.h"

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        UE_TRACE("Sandbox created!");
    }
};

Universe::Application* Universe::CreateApplication()
{
    return new Sandbox();
}

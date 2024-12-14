#include "universe.hpp"

class Forge : public Universe::Application
{
public:
    Forge()
    {
        // Initialize the application
    }

    ~Forge()
    {
        // Shutdown the application
    }
};

Universe::Application* Universe::Create()
{
    return new Forge();
}
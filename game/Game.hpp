#include <universe.hpp>

namespace Universe
{
    class Game : public Application
    {
    public:
        Game();
        ~Game() override = default;
    };

    Application* Application::CreateApplication()
    {
        return new Game();
    }
}
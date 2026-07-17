#include <universe.hpp>

namespace Universe
{
    class Game : public Application
    {
    public:
        Game();
        ~Game() override = default;
    };

    class GameLayer : public Layer
    {
        void OnUpdate() override;
    };

    Application* Application::CreateApplication()
    {
        return new Game();
    }
}
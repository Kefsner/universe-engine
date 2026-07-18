#pragma once

#include <universe.hpp>
#include <universe/EntryPoint.hpp>

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
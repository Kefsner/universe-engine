#pragma once

#include <glm/glm.hpp>

#include "universe/inputs/key_codes.hpp"
#include "universe/inputs/mouse_codes.hpp"

namespace Universe
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}
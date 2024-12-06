#pragma once

#include <utility> // std::pair

namespace Universe {

    class Input
    {
    public:
        // Keyboard
        static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

        // Mouse
        static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
        static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;

    private:
        static Input* s_Instance;
    };
}
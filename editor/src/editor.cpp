#include "editor_layer.hpp"

namespace Universe {

    class UniverseEditor : public Application {
    public:
        UniverseEditor()
        {
            PushLayer(new EditorLayer());
        }

        ~UniverseEditor()
        {
        }
    };

    Application* CreateApplication()
    {
        return new UniverseEditor();
    }
}
#include "universe.hpp"
#include "universe/base/entrypoint.hpp"

#include "editor_layer.hpp"

namespace Universe
{
    class Forge : public Application
    {
    public:
        Forge()
        {
            PushLayer(new EditorLayer());
        }
    };

    Application* Create()
    {
        return new Forge();
    }
}
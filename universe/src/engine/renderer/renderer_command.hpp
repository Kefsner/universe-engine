#include "engine/core.hpp"
#include "engine/renderer/vertex_array.hpp"
#include "engine/renderer/renderer_api.hpp"

namespace Universe {

    class RendererCommand
    {
    public:
        static void DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            s_API->DrawIndexed(vertexArray);
        }

    private:
        static Ref<RendererAPI> s_API;
    };
}
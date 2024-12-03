#include "engine/core.hpp"
#include "engine/renderer/vertex_array.hpp"
#include "engine/renderer/renderer_api.hpp"

namespace Universe {

    class RendererCommand
    {
    public:
        static void Init()
        {
            s_API->Init();
        }
        
        static void DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            s_API->DrawIndexed(vertexArray);
        }

        static void Clear()
        {
            s_API->Clear();
        }

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_API->SetViewport(x, y, width, height);
        }

    private:
        static Ref<RendererAPI> s_API;
    };
}
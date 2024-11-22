#include "engine/renderer/opengl/opengl_renderer_api.hpp"
#include <glad/glad.h>

namespace Universe {
    
        void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            UE_TRACE("Elements were drawn");
        }
}
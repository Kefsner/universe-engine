#include "pch.hpp"

#include "universe/renderer/vertex_array.hpp"
#include "universe/renderer/opengl/opengl_vertex_array.hpp"

namespace Universe
{
    Ref<VertexArray> VertexArray::Create()
    {
        return CreateRef<OpenGLVertexArray>();
    }
}
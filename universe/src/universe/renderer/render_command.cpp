#include "pch.hpp"

#include "universe/renderer/render_command.hpp"

namespace Universe {

    Ref<RendererAPI> RenderCommand::s_API = RendererAPI::Create();

}
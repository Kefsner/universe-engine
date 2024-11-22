#include "pch.hpp"
#include "engine/renderer/renderer_command.hpp"

namespace Universe {

    Ref<RendererAPI> RendererCommand::s_API = RendererAPI::Create();

}
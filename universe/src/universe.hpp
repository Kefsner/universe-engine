#pragma once

#include "universe/base/base.hpp"
#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"

#include "universe/application.hpp"

#include "universe/layers/layer.hpp"
#include "universe/layers/layer_stack.hpp"

#include "universe/events/events.hpp"
#include "universe/events/application_events.hpp"
#include "universe/events/key_events.hpp"
#include "universe/events/mouse_events.hpp"

#include "universe/inputs/input.hpp"
#include "universe/inputs/key_codes.hpp"
#include "universe/inputs/mouse_codes.hpp"

#include "universe/renderer/renderer2D.hpp"
#include "universe/renderer/render_command.hpp"
#include "universe/renderer/buffer.hpp"
#include "universe/renderer/vertex_array.hpp"
#include "universe/renderer/shader.hpp"
#include "universe/renderer/texture.hpp"
#include "universe/renderer/opengl/opengl_buffer.hpp"
#include "universe/renderer/opengl/opengl_vertex_array.hpp"
#include "universe/renderer/opengl/opengl_shader.hpp"
#include "universe/renderer/opengl/opengl_texture.hpp"
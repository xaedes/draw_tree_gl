#pragma once

#include <string>
#include "gl_classes/shader.h"

namespace draw_tree_gl {
namespace shader {

    gl_classes::Shader defaultVertexShader();
    gl_classes::Shader defaultFragmentShader();

    std::string defaultVertexShaderCode();
    std::string defaultFragmentShaderCode();

}
}

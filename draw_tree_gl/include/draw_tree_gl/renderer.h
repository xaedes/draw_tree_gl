#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "transform_tree_glm/transform.h"
#include "draw_tree_gl/shader/default_program.h"

namespace draw_tree_gl {

    class Renderer
    {
    public:
        void setup();

        void draw(
            transform_tree_glm::Transform::pointer root, 
            glm::mat4 projection_view
        );
        DefaultProgram m_drawProgram;
        std::vector<glm::mat4> m_poseTrace;
    };

} // namespace draw_tree_gl

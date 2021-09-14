#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "transform_tree_glm/transform.h"
#include "draw_tree_gl/shader/default_program.h"

namespace draw_tree_gl {

    class Renderer
    {
    public:
        virtual ~Renderer();
        virtual void setup();

        virtual void draw(
            transform_tree_glm::Transform::pointer root, 
            glm::mat4 projection_view
        );
        
        shader::DefaultProgram& drawProgram() { return m_drawProgram; }
        std::vector<glm::mat4>& poseTrace() { return m_poseTrace; }

    protected:
        shader::DefaultProgram m_drawProgram;
        std::vector<glm::mat4> m_poseTrace;
    };

} // namespace draw_tree_gl

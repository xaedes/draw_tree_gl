#pragma once

#include <glm/glm.hpp>
#include "draw_tree_gl/drawing/drawable.h"
#include "gl_classes/host_device_buffer.h"

namespace draw_tree_gl {
namespace drawable {

    class Grid : public Drawable
    {
    public:
        using Drawable::Drawable;
        using pointer = Grid*;

        //template <typename... Args>
        //Grid(Args&&... args)
        //    : Drawable(std::forward< Args >( args )...)
        //{}

        virtual ~Grid() {}

        void setup() override
        {}
        void draw() override
        {}

    protected:
        gl_classes::HostDeviceBuffer<glm::vec3> m_vertexBuffer;
        gl_classes::HostDeviceBuffer<glm::vec3> m_colorBuffer;
        gl_classes::HostDeviceBuffer<glm::mat4> m_pvmBuffer;

    };

} // namespace drawable
} // namespace draw_tree_gl

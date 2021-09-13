#pragma once

#include <memory>
#include <iostream>
#include "transform_tree_glm/transform.h"
#include "chunky_mem/memory_pool_dynamic.h"

namespace draw_tree_gl {
namespace drawable {

    // template <typename memory_pool_t = MemoryPoolDynamic<>>
    class Drawable
    {
    public:
        using pointer = Drawable*;
        // using pointer = std::shared_ptr<Drawable>;

        // using Transform = ::transform_tree_glm::Transform<pointer>;
        // using TransformPtr = typename Transform::pointer;
        // using TransformRawPtr = typename Transform::raw_pointer;

        // using entity_manager_type = typename Transform::entity_manager_type;
        // using memory_pool_type = memory_pool_t;
        using memory_pool_type = ::chunky_mem::MemoryPoolDynamic<>;
        using Transform = ::transform_tree_glm::Transform;
        // template <typename drawable_type, typename... Args> 
        // static typename drawable_type::pointer 
        // Make(memory_pool_type& pool, Args&& ... args)
        // {
        //     drawable_type::pointer ptr(pool.create<drawable_type>(pool, std::forward< Args >(args)...));
        //     ptr->self = ptr;
        //     ptr->transform->object = ptr;
        //     return ptr;
        // }

        template <typename drawable_type, typename... Args> 
        static typename drawable_type::pointer 
        Instance(memory_pool_type& pool, const pointer& instanceOf, Args&& ... args)
        {
            return  pool.create<drawable_type>(pool, std::forward< Args >(args)..., instanceOf);
            // ptr->self = ptr;
            // ptr->transform->object = ptr;
            // ptr->transform->object->instanceOf = instanceOf;
            // return ptr;
        }

        // pointer self = nullptr;
        pointer instanceOf;
        bool customProgram = false;
        
        Drawable(memory_pool_type& pool, pointer instanceOf = nullptr)
            : Drawable(pool, nullptr, glm::mat4(1))
        {}
        Drawable(memory_pool_type& pool, const Transform::pointer& parent, const glm::mat4& localPose = glm::mat4(1), pointer instanceOf = nullptr)
            : transform(*pool.create<Transform>("", this, parent, localPose))
            , m_pool(&pool)
            , instanceOf(instanceOf)
        {}
        Drawable(memory_pool_type& pool, const std::string& name, const Transform::pointer& parent = nullptr, const glm::mat4& localPose = glm::mat4(1), pointer instanceOf = nullptr)
            : transform(*pool.create<Transform>(name, this, parent, localPose))
            , m_pool(&pool)
            , instanceOf(instanceOf)
        {}
        virtual ~Drawable() 
        {
            m_pool->destroy<Transform>(&transform);
        }

        virtual void setup() {}
        virtual void draw() {}
        virtual void draw(const glm::mat4&) {}
        virtual void drawInstance(const glm::mat4& pvm) {}
        virtual bool isInstancedRenderer() const { return false; }

        inline operator Transform::pointer()
        {
            return &transform;
        }

        template <typename DrawableType>
        inline DrawableType* as()
        {
            return static_cast<DrawableType*>(this);
        }

        template <typename DrawableType>
        inline const DrawableType* as() const
        {
            return static_cast<DrawableType*>(this);
        }

        // transform is allocated by Drawable vial memory pool.
        // We use reference instead of pointer, to ensure transform 
        // can never be nullptr.
        Transform& transform;

        inline bool enabled() const { return m_enabled; }
        inline bool& enabled() { return m_enabled; }
    protected:
        bool m_enabled = true;
        memory_pool_type* const m_pool;

    };

} // namespace drawable
} // namespace draw_tree_gl

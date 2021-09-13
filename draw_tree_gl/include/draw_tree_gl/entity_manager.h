#pragma once

#include "chunky_mem/memory_pool_dynamic.h"

namespace draw_tree_gl {

    template<
        typename idx_t = int,
        typename size_t = size_t
    >
    class EntityManager 
    {
    public:
        using idx_type = idx_t;
        using size_type = size_t;
        using memory_pool_type = chunky_mem::MemoryPoolDynamic<idx_type, size_type>;

        template<typename... Args>
        EntityManager(Args&&... args)
            : pool(std::forward< Args >(args)...)
        {}
        
        memory_pool_type pool;

        template<typename element_type, typename... Args>
        inline element_type* make(Args&&... args)
        {
            return element_type::Make(pool, std::forward< Args >(args)...);
        }

        bool destroy(void* ptr)
        {
            return pool.destroy(ptr);
        }
    };

} // namespace draw_tree_gl


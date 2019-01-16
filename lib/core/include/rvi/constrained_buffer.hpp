#pragma once

#include <deque>
#include <type_traits>

namespace rvi
{
    /**
     * @brief Size constrained buffer
     * 
     * @tparam T Buffer element type
     * @tparam max_sz Maximum number of elements allowed
     * @tparam std::enable_if_t<std::is_scalar_v<T>> Only scalar types allowed
     */
    template<typename T, size_t max_sz, typename = std::enable_if_t<std::is_scalar_v<T>>>
    class constrained_buffer
    {
    private:
        std::deque<T> buffer;

    public:
        
        ///Default constructor
        constexpr constrained_buffer() { }
        
        ///Maximum number of elements allowed 
        constexpr size_t max_size() const noexcept
        {
            return max_sz;
        }

        /**
         * @brief Push an element to the back of the buffer.
         * If the buffer size after insertion is bigger than the
         * stablished maximum size, the oldest element is removed.
         * 
         * @param val Element to append
         */
        void push_back(const T& val)
        {
            buffer.push_back(val);
            if(buffer.size() > max_sz)
            {
                buffer.pop_front();
            }
        }

        /**
         * @brief Push an element to the back of the buffer.
         * If the buffer size after insertion is bigger than the
         * stablished maximum size, the oldest element is removed.
         * 
         * @param val Element to append
         */
        void push_back(T&& val)
        {
            buffer.push_back(std::move(val));
            if(buffer.size() > max_sz)
            {
                buffer.pop_front();
            }
        }

        ///Remove all elements from the buffer
        void clear() noexcept
        {
            buffer.clear();
        }

        ///Buffer begin iterator
        auto begin() noexcept
        {
            return buffer.begin();
        }

        ///Buffer end iterator
        auto end() noexcept
        {
            return buffer.end();
        }

        ///Buffer reverse begin iterator
        auto rbegin() noexcept
        {
            return buffer.rbegin();
        }

        ///Buffer reverse end iterator
        auto rend() noexcept
        {
            return buffer.rend();
        }

        T operator[](size_t index)
        {
            return buffer[index];
        }
    };
}
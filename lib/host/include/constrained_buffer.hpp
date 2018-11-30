#pragma once

#include <deque>
#include <type_traits>

namespace rvi
{
    template<typename T, size_t max_sz, typename = std::enable_if_t<std::is_scalar_v<T>>>
    class constrained_buffer
    {
    private:
        std::deque<T> buffer;

    public:
        
        constexpr constrained_buffer() { }
       
        constexpr max_size() const noexcept
        {
            return max_sz;
        }

        void push_back(const T& val)
        {
            buffer.push_back(val);
            if(buffer.size() > max_size)
            {
                buffer.pop_front();
            }
        }

        void push_back(T&& val)
        {
            buffer.push_back(std::move(val));
            if(buffer.size() > max_size)
            {
                buffer.pop_front();
            }
        }

        void clear() noexcept
        {
            buffer.clear();
        }

        std::deque<T>::const_iterator begin() noexcept
        {
            return buffer.begin();
        }

        std::deque<T>::const_iterator end() noexcept
        {
            return buffer.end();
        }
    };
}
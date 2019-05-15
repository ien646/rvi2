#include <unordered_map>

#include <rvi/vframe.hpp>

#include <utility>

namespace rvi
{
    class vframe_container
    {
    private:
        typedef std::unordered_map<std::string, vframe> vframe_cnt_map_t;
        vframe_cnt_map_t _vframes;

    public:        
        void emplace(const std::string& str, vframe&& vf);
        vframe& at(const vframe_cnt_map_t::key_type& key);
        void erase(const vframe_cnt_map_t::key_type& key);
        void clear();
        size_t count(const vframe_cnt_map_t::key_type& key);
        vframe_cnt_map_t::iterator begin();
        vframe_cnt_map_t::iterator end();
    };
}
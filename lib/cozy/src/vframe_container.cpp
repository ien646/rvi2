#include <rvi/vframe_container.hpp>

namespace rvi
{
    void vframe_container::emplace(const std::string& str, vframe&& vf)
    {
        _vframes.emplace(str, std::move(vf));
    }

    vframe& vframe_container::at(const vframe_cnt_map_t::key_type& key)
    {
        return _vframes.at(key);
    }

    void vframe_container::erase(const vframe_cnt_map_t::key_type& key)
    {
        vframe& vf = _vframes.at(key);
        vf.destroy();
        _vframes.erase(key);
    }

    void vframe_container::clear()
    {
        _vframes.clear();
    }

    size_t vframe_container::count(const vframe_cnt_map_t::key_type& key)
    {
        return _vframes.count(key);
    }

    vframe_container::vframe_cnt_map_t::iterator vframe_container::begin()
    {
        return _vframes.begin();
    }

    vframe_container::vframe_cnt_map_t::iterator vframe_container::end()
    {
        return _vframes.end();
    }
}
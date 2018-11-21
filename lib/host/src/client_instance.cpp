#include "client_instance.hpp"

namespace rvi
{
    client_instance::client_instance(runtime* rptr)
        : _runtime_ptr(rptr)
    { }

    void client_instance::push_include(const std::string& inc_file)
    {
        data.include_stack.push_back(inc_file);
    }

    const std::string& client_instance::peek_current_include() const
    {
        return data.include_stack.back();
    }

    void client_instance::pop_include()
    {
        data.include_stack.pop_back();
    }

    void client_instance::mark_include_once()
    {
        data.include_once_ids.emplace(peek_current_include());
    }

    runtime* client_instance::runtime_ptr()
    {
        return _runtime_ptr;
    }
}
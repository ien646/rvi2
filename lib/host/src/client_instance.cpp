#include "client_instance.hpp"

#include <iostream>

#include "call_map.hpp"

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

    void client_instance::exec_definition(const std::string& dname)
    {
        if(data.definitions.count(dname) > 0)
        {
            auto def = data.definitions.at(dname);
            for(auto& inst : def)
            {
                auto& call = call_map.at(inst.cmd);
                call(*this, inst.args);
            }
        }
        else
        {
            std::cerr   << "Attempt to use undefined definition ["
                        << dname
                        << "]"
                        << std::endl;
        }
    }

    void client_instance::set_clickable_frame(
        frame* fptr, 
        const std::string& binding_name,
        const std::vector<std::string>& binding_args)
    {
        rectangle rect(fptr->transform().position, fptr->transform().scale);

        clickable_frame_data cfdata;
        cfdata.binding_name = binding_name;
        cfdata.binding_args = std::move(binding_args);
        cfdata.rect = rect;

        remove_clickable_frame(fptr);
        data.clickable_frames.emplace(fptr, cfdata);
    }

    void client_instance::remove_clickable_frame(frame* fptr)
    {
        if(data.clickable_frames.count(fptr) > 0)
        {
            data.clickable_frames.erase(fptr);
        }
    }
}
#include <rvi/client_instance.hpp>

#include <iostream>
#include <rvi/cmd_def_map.hpp>

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

    void client_instance::exec_macro(const std::string& mname)
    {
        if(data.macros.count(mname) > 0)
        {
            auto& def = data.macros.at(mname);
            for(auto& inst : def)
            {
                auto& cmd = cmd_def_map.at(inst.cmd);
                cmd(*this, inst.args);
            }
        }
        else
        {
            std::cerr   << "Attempt to execute undefined macro ["
                        << mname
                        << "]"
                        << std::endl;
        }
    }

    void client_instance::exec_binding(const std::string& bname, const arglist_t& args)
    {
        if(data.bindings.count(bname) > 0)
        {
            auto& binding = data.bindings.at(bname);
            arglist_t n_args = args;
            n_args.push_back(context.get_full_frame_name());
            binding(*this, n_args);
        }
        else
        {
            std::cerr   << "Attempt to execute undefined binding ["
                        << bname
                        << "]"
                        << std::endl;
        }
    }

    void client_instance::create_binding(const std::string& bname, runtime_cmd_t call)
    {
        if(data.bindings.count(bname) > 0)
        {
            data.bindings.erase(bname);
        }
        data.bindings.emplace(bname, call);
    }

    void client_instance::delete_binding(const std::string& bname)
    {
        data.bindings.erase(bname);
    }

    void client_instance::set_clickable_frame(
            frame* fptr, 
            const std::string& binding_name,
            float depth,
            const std::vector<std::string>& binding_args)
    {
        rectangle rect(fptr->transform().position, fptr->transform().scale);

        clickable_frame_data cfdata;
        cfdata.binding_name = binding_name;
        cfdata.binding_args = std::move(binding_args);
        cfdata.rect = rect;
        cfdata.depth_value = depth;
        cfdata.fptr = fptr;

        unset_clickable_frame(fptr);
        data.clickable_frames.emplace(fptr, cfdata);
    }

    void client_instance::unset_clickable_frame(frame* fptr)
    {
        if(data.clickable_frames.count(fptr) > 0)
        {
            data.clickable_frames.erase(fptr);
        }
    }

    void client_instance::user_click(vector2 pos)
    {
        std::vector<clickable_frame_data*> matches;
        for(auto& dt : data.clickable_frames)
        {
            auto& sdata = dt.second;
            if(sdata.rect.contains(pos))
            {
                if(matches.size() == 0)
                {
                    matches.push_back(&sdata);
                }
                else
                {
                    if(sdata.depth_value > matches.back()->depth_value)
                    {
                        continue;
                    }
                    else if(sdata.depth_value == matches.back()->depth_value)
                    {
                        matches.push_back(&sdata);
                    }
                    else //if (data.depth_value < matches.back().depth_value)
                    {
                        matches.clear();
                        matches.push_back(&sdata);
                    }
                }
            }
        }

        for(auto& match : matches)
        {
            auto& binding_name = match->binding_name;
            auto& frame_name = match->fptr->name();

            rvi::arglist_t args = match->binding_args;
            args.push_back(frame_name);
            
            exec_binding(binding_name, args);
        }
    }

    void client_instance::key_press(char kval)
    {
        data.key_buffer.push_back(kval);
    }
}
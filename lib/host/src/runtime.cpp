#include "runtime.hpp"

#include <map>
#include <stack>
#include <iostream>

#include <serializer.hpp>
#include <context_action_map.hpp>

#include "interpreter.hpp"
#include "std_bindings.hpp"

using namespace rvi::serialization;

namespace rvi::host
{
    struct orderable_path_container
    {
        std::vector<std::string> container;

        orderable_path_container(const std::vector<std::string>& ctn)
        {
            container = ctn;
        }

        orderable_path_container(std::vector<std::string>&& ctn)
        {
            container = std::move(ctn);
        }

        bool empty() const noexcept
        {
            return container.empty();
        }

        size_t size() const noexcept
        {
            return container.size();
        }

        bool operator>(const orderable_path_container& other) const
        {
            if(this->empty() && other.empty())
            {
                return false;
            }

            size_t minsz = std::min(this->size(), other.size());
            for(size_t i = 0; i < minsz; i++)
            {
                if(container[i] == other.container[i])
                    continue;
                else
                    return container[i] > other.container[i];
            }

            return this->size() > other.size();
        }

        bool operator<(const orderable_path_container& other) const
        {
            if(this->empty() && other.empty())
            {
                return false;
            }

            size_t minsz = std::min(this->size(), other.size());
            for(size_t i = 0; i < minsz; i++)
            {
                if(container[i] == other.container[i])
                    continue;
                else
                    return container[i] < other.container[i];
            }

            return this->size() < other.size();
        }

        std::string to_full_path(char sep) const
        {
            std::string result;
            if(container.empty())
            {
                return result;
            }
            result.append(container[0]);
            for(auto it = container.begin()+1; it != container.end(); it++)
            {
                result.push_back(sep);
                result.append(*it);
            }
            return result;
        }
    };

    cid_t runtime::create_client()
    {
        _clients.emplace(++_last_cid, client_context{});
        return _last_cid;
    }

    void runtime::start_client(cid_t cid, std::stringstream& program)
    {
        client_context& ctx = _clients.at(cid);
        auto stmt_col = interpreter::read(program);
        push_include("main.rpf");
        interpreter::run(*this, stmt_col, ctx);
        pop_include();
    }

    cmdlist_t runtime::get_update_commands(cid_t cid)
    {
        std::vector<std::vector<std::uint8_t>> result;

        client_context& ctx = _clients.at(cid);
        auto line_map = ctx.snapshot_diff_relative();

        std::map<orderable_path_container, std::vector<line>> paths_map;

        // Generate path collections
        for (const auto& data_pair : line_map)
        {
            const std::string str_path = data_pair.first;
            const char sep = client_context::FRAMEPATH_SEPARATOR;
            std::vector<std::string> path = str_split(str_path, sep);
            paths_map.emplace(orderable_path_container(std::move(path)), std::move(data_pair.second));
        }

        std::vector<std::string> path_stack;

        int idx = -1;
        for(auto& map_pair : paths_map)
        {
            idx++;
            int desired_stack_size = static_cast<int>(map_pair.first.size());
            auto& ccont = map_pair.first;
            if(path_stack.empty())
            {
                // Push frames
                for(const auto& seg : ccont.container)
                {
                    path_stack.push_back(seg);
                    result.push_back(serializer::select_frame(seg));
                    std::string path = 
                        orderable_path_container(path_stack).to_full_path(client_context::FRAMEPATH_SEPARATOR);
                    frame* fptr = ctx.find_frame(path);
                    result.push_back(serializer::set_transform(fptr->transform()));
                }

                // Push lines
                for(auto& ln : map_pair.second)
                {
                    result.push_back(serializer::draw_line(ln));
                }
            }
            else
            {
                int diffidx = 0;
                for(const auto& seg : ccont.container)
                {
                    if(path_stack.size() <= static_cast<size_t>(diffidx))
                    {
                        break;
                    }

                    if(seg == path_stack[diffidx])
                    {
                        diffidx++;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }

                // Release deeper frames
                int release_count = desired_stack_size - diffidx;
                if(static_cast<size_t>(diffidx) == path_stack.size())
                {
                    release_count = 0;
                }

                for(int i = 0; i < release_count; i++)
                {
                    result.push_back(serializer::release_frame());
                    path_stack.pop_back();
                }

                // Push frames from difference index onwards
                for(size_t i = diffidx; i < static_cast<size_t>(desired_stack_size); i++)
                {
                    std::string fname = ccont.container[i];
                    result.push_back(serializer::select_frame(fname));
                    path_stack.push_back(fname);
                    std::string path = 
                        orderable_path_container(path_stack).to_full_path(client_context::FRAMEPATH_SEPARATOR);
                    frame* fptr = ctx.find_frame(path);
                    result.push_back(serializer::set_transform(fptr->transform()));
                }

                // Push lines
                for(auto& ln : map_pair.second)
                {
                    result.push_back(serializer::draw_line(ln));
                }
            }
        }

        // Release final frame stack
        size_t pop_count = path_stack.size();
        for(size_t i = 0; i < pop_count; i++)
        {
            result.push_back(serializer::release_frame());
            path_stack.pop_back();
        }
        return result;
    }

    std::vector<line> runtime::get_flat_snapshot(cid_t cid)
    {
        auto& ctx = _clients.at(cid);
        return ctx.snapshot_full_flat();
    }

    void runtime::create_binding(const std::string& name, binding_t call)
    {
        if(_bindings.count(name) > 0)
        {
            std::cout << "Overwrite binding: [ " << name << " ]" << std::endl;
        }
        _bindings[name] = call;
    }

    void runtime::exec_binding(const std::string& name, client_context& ctx, const arglist_t& args)
    {
        if(_bindings.count(name) == 0)
        {
            std::cout << "[ RUNTIME ] Binding [ " << name << " ] not found!" << std::endl;
            return;
        }
        auto cb = _bindings.at(name);
        cb(ctx, args);
    }

    bool runtime::can_include(const std::string fname)
    {
        return _include_once_files.count(fname) == 0;
    }

    void runtime::mark_include_once()
    {
        _include_once_files.emplace(current_include());
    }

    void runtime::push_include(const std::string& fname)
    {
        _include_stack.push(fname);
    }

    const std::string& runtime::current_include()
    {
        return _include_stack.top();
    }

    void runtime::pop_include()
    {
        _include_stack.pop();
    }

    void runtime::init_std_bindings()
    {
        for(auto& entry : std_bindings_list)
        {
            create_binding(entry.name, entry.call);
        }
    }
}
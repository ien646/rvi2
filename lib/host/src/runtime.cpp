#include "runtime.hpp"

#include <std_fs.hpp>
#include <reader.hpp>

#include <fstream>

#include "cmd_def_map.hpp"
#include "std_bindings.hpp"

using namespace RVI_STD_FILESYSTEM_NAMESPACE;

namespace rvi
{
    runtime::runtime()
    {
        init_include_files(DATA_DIR);
    }

    int runtime::create_client()
    {
        int client_id = ++_client_id_accum;
        _client_instances.emplace(client_id, client_instance(this));
        std_bindings::init_std_bindings(_client_instances.at(client_id));
        return client_id;
    }

    void runtime::start_client(int client_id)
    {
        client_instance& client = _client_instances.at(client_id);

        std::ifstream ifs_prg(DATA_DIR + "/" + MAIN_PRGNAME);
        if(!ifs_prg)
        {
            throw std::runtime_error("Main program file not found!");
        }
        
        reader rdr(ifs_prg);
        auto stmt_col = rdr.process();
        for(auto& stmt : stmt_col)
        {
            auto& cmd = cmd_def_map.at(stmt.cmd);
            cmd(client, stmt.args);
        }
    }

    client_instance& runtime::get_instance(int inst_id)
    {
        if(_client_instances.count(inst_id) == 0)
        {
            throw std::invalid_argument("Invalid client instance id:" + std::to_string(inst_id));
        }
        return _client_instances.at(inst_id);
    }

    const std::string& runtime::get_include_path(const std::string& name)
    {
        return _include_filepaths[name];
    }

    bool runtime::is_include_cached(const std::string& name)
    {
        return (_include_cache.count(name) > 0);
    }

    const std::vector<parsed_stmt>& runtime::get_cached_include(const std::string& name)
    {
        return _include_cache.at(name);
    }

    void runtime::cache_parsed_include(const std::string& name, std::vector<parsed_stmt> instructions)
    {
        _include_cache[name] = instructions;
    }

    void runtime::init_include_files(const std::string& dir)
    {
        #if !(defined RVI_HAS_STD_FILESYSTEM)
            #error Current version of RVI2 requires std::filesystem support!
        #endif        
        
        _include_dir = dir;

        for(auto& file : recursive_directory_iterator(_include_dir))
        {
            std::string path = file.path().string();
            std::string iid = file.path().filename().string();
            _include_filepaths.emplace(iid, path);
        }
    }

    std::vector<line> runtime::snapshot_full_flat(int client_id)
    {
        client_instance& client = _client_instances.at(client_id);
        return client.context.snapshot_full_flat();
    }

    relative_snapshot runtime::snapshot_full_relative(int client_id)
    {
        client_instance& client = _client_instances.at(client_id);
        return client.context.snapshot_full_relative();
    }

    relative_snapshot runtime::snapshot_diff_relative(int client_id)
    {
        client_instance& client = _client_instances.at(client_id);
        return client.context.snapshot_diff_relative();
    }
}
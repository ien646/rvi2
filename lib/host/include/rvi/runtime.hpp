#pragma once

#include <unordered_map>
#include <string>

#include <rvi/client_instance.hpp>
#include <rvi/parsed_stmt.hpp>

namespace rvi
{
    class runtime
    {
    private:
        const std::string DATA_DIR = "data";
        const std::string MAIN_PRGNAME = "main.rpf";

        int _client_id_accum = 0;

        std::string _include_dir;
        std::unordered_map<int, client_instance> _client_instances;
        std::unordered_map<std::string, std::string> _include_filepaths;
        std::unordered_map<std::string, std::vector<parsed_stmt>> _include_cache;
        
    public:
        runtime();

        [[nodiscard]] int create_client();

        void start_client(int client_id);

        client_instance& get_instance(
            int inst_id);
        
        const std::string& get_include_path(
            const std::string& name);
        
        bool is_include_cached(
            const std::string& name);
        
        const std::vector<parsed_stmt>& get_cached_include(
            const std::string& name);
        
        void cache_parsed_include(
            const std::string& name, 
            std::vector<parsed_stmt> instructions);

        std::vector<line> snapshot_full_flat(int client_id);
        relative_snapshot snapshot_full_relative(int client_id);
        relative_snapshot snapshot_diff_relative(int client_id);

    private:
        void init_include_files(const std::string& dir);
    };
}
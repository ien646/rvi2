#include "data_reader.hpp"

#ifdef RVI_COMPILER_MSVC

#include <filesystem>
#include <fstream>
    namespace stdfs = std::filesystem;
#else
    #include <experimental/filesystem>
    namespace stdfs = std::experimental::filesystem;
#endif

const static std::string EXT_RUNTIME = { ".rpf" };
const static std::string EXT_INIT = { ".rpd" };

using rec_dir_it = stdfs::recursive_directory_iterator;
using std_dir_it = stdfs::directory_iterator;

using namespace std;

namespace rvi::host
{
    static bool data_reader_cache_built = false;
    static std::unordered_map<std::string, std::string> data_reader_cache_init;
    static std::unordered_map<std::string, std::string> data_reader_cache_runtime;

    template<typename T_DIR_ITER>
    static void enum_data_files_g_it(data_reader_result& result, string_view dir)
    {    
        for (auto& entry : T_DIR_ITER(dir))
        {
            string ext = entry.path().extension().string();
            if (ext == EXT_RUNTIME)
            {
                result.runtime_files.push_back(entry.path().string());                
            }
            else if (ext == EXT_INIT)
            {
                result.init_files.push_back(entry.path().string());
            }
        }
    }

    data_reader_result data_reader::enum_data_files(string_view dir, bool recursive)
    {
        data_reader_result result;

        if(!data_reader_cache_built)
        {
            if (recursive)
            {
                enum_data_files_g_it<rec_dir_it>(result, dir);
            }
            else
            {
                enum_data_files_g_it<std_dir_it>(result, dir);
            }

            // cache init files
            for(auto& entry : result.init_files)
            {
                std::string fname = stdfs::path(entry).filename().string();
                data_reader_cache_init.emplace(fname, entry);
            }

            // cache runtime files
            for(auto& entry : result.runtime_files)
            {
                std::string fname = stdfs::path(entry).filename().string();
                data_reader_cache_runtime.emplace(fname, entry);
            }
            data_reader_cache_built = true;
        }
        else
        {
            for(auto& entry : data_reader_cache_init)
            {
                result.init_files.push_back(entry.second);
            }

            for(auto& entry : data_reader_cache_runtime)
            {
                result.runtime_files.push_back(entry.second);
            }
        }

        return result;
    }

    std::string data_reader::get_include_text(const std::string& id)
    {
        if(!data_reader_cache_built)
        {
            DISCARD_RESULT enum_data_files("data", true);
        }

        if(data_reader_cache_init.count(id) > 0)
        {
            std::stringstream ss;
            std::ifstream ifs(data_reader_cache_init[id]);
            ss << ifs.rdbuf();
            return ss.str();
        }
        else if(data_reader_cache_runtime.count(id) > 0)
        {
            std::stringstream ss;
            std::ifstream ifs(data_reader_cache_runtime[id]);
            ss << ifs.rdbuf();
            return ss.str();
        }
        else
        {
            return std::string();
        }
    }
}
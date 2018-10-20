#include "data_reader.hpp"

#ifdef RVI_COMPILER_MSVC

#include <filesystem>
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

    if (recursive)
    {
        enum_data_files_g_it<rec_dir_it>(result, dir);
    }
    else
    {
        enum_data_files_g_it<std_dir_it>(result, dir);
    }
    return result;
}





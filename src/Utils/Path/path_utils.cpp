#include "path_utils.hpp"

/* Returns the assets folder path. */
std::string get_executable_path()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring wstr(buffer);
    
    // Convert wstring to string
    std::string path(wstr.begin(), wstr.end());

    std::string::size_type pos = path.find_last_of("\\/");
    std::string exe_dir = path.substr(0, pos);
    std::string assets_dir = exe_dir + "/../assets/";
    
    return assets_dir;
}
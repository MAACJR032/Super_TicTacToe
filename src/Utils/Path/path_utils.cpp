#include "path_utils.hpp"

std::string get_executable_path()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring wstr(buffer);
    
    // Convert wstring to string
    std::string path(wstr.begin(), wstr.end());

    std::string::size_type pos = path.find_last_of("\\/");
    std::string exeDir = path.substr(0, pos);
    std::string assetsDir = exeDir + "/../assets/"; // Get the assets folder path
    return assetsDir;
}
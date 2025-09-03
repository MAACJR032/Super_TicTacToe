#include "path_utils.hpp"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <limits.h>
    #include <stdlib.h>
#endif

/* Returns the assets folder path. */
std::string get_assets_path()
{
#ifdef _WIN32
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring wstr(buffer);
    
    // Convert wstring to string
    std::string path(wstr.begin(), wstr.end());

    std::string::size_type pos = path.find_last_of("\\/");
    std::string exe_dir        = path.substr(0, pos);
    std::string assets_dir     = exe_dir + "/../assets/";
    
    return assets_dir;
#else
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    
    if (len != -1)
    {
        buffer[len] = '\0';
        std::string path(buffer);

        std::string::size_type pos = path.find_last_of("/");
        std::string exe_dir        = path.substr(0, pos);
        std::string assets_dir     = exe_dir + "/../assets/";

        return assets_dir;
    }

    return "";

#endif
}
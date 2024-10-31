#include "logger.hpp"

void logger::Log(const std::string &prefix, const std::string &format)
{
    // Get the current system time
    auto now = std::chrono::system_clock::now();
    std::time_t curr_time = std::chrono::system_clock::to_time_t(now);
    
    // Convert to a string and remove the newline
    std::string time_str = std::ctime(&curr_time);
    time_str.pop_back();

    std::cout << prefix << time_str << " " << format << '\n';
}

logger::logger()
{
}

void logger::Debug(const std::string &format)
{
    Log("Debug: ", format);
}

void logger::Info(const std::string &format)
{
    Log("Info: ", format);
}

void logger::Warning(const std::string &format)
{
    Log("Warning: ", format);
}

void logger::Error(const std::string &format)
{
    Log("Error: ", format);
}
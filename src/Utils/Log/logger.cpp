#include "logger.hpp"

std::string Logger::get_current_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t curr_time = std::chrono::system_clock::to_time_t(now);
    std::string time_str = std::ctime(&curr_time);

    if (!time_str.empty() && time_str.back() == '\n')
        time_str.pop_back();

    return time_str;
}

void Logger::Log(const std::string &prefix, const std::string &msg)
{
    std::cout << prefix << get_current_time() << " " << msg << '\n';
}

void Logger::Debug(const std::string &msg)
{
    Log("Debug: ", msg);
}

void Logger::Info(const std::string &msg)
{
    Log("Info: ", msg);
}

void Logger::Warning(const std::string &msg)
{
    Log("Warning: ", msg);
}

void Logger::Error(const std::string &msg)
{
    Log("Error: ", msg);
}
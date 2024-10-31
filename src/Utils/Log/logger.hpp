#pragma once

#include <iostream>
#include <string>
#include <chrono>

class logger
{
    private:
        void Log(const std::string &prefix, const std::string &format);

        template <typename ...Args>
        void Logf(const std::string &prefix, const std::string &format, Args&&... args)
        {
            // Allocate a buffer large enough to hold the formatted string
            int size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Add 1 for the null terminator
            if (size <= 0)
            { 
                std::cerr << "Error during formatting\n";
                return;
            }

            std::string buffer(size, '\0');
            std::snprintf(&buffer[0], size, format.c_str(), std::forward<Args>(args)...);

            // Get the current system time
            auto now = std::chrono::system_clock::now();
            std::time_t curr_time = std::chrono::system_clock::to_time_t(now);
            
            // Convert to a string and remove the newline
            std::string time_str = std::ctime(&curr_time);
            time_str.pop_back();

            std::cout << prefix << time_str << " " << buffer << '\n';
        }
        
    public:
        logger();

        void Debug(const std::string &format);
        void Info(const std::string &format);
        void Warning(const std::string &format);
        void Error(const std::string &format);

        template <typename ...Args>
        void Debugf(const std::string &format, Args&& ...args)
        {
            Logf("Debug: ", format, std::forward<Args>(args)...);
        }

        template <typename ...Args>
        void Infof(const std::string &format, Args&& ...args)
        {
            Logf("Info: ", format, std::forward<Args>(args)...);
        }

        template <typename ...Args>
        void Warningf(const std::string &format, Args&& ...args)
        {
            Logf("Warning: ", format, std::forward<Args>(args)...);
        }

        template <typename ...Args>
        void Errorf(const std::string &format, Args&& ...args)
        {
            Logf("Error: ", format, std::forward<Args>(args)...);
        }
};
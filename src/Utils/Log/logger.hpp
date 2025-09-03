#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <vector>

#ifdef DEBUG
    #define LOG_DEBUG(msg) Logger::get().Debug(msg)
    #define LOG_INFO(msg) Logger::get().Info(msg)
    #define LOG_WARNING(msg) Logger::get().Warning(msg)
    #define LOG_ERROR(msg) Logger::get().Error(msg)

    #define LOG_DEBUGF(fmt, ...) Logger::get().Debugf(fmt, __VA_ARGS__)
    #define LOG_INFOF(fmt, ...) Logger::get().Infof(fmt, __VA_ARGS__)
    #define LOG_WARNINGF(fmt, ...) Logger::get().Warningf(fmt, __VA_ARGS__)
    #define LOG_ERRORF(fmt, ...) Logger::get().Errorf(fmt, __VA_ARGS__)
#else
    // When not debugging, remove log calls from compilation (zero cost)
    #define LOG_DEBUG(msg) do {} while(0)
    #define LOG_INFO(msg) do {} while(0)
    #define LOG_WARNING(msg) do {} while(0)
    #define LOG_ERROR(msg) do {} while(0)

    #define LOG_DEBUGF(fmt, ...) do {} while(0)
    #define LOG_INFOF(fmt, ...) do {} while(0)
    #define LOG_WARNINGF(fmt, ...) do {} while(0)
    #define LOG_ERRORF(fmt, ...) do {} while(0)
#endif

class Logger
{
    private:
        Logger()  = default;
        ~Logger() = default;

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static std::string get_current_time();

        void Log(const std::string &prefix, const std::string &format);

        template <typename ...Args>
        void Logf(const std::string &prefix, const std::string &format, Args&&... args)
        {
            if constexpr (sizeof...(args) == 0)
            {
                Error("Logf requires at least one formatting argument");
            }
            else
            {
                // Allocate a buffer large enough to hold the formatted string
                int size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Add 1 for the null terminator
                if (size < 0)
                { 
                    Error("snprintf failed due to an invalid format string or internal encoding error");
                    return;
                }

                std::vector<char> buffer(size);
                std::snprintf(buffer.data(), size, format.c_str(), std::forward<Args>(args)...);

                Log(prefix, std::string(buffer.data()));
            }
        }
        
    public:
        static Logger& get()
        {
            static Logger instance;
            return instance;
        }

        void Debug(const std::string &msg);
        void Info(const std::string &msg);
        void Warning(const std::string &msg);
        void Error(const std::string &msg);

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
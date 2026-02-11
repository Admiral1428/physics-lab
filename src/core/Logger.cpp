#include "core/Logger.hpp"
#include <iostream>
#include <ctime>

std::ofstream Logger::logfile;

void Logger::init(const std::string& filename) 
{
    logfile.open(filename, std::ios::out | std::ios::app);
}

void Logger::write(const std::string& level, const std::string& msg) 
{
    // Timestamp
    std::time_t now = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    std::string formatted = "[" + std::string(buf) + "] [" + level + "] " + msg;

    // Console
    if (level == "ERROR")
        std::cerr << formatted << std::endl;
    else
        std::cout << formatted << std::endl;

    // File
    if (logfile.is_open())
        logfile << formatted << std::endl;
}

void Logger::info(const std::string& msg)
{ 
    write("INFO", msg); 
}

void Logger::warn(const std::string& msg)  
{
    write("WARN", msg);
}

void Logger::error(const std::string& msg)
{
    write("ERROR", msg);
}

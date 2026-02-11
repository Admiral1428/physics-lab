#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>

class Logger {
public:
    static void init(const std::string& filename);
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);

private:
    static std::ofstream logfile;
    static void write(const std::string& level, const std::string& msg);
};

#endif

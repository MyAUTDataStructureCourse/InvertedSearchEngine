#ifndef LOG_H
#define LOG_H

#include <string>
#include <vector>

class Log
{
    static std::vector<std::string> logs;
public:


    static void error(std::string error);

    ~Log();
};

#endif // LOG_H

#include "log.h"
#include <fstream>

std::vector<std::string> Log::logs;

void Log::error(std::__cxx11::string error)
{
    logs.push_back("error : " + error);
}
Log::~Log()
{

    std::ofstream file_writer("/home/ahmad/inverted_search_engine_logs.log");

    file_writer << "Logs : ";
    for(int i = 0; i < logs.size(); i++)
    {
        file_writer << logs[i] << std::endl;
    }

    file_writer.close();
}

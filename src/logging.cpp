#include "logging.h"
#include <time.h>

using namespace smtm;

Logger::Logger(std::string filename, LogLevel level)
{
    _filename = filename;
    _fs = std::ofstream();

    _level = level;
}

void Logger::Error(std::string msg)
{
    _WriteLog("[ERROR] " + msg, llError);
}

void Logger::Warning(std::string msg)
{
    _WriteLog("[WARNING] " + msg, llWarning);
}

void Logger::Info(std::string msg)
{
    _WriteLog("[INFO] " + msg, llInfo);
}

void Logger::Debug(std::string msg)
{
    _WriteLog("[DEBUG] " + msg, llDebug);
}

void Logger::_WriteLog(std::string msg, LogLevel level)
{
    const time_t t = time(NULL);
    struct tm lt;
    char buff[256];

    if (level > _level) {
        return;
    }

    localtime_s(&lt, &t);

    sprintf_s(buff, 256, "[%d-%d-%d %d:%d:%d] ", lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday, lt.tm_hour, lt.tm_min, lt.tm_sec);

    _fs.open(_filename, std::ios_base::app);
    _fs << buff << msg.c_str() << std::endl;
    _fs.close();
}
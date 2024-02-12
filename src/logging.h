#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <fstream>
#include <ios>

namespace smtm {
    enum LogLevel {
        llNone = 0,
        llError, llWarning, llInfo, llDebug
    };

    class Logger {
    public:
        Logger(std::string msg, LogLevel level);
        void Error(std::string msg);
        void Warning(std::string msg);
        void Info(std::string msg);
        void Debug(std::string msg);
    private:
        std::string _filename;
        std::ofstream _fs;
        LogLevel _level;

        void _WriteLog(std::string msg, LogLevel level);
    };
}

#endif // __LOGGING_H__
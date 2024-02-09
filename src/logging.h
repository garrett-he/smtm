/**
 * Copyright (C) 2019 Garrett HE <garrett.he@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
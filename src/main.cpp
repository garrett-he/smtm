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

#include <Windows.h>
#include <stdio.h>
#include "getopt.h"
#include "inih.h"
#include "logging.h"

#define OPTS_SHORT_STRING "h"

static const struct option opt_define[] = {
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
};

static void display_help(FILE* fp) {
    fprintf(fp, "usage: smtm [FILE]\n");
    fprintf(fp, "Lua engine to let you run scripts to cheat/mod in games.\n");
}

int main(int argc, char** argv) {
    std::string execName;
    std::string baseDir;
    smtm::Logger* logger;
    TCHAR path[MAX_PATH];
    INIReader* configReader;

    if (argc < 2) {
        display_help(stderr);
        return -1;
    }

    struct {
        std::string LogDir;
        smtm::LogLevel LogLevel;
    } config;

    do {
        optopt = getopt_long(argc, argv, OPTS_SHORT_STRING, opt_define, &optind);

        switch (optopt) {
        case 'h':
            display_help(stdout);
            return 0;
        default:
            /* You won't actually get here */
            break;
        }
    } while (optopt != -1);

    if (!::GetModuleFileName(NULL, path, MAX_PATH)) {
        throw std::exception("Cannot get filename of smtm.");
    }

    execName = std::string(path);
    baseDir = execName.substr(0, execName.find_last_of('\\'));

    configReader = new INIReader(baseDir + "\\smtm.ini");

    config.LogDir = configReader->Get("smtm", "log_dir", baseDir);
    config.LogLevel = smtm::LogLevel(configReader->GetInteger("smtm", "log_level", smtm::llInfo));

    delete configReader;

    logger = new smtm::Logger(config.LogDir + "\\smtm.log", config.LogLevel);

    delete logger;

    return 0;
}

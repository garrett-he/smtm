#include <Windows.h>
#include <stdio.h>
#include "getopt.h"
#include "inih.h"
#include "logging.h"
#include "lua_engine.h"

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
    smtm::LuaEngine* engine;
    std::string scriptPath;

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

    // Read configurations
    configReader = new INIReader(baseDir + "\\smtm.ini");

    config.LogDir = configReader->Get("smtm", "log_dir", baseDir);
    config.LogLevel = smtm::LogLevel(configReader->GetInteger("smtm", "log_level", smtm::llInfo));

    delete configReader;

    // Start Lua engine
    logger = new smtm::Logger(config.LogDir + "\\smtm.log", config.LogLevel);
    logger->Debug("Starting Lua engine");

    engine = new smtm::LuaEngine();

    scriptPath = std::string(argv[optind]);

    try {
        logger->Info("Run script: " + scriptPath);
        engine->RunScript(scriptPath);
    }
    catch (std::exception &e) {
        logger->Error(std::string(e.what()));
        fprintf(stderr, "error: %s\n", e.what());

        return -1;
    }

    logger->Debug("Stopping Lua engine");

    delete engine;
    delete logger;

    return 0;
}

#include "cli.hpp"
#include "system.hpp"
#include "package.hpp"
#include "dev.hpp"
#include "api.hpp"
#include "file.hpp"
#include "config.hpp"
#include "plugin.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#ifdef _WIN32
    #define OS_NAME "Windows"
#elif __APPLE__
    #define OS_NAME "macOS"
#else
    #define OS_NAME "Linux"
#endif

void printHelp() {
    std::cout << "Flux CLI Tool\n";
    std::cout << "Usage: flux [command]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  --help      Show this help message\n";
    std::cout << "  install     Install packages\n";
    std::cout << "  process     Manage processes\n";
    std::cout << "  api         Make API calls\n";
    std::cout << "  file        File operations\n";
    std::cout << "  config      Configuration management\n";
    std::cout << "  plugin      Plugin management\n";
    std::cout << "  system      System operations\n";
    std::cout << "  dev         Development utilities\n";
}

int CLI::handle(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 0;
    }

    std::string command = argv[1];

    if (command == "--help") {
        printHelp();
        return 0;
    }

    if (command == "install") {
        if (argc < 3) {
            std::cerr << "Usage: flux install <package_name>" << std::endl;
            return 1;
        }
        std::string packageName = argv[2];
        return Package::install(packageName);
    }

    if (command == "process") {
        if (argc < 3) {
            std::cerr << "Usage: flux process <subcommand> [args]" << std::endl;
            std::cerr << "Subcommands: kill <port>, find <port>, start <cmd>" << std::endl;
            return 1;
        }
        std::string subcommand = argv[2];

        if (subcommand == "kill" && argc >= 4) {
            int port = std::stoi(argv[3]);
            return System::killProcessByPort(port);
        } else if (subcommand == "find" && argc >= 4) {
            int port = std::stoi(argv[3]);
            return System::findProcessByPort(port);
        } else if (subcommand == "start" && argc >= 4) {
            std::string cmd = argv[3];
            return System::startProcess(cmd);
        } else {
            std::cerr << "Unknown process subcommand: " << subcommand << std::endl;
            return 1;
        }
    }

    if (command == "api") {
        if (argc < 4) {
            std::cerr << "Usage: flux api <method> <url>" << std::endl;
            std::cerr << "Methods: GET, POST" << std::endl;
            return 1;
        }
        std::string method = argv[2];
        std::string url = argv[3];
        if (method == "GET") {
            return Api::get(url);
        } else if (method == "POST" && argc >= 5) {
            std::string data = argv[4];
            return Api::post(url, data);
        } else {
            std::cerr << "Unsupported method or missing data for POST" << std::endl;
            return 1;
        }
    }

    if (command == "file") {
        if (argc < 3) {
            std::cerr << "Usage: flux file <subcommand> [args]" << std::endl;
            std::cerr << "Subcommands: find <path>, copy <src> <dst>, move <src> <dst>, rename <old> <new>" << std::endl;
            return 1;
        }
        std::string subcommand = argv[2];

        if (subcommand == "find" && argc >= 4) {
            std::string path = argv[3];
            return File::find(path);
        } else if (subcommand == "copy" && argc >= 5) {
            std::string src = argv[3];
            std::string dst = argv[4];
            return File::copy(src, dst);
        } else if (subcommand == "move" && argc >= 5) {
            std::string src = argv[3];
            std::string dst = argv[4];
            return File::move(src, dst);
        } else if (subcommand == "rename" && argc >= 5) {
            std::string old = argv[3];
            std::string new_name = argv[4];
            return File::rename(old, new_name);
        } else {
            std::cerr << "Unknown file subcommand: " << subcommand << std::endl;
            return 1;
        }
    }

    if (command == "config") {
        if (argc < 3) {
            std::cerr << "Usage: flux config <subcommand> [args]" << std::endl;
            std::cerr << "Subcommands: get <key>, set <key> <value>" << std::endl;
            return 1;
        }
        std::string subcommand = argv[2];

        if (subcommand == "get" && argc >= 4) {
            std::string key = argv[3];
            return Config::get(key);
        } else if (subcommand == "set" && argc >= 5) {
            std::string key = argv[3];
            std::string value = argv[4];
            return Config::set(key, value);
        } else {
            std::cerr << "Unknown config subcommand: " << subcommand << std::endl;
            return 1;
        }
    }

    if (command == "plugin") {
        if (argc < 3) {
            std::cerr << "Usage: flux plugin <subcommand> [args]" << std::endl;
            std::cerr << "Subcommands: list, install <path>, run <name>" << std::endl;
            return 1;
        }
        std::string subcommand = argv[2];

        if (subcommand == "list") {
            return Plugin::list();
        } else if (subcommand == "install" && argc >= 4) {
            std::string path = argv[3];
            return Plugin::install(path);
        } else if (subcommand == "run" && argc >= 4) {
            std::string name = argv[3];
            return Plugin::run(name);
        } else {
            std::cerr << "Unknown plugin subcommand: " << subcommand << std::endl;
            return 1;
        }
    }

    if (command == "system") {
        if (argc < 3) {
            std::cerr << "Usage: flux system <subcommand> [args]" << std::endl;
            std::cerr << "Subcommands: monitor, cleanup, update" << std::endl;
            return 1;
        }
        std::string subcommand = argv[2];

        if (subcommand == "monitor") {
            return System::monitor();
        } else if (subcommand == "cleanup") {
            return System::cleanup();
        } else if (subcommand == "update") {
            return System::update();
        } else {
            std::cerr << "Unknown system subcommand: " << subcommand << std::endl;
            return 1;
        }
    }

    if (command == "dev") {
        if (argc < 3) {
            std::cerr << "Usage: flux dev <subcommand> [args]" << std::endl;
            std::cerr << "Subcommands: init <name>, run <path>, build <path>" << std::endl;
            return 1;
        }
        std::string subcommand = argv[2];

        if (subcommand == "init" && argc >= 4) {
            std::string name = argv[3];
            return Dev::init(name);
        } else if (subcommand == "run" && argc >= 4) {
            std::string path = argv[3];
            return Dev::run(path);
        } else if (subcommand == "build" && argc >= 4) {
            std::string path = argv[3];
            return Dev::build(path);
        } else {
            std::cerr << "Unknown dev subcommand: " << subcommand << std::endl;
            return 1;
        }
    }

    std::cerr << "Unknown command: " << command << std::endl;
    printHelp();
    return 1;
}

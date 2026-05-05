#include "system.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/stat.h>
    #include <unistd.h>
#endif

int System::killProcessByPort(int port) {
#ifdef _WIN32
    std::string cmd = "netstat -ano | findstr :" + std::to_string(port);
    std::string result = Utils::executeCommand(cmd);
    std::cout << "Processes on port " << port << ":\n" << result << std::endl;

    // Extract PID from result and kill process
    // For simplicity, we'll just show the process info
    return 0;
#else
    std::string cmd = "lsof -i:" + std::to_string(port);
    std::string result = Utils::executeCommand(cmd);
    std::cout << "Processes on port " << port << ":\n" << result << std::endl;

    // Extract PID from result and kill process
    // Example: lsof -ti:8080 | xargs kill -9
    std::string pid_cmd = "lsof -ti:" + std::to_string(port) + " | xargs kill -9 2>/dev/null";
    Utils::executeCommand(pid_cmd);
    std::cout << "Killed processes on port " << port << std::endl;
    return 0;
#endif
}

int System::findProcessByPort(int port) {
#ifdef _WIN32
    std::string cmd = "netstat -ano | findstr :" + std::to_string(port);
#else
    std::string cmd = "lsof -i:" + std::to_string(port);
#endif
    std::string result = Utils::executeCommand(cmd);
    std::cout << "Processes on port " << port << ":\n" << result << std::endl;
    return 0;
}

int System::startProcess(const std::string& command) {
    std::cout << "Starting process: " << command << std::endl;
    int result = std::system(command.c_str());
    return result;
}

int System::monitor() {
#ifdef _WIN32
    std::string cmd = "wmic cpu get loadpercentage";
    std::string cpu_result = Utils::executeCommand(cmd);
    std::cout << "CPU Usage:\n" << cpu_result << std::endl;

    cmd = "wmic os get freephysicalmemory,totalvisiblememorysize";
    std::string ram_result = Utils::executeCommand(cmd);
    std::cout << "RAM Info:\n" << ram_result << std::endl;
#else
    std::string cmd = "top -bn1 | head -20";
    std::string top_result = Utils::executeCommand(cmd);
    std::cout << "Top processes:\n" << top_result << std::endl;

    cmd = "free -h";
    std::string free_result = Utils::executeCommand(cmd);
    std::cout << "Memory usage:\n" << free_result << std::endl;

    cmd = "df -h";
    std::string disk_result = Utils::executeCommand(cmd);
    std::cout << "Disk usage:\n" << disk_result << std::endl;
#endif
    return 0;
}

int System::cleanup() {
#ifdef _WIN32
    std::cout << "Cleaning up system cache..." << std::endl;
    std::string cmd = "cleanmgr /sagerun:1 2>nul || echo Windows cleanup not available without admin rights";
#else
    std::cout << "Cleaning up system cache..." << std::endl;
    std::string cmd = "sudo rm -rf /tmp/* ~/.cache/* 2>/dev/null; echo 'Cache cleaned'";
#endif
    std::string result = Utils::executeCommand(cmd);
    std::cout << result << std::endl;
    return 0;
}

int System::update() {
#ifdef _WIN32
    std::cout << "System update not implemented for Windows" << std::endl;
    return 0;
#elif defined(__APPLE__)
    std::string cmd = "brew upgrade 2>/dev/null || echo 'Homebrew not found'";
    std::cout << "Updating system packages..." << std::endl;
    std::string result = Utils::executeCommand(cmd);
    std::cout << result << std::endl;
#else
    std::string cmd = "sudo apt-get update && sudo apt-get upgrade -y 2>/dev/null || "
                      "sudo pacman -Syu --noconfirm 2>/dev/null || "
                      "echo 'No supported package manager found'";
    std::cout << "Updating system packages..." << std::endl;
    std::string result = Utils::executeCommand(cmd);
    std::cout << result << std::endl;
#endif
    return 0;
}

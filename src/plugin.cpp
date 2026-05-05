#include "plugin.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string getPluginsPath() {
    const char* home = std::getenv("HOME");
    if (!home) {
        std::cerr << "HOME environment variable not set" << std::endl;
        return "";
    }
    return std::string(home) + "/.config/flux/plugins/";
}

int Plugin::list() {
    std::string pluginsPath = getPluginsPath();
    if (pluginsPath.empty()) return 1;

    Utils::executeCommand("mkdir -p " + pluginsPath);

    std::cout << "Available plugins:" << std::endl;
    try {
        for (const auto& entry : fs::directory_iterator(pluginsPath)) {
            if (entry.is_regular_file()) {
                std::cout << "  - " << entry.path().filename() << std::endl;
            }
        }
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error reading plugins directory: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

int Plugin::install(const std::string& path) {
    std::string pluginsPath = getPluginsPath();
    if (pluginsPath.empty()) return 1;

    Utils::executeCommand("mkdir -p " + pluginsPath);

    std::string destPath = pluginsPath + fs::path(path).filename().string();
    std::cout << "Installing plugin from: " << path << " to: " << destPath << std::endl;

    try {
        fs::copy_file(path, destPath, fs::copy_options::overwrite_existing);
        std::cout << "Plugin installed successfully." << std::endl;
        return 0;
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error installing plugin: " << ex.what() << std::endl;
        return 1;
    }
}

int Plugin::run(const std::string& name) {
    std::string pluginsPath = getPluginsPath();
    if (pluginsPath.empty()) return 1;

    std::string pluginPath = pluginsPath + name;
    std::cout << "Running plugin: " << pluginPath << std::endl;

    // Make sure the plugin is executable
    Utils::executeCommand("chmod +x \"" + pluginPath + "\" 2>/dev/null || echo 'Setting executable failed'");

    std::string cmd = "\"" + pluginPath + "\"";
    std::string result = Utils::executeCommand(cmd);
    std::cout << result << std::endl;

    return 0;
}

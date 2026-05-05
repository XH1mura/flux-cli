#include "config.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string getConfigPath() {
    const char* home = std::getenv("HOME");
    if (!home) {
        std::cerr << "HOME environment variable not set" << std::endl;
        return "";
    }
    return std::string(home) + "/.config/flux/config.json";
}

int Config::get(const std::string& key) {
    std::string configPath = getConfigPath();
    if (configPath.empty()) return 1;

    // Ensure config directory exists
    std::string configDir = configPath.substr(0, configPath.find_last_of("/"));
    Utils::executeCommand("mkdir -p " + configDir);

    std::ifstream configFile(configPath);
    json config;

    if (configFile.is_open()) {
        configFile >> config;
        configFile.close();
    } else {
        std::cout << "Config not found, creating default config" << std::endl;
        config = json::object();
    }

    if (config.contains(key)) {
        std::cout << config[key] << std::endl;
        return 0;
    } else {
        std::cout << "Key '" << key << "' not found in config" << std::endl;
        return 1;
    }
}

int Config::set(const std::string& key, const std::string& value) {
    std::string configPath = getConfigPath();
    if (configPath.empty()) return 1;

    // Ensure config directory exists
    std::string configDir = configPath.substr(0, configPath.find_last_of("/"));
    Utils::executeCommand("mkdir -p " + configDir);

    std::ifstream configFile(configPath);
    json config;

    if (configFile.is_open()) {
        configFile >> config;
        configFile.close();
    } else {
        config = json::object();
    }

    config[key] = value;

    std::ofstream outFile(configPath);
    outFile << config.dump(4);
    outFile.close();

    std::cout << "Config updated: " << key << " = " << value << std::endl;
    return 0;
}

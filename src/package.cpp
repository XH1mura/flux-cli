#include "package.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

int Package::install(const std::string& packageName) {
    std::cout << "Installing package: " << packageName << std::endl;

#ifdef __APPLE__
    std::string cmd = "brew install " + packageName;
#elif defined(_WIN32)
    std::string cmd = "choco install " + packageName + " -y";
#else
    // Try different package managers
    std::string cmd = "command -v apt >/dev/null 2>&1 && sudo apt-get install -y " + packageName +
                     " || command -v pacman >/dev/null 2>&1 && sudo pacman -S --noconfirm " + packageName +
                     " || command -v yum >/dev/null 2>&1 && sudo yum install -y " + packageName +
                     " || echo 'No supported package manager found'";
#endif

    std::string result = Utils::executeCommand(cmd);
    std::cout << result << std::endl;
    return 0;
}

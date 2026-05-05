#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace Utils {
    std::string executeCommand(const std::string& cmd);
    bool fileExists(const std::string& filename);
}

#endif

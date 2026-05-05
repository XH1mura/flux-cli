#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>

namespace System {
    int killProcessByPort(int port);
    int findProcessByPort(int port);
    int startProcess(const std::string& command);
    int monitor();
    int cleanup();
    int update();
}

#endif

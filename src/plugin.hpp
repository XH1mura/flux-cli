#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <string>

namespace Plugin {
    int list();
    int install(const std::string& path);
    int run(const std::string& name);
}

#endif

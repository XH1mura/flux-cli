#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace Config {
    int get(const std::string& key);
    int set(const std::string& key, const std::string& value);
}

#endif

#ifndef DEV_HPP
#define DEV_HPP

#include <string>

namespace Dev {
    int init(const std::string& projectName);
    int run(const std::string& path);
    int build(const std::string& path);
}

#endif

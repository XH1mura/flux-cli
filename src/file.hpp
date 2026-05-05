#ifndef FILE_HPP
#define FILE_HPP

#include <string>

namespace File {
    int find(const std::string& path);
    int copy(const std::string& src, const std::string& dst);
    int move(const std::string& src, const std::string& dst);
    int rename(const std::string& oldName, const std::string& newName);
}

#endif

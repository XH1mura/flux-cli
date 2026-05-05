#ifndef API_HPP
#define API_HPP

#include <string>

namespace Api {
    int get(const std::string& url);
    int post(const std::string& url, const std::string& data);
}

#endif

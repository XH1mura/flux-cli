#include "api.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

int Api::get(const std::string& url) {
    std::cout << "Making GET request to: " << url << std::endl;

    // Using curl for HTTP requests
    std::string cmd = "curl -s -X GET '" + url + "'";
    std::string result = Utils::executeCommand(cmd);
    std::cout << "Response:\n" << result << std::endl;
    return 0;
}

int Api::post(const std::string& url, const std::string& data) {
    std::cout << "Making POST request to: " << url << " with data: " << data << std::endl;

    // Using curl for HTTP requests
    std::string cmd = "curl -s -X POST -H 'Content-Type: application/json' -d '" + data + "' '" + url + "'";
    std::string result = Utils::executeCommand(cmd);
    std::cout << "Response:\n" + result << std::endl;
    return 0;
}

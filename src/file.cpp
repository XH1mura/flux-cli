#include "file.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int File::find(const std::string& path) {
    std::cout << "Finding files in: " << path << std::endl;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            std::cout << entry.path() << std::endl;
        }
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error accessing directory: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

int File::copy(const std::string& src, const std::string& dst) {
    std::cout << "Copying " << src << " to " << dst << std::endl;

    try {
        fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully." << std::endl;
        return 0;
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error copying file: " << ex.what() << std::endl;
        return 1;
    }
}

int File::move(const std::string& src, const std::string& dst) {
    std::cout << "Moving " << src << " to " << dst << std::endl;

    try {
        fs::rename(src, dst);
        std::cout << "File moved successfully." << std::endl;
        return 0;
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error moving file: " << ex.what() << std::endl;
        return 1;
    }
}

int File::rename(const std::string& oldName, const std::string& newName) {
    std::cout << "Renaming " << oldName << " to " << newName << std::endl;

    try {
        fs::rename(oldName, newName);
        std::cout << "File renamed successfully." << std::endl;
        return 0;
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error renaming file: " << ex.what() << std::endl;
        return 1;
    }
}

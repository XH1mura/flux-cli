#include "dev.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

#ifdef _WIN32
    #define MKDIR_CMD "mkdir "
    #define PATH_SEP "\\"
#else
    #define MKDIR_CMD "mkdir -p "
    #define PATH_SEP "/"
#endif

int Dev::init(const std::string& projectName) {
    std::cout << "Initializing project: " << projectName << std::endl;

    // Create project directory
    std::string mkdirCmd = MKDIR_CMD + projectName;
    Utils::executeCommand(mkdirCmd);

    // Create basic files
    std::string projPath = projectName + PATH_SEP;
    std::ofstream readme(projPath + "README.md");
    readme << "# " << projectName << "\n\nProject initialized with Flux CLI\n";
    readme.close();

    std::ofstream gitignore(projPath + ".gitignore");
    gitignore << "*.o\n*.a\n*.so\n.DS_Store\ncmake-build-debug/\nbuild/\n";
    gitignore.close();

    std::ofstream mainCpp(projPath + "main.cpp");
    mainCpp << "#include <iostream>\n\nint main() {\n    std::cout << \"Hello, " << projectName << "!\" << std::endl;\n    return 0;\n}\n";
    mainCpp.close();

    std::ofstream cmakeLists(projPath + "CMakeLists.txt");
    cmakeLists << "cmake_minimum_required(VERSION 3.10)\nproject(" << projectName << ")\nset(CMAKE_CXX_STANDARD 14)\nadd_executable(" << projectName << " main.cpp)\n";
    cmakeLists.close();

    std::cout << "Project " << projectName << " initialized successfully!" << std::endl;
    return 0;
}

int Dev::run(const std::string& path) {
    std::cout << "Running project at: " << path << std::endl;

    // Check if it's a Node.js project
    if (Utils::fileExists(path + "/package.json")) {
        std::string cmd = "cd " + path + " && npm start";
        std::string result = Utils::executeCommand(cmd);
        std::cout << result << std::endl;
        return 0;
    }

    // Check if it's a Python project
    if (Utils::fileExists(path + "/app.py") || Utils::fileExists(path + "/main.py")) {
        std::string pythonFile = Utils::fileExists(path + "/app.py") ? "app.py" : "main.py";
        std::string cmd = "cd " + path + " && python3 " + pythonFile;
        std::string result = Utils::executeCommand(cmd);
        std::cout << result << std::endl;
        return 0;
    }

    // For C++ projects, try building first
    if (Utils::fileExists(path + "/CMakeLists.txt")) {
        std::string buildDir = path + "/build";
        Utils::executeCommand("mkdir -p " + buildDir);
        std::string cmd = "cd " + buildDir + " && cmake .. && make && ./$(ls *.out *.exe 2>/dev/null | head -n1)";
        std::string result = Utils::executeCommand(cmd);
        std::cout << result << std::endl;
        return 0;
    }

    std::cout << "Could not determine how to run project at: " << path << std::endl;
    return 1;
}

int Dev::build(const std::string& path) {
    std::cout << "Building project at: " << path << std::endl;

    // Check if it's a Node.js project
    if (Utils::fileExists(path + "/package.json")) {
        std::string cmd = "cd " + path + " && npm run build";
        std::string result = Utils::executeCommand(cmd);
        std::cout << result << std::endl;
        return 0;
    }

    // Check if it's a Python project
    if (Utils::fileExists(path + "/setup.py")) {
        std::string cmd = "cd " + path + " && python3 setup.py build";
        std::string result = Utils::executeCommand(cmd);
        std::cout << result << std::endl;
        return 0;
    }

    // For C++ projects with CMake
    if (Utils::fileExists(path + "/CMakeLists.txt")) {
        std::string buildDir = path + "/build";
        Utils::executeCommand("mkdir -p " + buildDir);
        std::string cmd = "cd " + buildDir + " && cmake .. && make";
        std::string result = Utils::executeCommand(cmd);
        std::cout << result << std::endl;
        return 0;
    }

    std::cout << "Could not determine how to build project at: " << path << std::endl;
    return 1;
}

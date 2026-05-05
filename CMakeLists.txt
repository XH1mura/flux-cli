cmake_minimum_required(VERSION 3.10)
project(flux)

set(CMAKE_CXX_STANDARD 17)

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(CURL REQUIRED)

# Include directories
include_directories(include)
include_directories(/usr/include/nlohmann)  # For JSON library

# Source files
set(SOURCES
    src/main.cpp
    src/cli.cpp
    src/system.cpp
    src/package.cpp
    src/dev.cpp
    src/api.cpp
    src/file.cpp
    src/config.cpp
    src/plugin.cpp
    src/utils.cpp
)

# Create executable
add_executable(flux ${SOURCES})

# Link libraries
target_link_libraries(flux CURL::libcurl)

# Install target
install(TARGETS flux DESTINATION bin)

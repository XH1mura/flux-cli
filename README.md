# Flux CLI

A powerful command-line interface tool for system administration, development, and automation tasks.

## Features

- **System Management**: Process control, monitoring, cleanup, updates
- **Package Management**: Install packages via system package managers
- **Development Tools**: Project initialization, running, and building
- **API Client**: Make HTTP requests to APIs
- **File Operations**: Find, copy, move, and rename files
- **Configuration Management**: Store and retrieve configuration values
- **Plugin System**: Extend functionality with custom plugins

## Installation

### Prerequisites
- C++17 compatible compiler
- CMake 3.10+
- libcurl development headers
- nlohmann/json library

On Ubuntu/Debian:
```bash
sudo apt-get install build-essential cmake libcurl4-openssl-dev nlohmann-json3-dev
```

### Building from Source
```bash
git clone https://github.com//CLI.git
cd CLI
mkdir build
cd build
cmake ..
make
```

### Curl Installing 
```bash
    curl -sSL https://github.com/XH1mura/flux-cli/raw/main/setup.sh | sudo bash
```

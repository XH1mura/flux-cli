#!/bin/bash

set -e

echo "Installing Flux CLI..."

# Check if running on macOS or Linux
if [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
    INSTALL_DIR="/usr/local/bin"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="Linux"
    INSTALL_DIR="/usr/local/bin"
else
    echo "Unsupported platform: $OSTYPE"
    exit 1
fi

echo "Detected platform: $PLATFORM"

# Check if we have write permissions to install directory
if [[ ! -w "$INSTALL_DIR" ]]; then
    echo "Need sudo access to install to $INSTALL_DIR"
    sudo -v
fi

# Build the project
echo "Building Flux CLI..."
if [[ ! -d "build" ]]; then
    mkdir build
fi
cd build
cmake ..
make

# Install the binary
echo "Installing binary..."
BINARY_PATH="$(pwd)/flux"

if [[ "$PLATFORM" == "Linux" ]]; then
    sudo cp "$BINARY_PATH" "$INSTALL_DIR/flux"
elif [[ "$PLATFORM" == "macOS" ]]; then
    sudo cp "$BINARY_PATH" "$INSTALL_DIR/flux"
fi

# Verify installation
if command -v flux &> /dev/null; then
    echo "Flux CLI installed successfully!"
    echo "Run 'flux --help' to get started."
else
    echo "Installation failed. Please check permissions and paths."
    exit 1
fi

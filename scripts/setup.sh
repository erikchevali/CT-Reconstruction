#!/bin/bash

echo "Setting up project folders..."

# navigate to home directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
cd "$PROJECT_ROOT"

# create required directories if they don't exist
mkdir -p data
mkdir -p results
mkdir -p build
echo "Directories created (or already exist)."

# create first build
echo "Running CMake..."
cd build
cmake ..
make
echo "Setup complete, first build made!"
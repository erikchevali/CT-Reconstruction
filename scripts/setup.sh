#!/bin/bash

echo "Setting up project folders..."


# Create required directories if they don't exist
cd ~/projects/CT-Reconstruction
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
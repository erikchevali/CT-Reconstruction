#!/bin/bash

# make sure we are in the project root directory
cd ~/projects/CT-Reconstruction

# reconfigure the project if necessary, handle edge cases
if [ "CMakeLists.txt" -nt "build/CMakeCache.txt" ] || [ ! -f "build/CMakeCache.txt" ]; then
    echo "CMakeLists.txt is newer than CMakeCache.txt. Reconfiguring the project..."
   
    # Create a build directory if it doesn't exist
    if [ ! -d "build" ]; then
        mkdir build
    fi

    cd build
    cmake ..
    cd ..

else
    echo "CMakeCache.txt is up to date. Skipping CMake configuration."
fi


# build the project
cd build
make

# get phantom input
PHANTOM=${1:-1}

# run the executable
./ct_reconstruct $PHANTOM

cd ..

# open the results in infranview
INFRANVIEW="/mnt/c/Program Files/IrfanView/i_view64.exe"

"$INFRANVIEW" "$(wslpath -w data/phantom.pgm)" &
"$INFRANVIEW" "$(wslpath -w data/sinogram.pgm)" &
"$INFRANVIEW" "$(wslpath -w data/result.pgm)" &



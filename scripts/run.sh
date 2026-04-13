#!/bin/bash

# build the project
cd ~/projects/CT-Reconstruction/build
make

# run the executable
./ct_reconstruct

cd ..

# open the results in infranview
INFRANVIEW="/mnt/c/Program Files/IrfanView/i_view64.exe"

"$INFRANVIEW" "$(wslpath -w data/phantom.pgm)" &
"$INFRANVIEW" "$(wslpath -w data/sinogram.pgm)" &
"$INFRANVIEW" "$(wslpath -w data/result.pgm)" &



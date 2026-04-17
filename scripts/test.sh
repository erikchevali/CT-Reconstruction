#!/bin/bash

# make sure we are in the project root directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
cd "$PROJECT_ROOT"

# reconfigure the project if necessary, handle edge cases
if [ "CMakeLists.txt" -nt "build/CMakeCache.txt" ] || [ ! -f "build/CMakeCache.txt" ]; then
    echo "CMakeLists.txt is newer than CMakeCache.txt. Reconfiguring the project..."
   
    # create a build directory if it doesn't exist
    if [ ! -d "build" ]; then
        mkdir build
    fi

    # reconfigure project
    cd build
    cmake ..
    cd ..

else
    echo "CMakeCache.txt is up to date. Skipping CMake configuration."
fi


# build the project
cd build
make

# create output directories for each phantom
mkdir -p ../results

echo "Running simulation on all 5 phantoms..."

# loop through all 5 phantoms
for i in 1 2 3 4 5; do
    echo "Running phantom $i..."
    
    # run the simulation
    ./ct_reconstruct $i

    # check if output files were created
    if [ -f "../data/phantom.pgm" ] && [ -f "../data/sinogram.pgm" ] && [ -f "../data/result.pgm" ]; then
        echo "PASS: Phantom $i output files generated"
        
        # Copy results to labeled files
        cp ../data/phantom.pgm ../results/phantom_$i.pgm
        cp ../data/sinogram.pgm ../results/sinogram_$i.pgm
        cp ../data/result.pgm ../results/result_$i.pgm

        # Convert PGM to PNG for web viewing
        convert ../results/phantom_$i.pgm ../results/phantom_$i.png
        convert ../results/sinogram_$i.pgm ../results/sinogram_$i.png
        convert ../results/result_$i.pgm ../results/result_$i.png

    else
        echo "FAIL: Phantom $i did not generate all output files"
    fi
done

# navigate back to project root
cd ..

echo "Generating HTML results page..."

# generate the HTML file
cat > results/index.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>CT Reconstruction Results</title>
    <style>
        body { font-family: Arial, sans-serif; background: #1a1a1a; color: #ffffff; padding: 20px; }
        h1 { color: #4a9edd; }
        h2 { color: #aaaaaa; font-size: 14px; margin: 4px 0; }
        table { border-collapse: collapse; width: 100%; }
        th { background: #2a2a2a; padding: 12px; color: #4a9edd; text-align: center; }
        td { padding: 10px; text-align: center; border: 1px solid #333; }
        img { width: 180px; height: 180px; object-fit: contain; background: #000; }
        .pass { color: #44ff44; font-weight: bold; }
    </style>
</head>
<body>
    <h1>CT Reconstruction Pipeline — Results</h1>
    <p>All 5 phantoms processed through forward projection and filtered back-projection (Ram-Lak + Hann window)</p>
    <table>
        <tr>
            <th>Phantom</th>
            <th>Original</th>
            <th>Sinogram</th>
            <th>Reconstruction</th>
            <th>Status</th>
        </tr>
EOF

# add a row for each phantom
PHANTOM_NAMES=("" "Basic Shepp-Logan" "Circle" "Off-Center" "Contrast Test" "Multi-Object")

for i in 1 2 3 4 5; do
    if [ -f "results/phantom_$i.png" ]; then
        STATUS='<span class="pass">PASS</span>'
    else
        STATUS='<span style="color:#ff4444">FAIL</span>'
    fi

    cat >> results/index.html << EOF
        <tr>
            <td><b>${PHANTOM_NAMES[$i]}</b></td>
            <td><img src="phantom_$i.png" alt="Phantom $i"></td>
            <td><img src="sinogram_$i.png" alt="Sinogram $i"></td>
            <td><img src="result_$i.png" alt="Result $i"></td>
            <td>$STATUS</td>
        </tr>
EOF
done


# close the HTML
cat >> results/index.html << 'EOF'
    </table>
</body>
</html>
EOF

echo "Opening results in browser..."

# get the absolute Windows path for the index file
WIN_PATH=$(wslpath -w "$(pwd)/results/index.html")

# use PowerShell to start the file
powershell.exe -Command "Start-Process '$WIN_PATH'"

echo "Done! Check results/index.html"





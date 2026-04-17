# CT-Reconstruction

## Project Overview
This project simulates the physics of a CT scanner. It takes 2D phantom images, generates sinograms (forward projection), and then reconstructs the original image using filtered back projection. 

## Prerequisites
Before running the scripts, ensure you have the following installed:
* **CMake**
* **C++ Compiler** (g++ used in development)
* **ImageMagick** 

## How to run
The project is automated via bash scripts located in the `scripts/` directory.

### 1. Setup
From the **project root**, make the scripts executable and initialize the build environment:
```bash
chmod +x scripts/*.sh
scripts/setup.sh
```
### 2. Testing
This will create an initial build. Then use:
```bash
scripts/test.sh
```

This will generate all five simulation results and display them in an html page.

Use run.sh to test a specific phantom. It takes an input of an integer 1-5. No input will run the first phantom '1'. Example:
```bash
scripts/run.sh 3
```
To run manually, the executable lives in the build folder and is called ct_reconstruct. Run from project root:
```bash
cd build
./ct_reconstruct [input integer here]
```

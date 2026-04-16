#include <numbers> 
#include <iostream>
#include <fstream>
#include "phantom.h"
#include "projection.h"
#include "reconstruction.h"
#include "filtering.h"

void saveImagePGM(const std::vector<std::vector<double>>& image, const std::string& filename) {
    if (image.empty() || image[0].empty()) return;

    int height = image.size();
    int width = image[0].size();
    std::ofstream file(filename);

    // Find the max value for normalization
    double maxVal = 0.0;
    for (const auto& row : image) {
        for (double val : row) {
            if (val > maxVal) maxVal = val;
        }
    }

    file << "P2\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            // clip non-negative values for display
            double rawVal = image[i][j];
            if (rawVal < 0) rawVal = 0.0;

            // Scale based on the max value found in the data
            int val = (maxVal > 0) ? static_cast<int>((rawVal / maxVal) * 255) : 0;
            file << val << " ";
        }
        file << "\n";
    }
}

int main(int argc, char* argv[]) {
    int size = 256;

    // default to phantom 1 if no argument is given
    int phantomChoice = 1;
    if (argc > 1) {
        phantomChoice = std::stoi(argv[1]);
    }

    // Sinogram Setup
    int numAngles = 360;    // How many views
    int numSensors = 400;   // How dense the detector bar is
    int length = 200;       // Physical size of detector
    double tStep = 0.25;     // Step size for ray marching
    double r = 200.0;       // Orbit radius

    // Preallocate vector images
    std::vector<std::vector<double>> image(size, std::vector<double>(size, 0.0));
    std::vector<std::vector<double>> result(size, std::vector<double>(size, 0.0));
    std::vector<std::vector<double>> sinogram(numAngles, std::vector<double>(numSensors, 0.0));

    // generate chosen phantom
    std::cout << "Generating phantom..." << std::endl;
    switch (phantomChoice) {
        case 1:
            generatePhantom(image, size);
            break;
        case 2:
            generateCirclePhantom(image, size);
            break;
        case 3:
            generateOffCenterPhantom(image, size);
            break;
        case 4:
            std::cout << "Generating high contrast phantom..." << std::endl;
            generateHighContrastPhantom(image, size);
            break;
        case 5:
            std::cout << "Generating multi-object phantom..." << std::endl;
            generateMultiObjectPhantom(image, size);
            break;
        default:
            std::cerr << "Invalid phantom choice. Using default phantom." << std::endl;
            generatePhantom(image, size);
    }

    std::cout << "Saving phantom to data/phantom.pgm..." << std::endl;
    saveImagePGM(image, "../data/phantom.pgm");

    std::cout << "Generating sinogram..." << std::endl;
    generateSinogram(image, sinogram, numAngles, numSensors, length, tStep, r);

    std::cout << "Saving sinogram to data/sinogram.pgm..." << std::endl;
    saveImagePGM(sinogram, "../data/sinogram.pgm");

    std::cout << "Filtering sinogram..." << std::endl;
    std::vector<std::vector<double>> filtSinogram = filteredSinogram(sinogram);
    
    std::cout << "Generating result..." << std::endl;
    reconstructImage(filtSinogram, result, numAngles, numSensors, length, tStep, r);

    std::cout << "Saving result to data/result.pgm..." << std::endl;
    saveImagePGM(result, "../data/result.pgm");
    
    std::cout << "Done!" << std::endl;
    
    return 0;
}
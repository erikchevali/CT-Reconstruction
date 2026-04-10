#include <numbers> 
#include <iostream>
#include <fstream>
#include "phantom.h"
#include "projection.h"
#include "reconstruction.h"

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
            // Scale based on the max value found in the data
            int val = (maxVal > 0) ? static_cast<int>((image[i][j] / maxVal) * 255) : 0;
            file << val << " ";
        }
        file << "\n";
    }
}

int main() {
    int size = 256;

    // 2. Sinogram Setup
    int numAngles = 360;    // How many views
    int numSensors = 400;   // How wide the detector bar is
    int length = 200;       // Physical size of detector
    double tStep = 0.5;     // Step size for ray marching
    double r = 200.0;       // Orbit radius

    // Preallocate vector images
    std::vector<std::vector<double>> image(size, std::vector<double>(size, 0.0));
    std::vector<std::vector<double>> result(size, std::vector<double>(size, 0.0));
    std::vector<std::vector<double>> sinogram(numAngles, std::vector<double>(numSensors, 0.0));

    std::cout << "Generating phantom..." << std::endl;
    generatePhantom(image, size);

    std::cout << "Saving phantom to data/phantom.pgm..." << std::endl;
    saveImagePGM(image, "../data/phantom.pgm");

    std::cout << "Generating sinogram..." << std::endl;
    generateSinogram(image, sinogram, numAngles, numSensors, length, tStep, r);

    std::cout << "Saving sinogram to data/sinogram.pgm..." << std::endl;
    saveImagePGM(sinogram, "../data/sinogram.pgm");

    std::cout << "Generating result..." << std::endl;
    reconstructImage(sinogram, result, numAngles, numSensors, length, tStep, r);

    std::cout << "Saving result to data/result.pgm..." << std::endl;
    saveImagePGM(result, "../data/result.pgm");
    
    std::cout << "Done!" << std::endl;
    
    return 0;
}
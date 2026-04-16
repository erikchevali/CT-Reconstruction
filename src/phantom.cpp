#include "phantom.h"
#include <cmath>
#include <tuple>

// function to normalize coordinates from size domain to [-1, 1]
std::tuple<double, double> normalizeCoordinates(int i, int j, int size) {
    double x = (2.0 * j / size) - 1.0;
    double y = (2.0 * i / size) - 1.0;
    return {x, y};
}

// generate a very simple Shepp-Logan
void generatePhantom(std::vector<std::vector<double>>& image, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            
            // normalize coordinates
            auto [x, y] = normalizeCoordinates(i, j, size);
            image[i][j] = 0.0;

            // outer ellipse (skull)
            if ((x * x) / 0.69 + (y * y) / 0.92 <= 1.0)
                image[i][j] += 1.0;

            // inner ellipse (brain stuff)
            if ((x * x) / 0.6624 + (y * y) / 0.8740 <= 1.0)
                image[i][j] -= 0.90;

            // small detail ellipse
            if (((x - 0.22) * (x - 0.22)) / 0.11 + (y * y) / 0.31 <= 1.0)
                image[i][j] += 0.41;
        }
    }
}

// generate a simple circle
void generateCirclePhantom(std::vector<std::vector<double>>& image, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            auto [x, y] = normalizeCoordinates(i, j, size);
            image[i][j] = 0.0;
            if (x * x + y * y <= 0.5)
                image[i][j] = 1.0;
        }
    }
}


// generate a multi object Shepp-Logan, slightly off center
void generateOffCenterPhantom(std::vector<std::vector<double>>& image, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            // normalize
            auto [x, y] = normalizeCoordinates(i, j, size);
            image[i][j] = 0.0;

            // generate an ellipse towards the upper left
            if ((x+0.4) * (x+0.4) / 0.18 + (y+0.2) * (y+0.2) / 0.4 <= 0.5) {
                image[i][j] = 1.0;
            }

            // generate a circle near the bottom right
            if ((x-0.3) * (x-0.3) / 0.1 + (y-0.3) * (y-0.3) / 0.1 <= 0.7) {
                image[i][j] = 1.0;
            }

            // generate a skull outline slightly offcenter
            if (((x+0.05) * (x+0.05) + (y+0.05) * (y+0.05) <= 0.85) && (x+0.05) * (x+0.05) + (y+0.05) * (y+0.05) >= 0.80) {
                image[i][j] = 1.0;
            }
        }
    }
}

// generate a high contrast multisection phantom
void generateHighContrastPhantom(std::vector<std::vector<double>>& image, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            // normalize
            auto [x, y] = normalizeCoordinates(i, j, size);
            image[i][j] = 0.0;

            // large bright outer ellipse
            if ((x * x) / 0.8 + (y * y) / 0.8 <= 1.0)
                image[i][j] = 1.0;

            // sectioned middle region with different attenuations
            if ((x * x) / 0.3 + (y * y) / 0.3 <= 1.0) {
                if (x < 0 && y < 0)  image[i][j] = 0.5; // bottom left quadrant
                else if (x >= 0 && y < 0) image[i][j] = 0.6; // bottom right quadrant
                else if (x < 0 && y >= 0) image[i][j] = 0.7; // top left quadrant
                else image[i][j] = 0.8; // top right quadrant     
            } 

            // small dark circle in top right quadrant
            if ((x - 0.25) * (x - 0.25) + (y - 0.25) * (y - 0.25) <= 0.02)
                image[i][j] = 0.0;
        }
    }
}

// generate a multi circle phantom of differing attenuations
void generateMultiObjectPhantom(std::vector<std::vector<double>>& image, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            //normalize
            auto [x, y] = normalizeCoordinates(i, j, size);
            image[i][j] = 0.0;

            // top left
            if (((x + 0.5) * (x + 0.5)) / 0.08 + ((y + 0.5) * (y + 0.5)) / 0.08 <= 1.0)
                image[i][j] = 1.0;

            // top right
            if (((x - 0.5) * (x - 0.5)) / 0.08 + ((y + 0.5) * (y + 0.5)) / 0.08 <= 1.0)
                image[i][j] = 0.8;

            // center
            if ((x * x) / 0.08 + (y * y) / 0.08 <= 1.0)
                image[i][j] = 0.6;

            // bottom left
            if (((x + 0.5) * (x + 0.5)) / 0.08 + ((y - 0.5) * (y - 0.5)) / 0.08 <= 1.0)
                image[i][j] = 0.4;

            // bottom right
            if (((x - 0.5) * (x - 0.5)) / 0.08 + ((y - 0.5) * (y - 0.5)) / 0.08 <= 1.0)
                image[i][j] = 0.2;
        }
    }
}
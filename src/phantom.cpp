#include "phantom.h"
#include <cmath>

void generatePhantom(std::vector<std::vector<double>>& image, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Normalize coordinates to range [-1, 1]
            double x = (2.0 * j / size) - 1.0;
            double y = (2.0 * i / size) - 1.0;

            image[i][j] = 0.0;

            // Outer ellipse (skull)
            if ((x * x) / 0.69 + (y * y) / 0.92 <= 1.0)
                image[i][j] += 1.0;

            // Inner ellipse (brain matter)
            if ((x * x) / 0.6624 + (y * y) / 0.8740 <= 1.0)
                image[i][j] -= 0.98;

            // Small detail ellipse
            if (((x - 0.22) * (x - 0.22)) / 0.11 + (y * y) / 0.31 <= 1.0)
                image[i][j] += 0.41;
        }
    }
}
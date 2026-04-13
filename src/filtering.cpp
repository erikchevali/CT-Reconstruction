#include <complex>
#include <vector>
#include <cmath>

// Discrete Fourier Transform (DFT) implementation
std::vector<std::complex<double>> dft(const std::vector<double>& signal) {
    int N = signal.size();
    std::vector<std::complex<double>> result(N);
    for (int k = 0; k < N; k++) {
        result[k] = 0;
        for (int n = 0; n < N; n++) {
            double angle = -2.0 * M_PI * k * n / N;

            result[k] += signal[n] * 
            std::complex<double>(std::cos(angle), std::sin(angle));
        }
    }
    return result;
}

//Inverse Discrete Fourier Transform (IDFT) implementation
std::vector<double> idft(const std::vector<std::complex<double>>& freqs) {
    int N = freqs.size();
    std::vector<double> result(N);
    for (int n = 0; n < N; n++) {
        std::complex<double> sum = 0;
        for (int k = 0; k < N; k++) {
            double angle = 2.0 * M_PI * k * n / N;
            sum += freqs[k] * std::complex<double>(std::cos(angle), std::sin(angle));
        }
        result[n] = sum.real() / N;
    }
    return result;
}

// Apply Ram-Lak filter to a single sinogram row
std::vector<double> ramLakFilter(const std::vector<double>& row) {
    int N = row.size();
    std::vector<std::complex<double>> freqs = dft(row);
    for (int k = 0; k < N; k++) {
        double freq = (k <= N / 2) ? k : N - k;
        freqs[k] *= freq;
    }
    return idft(freqs);
}

// Run the Ram-Lak filter on the entire sinogram
std::vector<std::vector<double>> filteredSinogram(const std::vector<std::vector<double>>& sinogram) {
    std::vector<std::vector<double>> filtered(sinogram.size(), std::vector<double>(sinogram[0].size()));
    for (size_t row = 0; row < sinogram.size(); row++) {
        filtered[row] = ramLakFilter(sinogram[row]);
    }

    return filtered;
}
#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "FastFourierTransform.h"
#include "CImg.h"

using namespace cimg_library;

FastFourierTransform::FastFourierTransform(std::string inputPath, std::string outputPath) {

    this->inputPath = inputPath;
    this->outputPath = outputPath;

}

FastFourierTransform::~FastFourierTransform() {
}

std::string FastFourierTransform::getInputPath() {
    return this->inputPath;
}
void FastFourierTransform::setInputPath(std::string path) {
    this->inputPath = path;
}

std::string FastFourierTransform::getOutputPath() {
    return this->outputPath;
}

void FastFourierTransform::setOutputPath(std::string path) {
    this->outputPath = path;
}

std::vector<std::complex<double>> FastFourierTransform::fft(std::vector<double> a) {
    int n = a.size();
    std::complex<double> ii;
    ii = -1;
    ii = sqrt(ii);

    // if input contains just one element
    if (n == 1)
        return std::vector<std::complex<double>>(1, a[0]);

    // For storing n complex nth roots of unity
    std::vector<double> w(n);
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        w[i] = alpha;
    }

    std::vector<double> A0(n / 2), A1(n / 2);
    for (int i = 0; i < n / 2; i++) {

        // even indexed coefficients
        A0[i] = a[i * 2];

        // odd indexed coefficients
        A1[i] = a[i * 2 + 1];
    }

    // Recursive call for even indexed coefficients
    std::vector<std::complex<double>> y0 = fft(A0);

    // Recursive call for odd indexed coefficients
    std::vector<std::complex<double>> y1 = fft(A1);

    // for storing values of y0, y1, y2, ..., yn-1.
    std::vector<std::complex<double>> y(n);

    for (int k = 0; k < n / 2; k++) {
        y[k] = y0[k] + (cos(w[k]) - ii*sin(w[k])) * y1[k];
        y[k + n / 2] = y0[k] - (cos(w[k]) - ii*sin(w[k])) * y1[k];
    }
    return y;
}

std::vector<double> FastFourierTransform::forward() {
    CImg<unsigned char> image(getInputPath().c_str());
    std::vector<double> matrix;
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            double avg = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
            matrix.push_back(avg);
        }
    }
    return matrix;
}

std::vector<std::complex<double>> FastFourierTransform::center(std::vector<std::complex<double>> a) {

    std::vector<std::complex<double>> transformCentered(a.size(), 0.0);
    CImg<unsigned char> image(getInputPath().c_str());

    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = 0; y < image.height() / 2; y++) {
            transformCentered[(x + (image.width()/2))  * image.width() + (y + image.height()/2)] = a[image.width() * x + y];
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = 0; y < image.height() / 2; y++) {
            transformCentered[(x - (image.width()/2)) * image.width() + (y + image.height()/2)] = a[image.width() * x + y];
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            transformCentered[(x + (image.width()/2)) * image.width() + (y - image.height()/2)] = a[image.width() * x + y];
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            transformCentered[(x - (image.width()/2)) * image.width() + (y - image.height()/2)] = a[image.width() * x + y];
        }
    }
    return transformCentered;
}

std::vector<std::complex<double>> FastFourierTransform::ifft(std::vector<std::complex<double>> a) {
    int n = a.size();
    std::complex<double> ii;
    ii = -1;
    ii = sqrt(ii);

    // if input contains just one element
    if (n == 1)
        return std::vector<std::complex<double>>(1, a[0]);

    // For storing n complex nth roots of unity
    std::vector<std::complex<double>> w(n);
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        w[i] = alpha;
    }

    std::vector<std::complex<double>> A0(n / 2), A1(n / 2);
    for (int i = 0; i < n / 2; i++) {

        // even indexed coefficients
        A0[i] = a[i * 2];

        // odd indexed coefficients
        A1[i] = a[i * 2 + 1];
    }

    // Recursive call for even indexed coefficients
    std::vector<std::complex<double>> y0 = ifft(A0);

    // Recursive call for odd indexed coefficients
    std::vector<std::complex<double>> y1 = ifft(A1);

    // for storing values of y0, y1, y2, ..., yn-1.
    std::vector<std::complex<double>> y(n);

    for (int k = 0; k < n / 2; k++) {
        y[k] = (y0[k] + (cos(w[k]) + ii*sin(w[k])) * y1[k]);
        y[k + n / 2] = (y0[k] - (cos(w[k]) + ii*sin(w[k])) * y1[k]);
    }
    return y;
}


void FastFourierTransform::transform() {
    cimg::exception_mode(0);
    CImg<unsigned char> image(getInputPath().c_str());
    CImg<unsigned char> mag(getInputPath().c_str());
    try {
        std::vector<double> matrix;
        std::vector<std::complex<double>> matrix2;
        std::vector<std::complex<double>> matrix3;
        std::vector<std::complex<double>> matrix4;
        std::vector<std::complex<double>> result;

        matrix = forward();
        matrix2 = fft(matrix);
        matrix3 = center(matrix2);
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double magnitude = sqrt(pow(matrix3[image.width() * x + y].real(), 2) + pow(matrix3[image.width() * x + y].imag(), 2));
                if (20 * log(1 + magnitude) < 0) {
                    mag(x, y, 0) = 0;
                    mag(x, y, 1) = 0;
                    mag(x, y, 2) = 0;
                } else if (20 * log(1 + magnitude) > 255) {
                    mag(x, y, 0) = 255;
                    mag(x, y, 1) = 255;
                    mag(x, y, 2) = 255;
                } else {
                    mag(x, y, 0) = 20 * log(1 + magnitude);
                    mag(x, y, 1) = 20 * log(1 + magnitude);
                    mag(x, y, 2) = 20 * log(1 + magnitude);
                }
            }
        }
        mag.save_bmp("../../../../images/fftmag.bmp");
        matrix4 = center(matrix3);
        result = ifft(matrix4);
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                result[image.width() * x + y] = result[image.width() * x + y] / ((double) result.size());
                double magnitude = sqrt(pow(result[image.width() * x + y].real(), 2) + pow(result[image.width() * x + y].imag(), 2));
                image(x, y, 0) = magnitude;
                image(x, y, 1) = magnitude;
                image(x, y, 2) = magnitude;
            }
        }
        image.save_bmp(getOutputPath().c_str());

//        matrix2 = inverse(matrix);
//        for (int x = 0; x < image.width(); x++) {
//            for (int y = 0; y < image.height(); y++) {
//                double mag = sqrt(pow(matrix2[image.width() * y + x].real(), 2) + pow(matrix2[image.width() * y + x].imag(), 2));
//                image(x, y, 0) = mag;
//                image(x, y, 1) = mag;
//                image(x, y, 2) = mag;
//            }
//        }
    }
    catch (CImgIOException e) {
        throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
    }

}
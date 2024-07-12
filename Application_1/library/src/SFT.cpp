#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "SFT.h"
#include "CImg.h"

using namespace cimg_library;

SFT::SFT(std::string inputPath, std::string outputPath) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
}

SFT::~SFT() {
}

std::string SFT::getInputPath() {
	return this->inputPath;
}
void SFT::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string SFT::getOutputPath() {
	return this->outputPath;
}

void SFT::setOutputPath(std::string path) {
	this->outputPath = path;
}

std::vector<std::vector<std::complex<double>>> SFT::forward() {
    CImg<unsigned char> image(getInputPath().c_str());
    CImg<unsigned char> magnitude(getInputPath().c_str());
    CImg<unsigned char> output(image.width(), image.height(), 1, 3);
    std::complex<double> i;
    i = -1;
    i = sqrt(i);
    std::vector<std::vector<std::complex<double>>> matrix(image.width(), std::vector<std::complex<double>>(image.height(), 0.0));
    std::vector<std::vector<std::complex<double>>> transformCentered(image.width(), std::vector<std::complex<double>>(image.height(), 0.0));

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            std::complex<double> sum = 0;
            double ph;
            for (int ii = 0; ii < image.width(); ii++) {
                for (int j = 0; j < image.height(); j++) {
                    double angle = 2 * M_PI * ((double)(x * ii) / (double)image.width() + (double)(y * j) / (double)image.height());
                    sum += (double)image(ii, j, 0) * (cos(angle) - i*sin(angle));
                }
            }
            matrix[x][y] = sum;
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = 0; y < image.height() / 2; y++) {
            transformCentered[x + (image.width()/2)][y + image.height()/2] = matrix[x][y];
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = 0; y < image.height() / 2; y++) {
            transformCentered[x - (image.width()/2)][y + image.height()/2] = matrix[x][y];
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            transformCentered[x + (image.width()/2)][y - image.height()/2] = matrix[x][y];
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            transformCentered[x - (image.width()/2)][y - image.height()/2] = matrix[x][y];
        }
    }
    double max = 0.0;
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            double magnitude = sqrt(pow(transformCentered[x][y].real(), 2) + pow(transformCentered[x][y].imag(), 2));
            if (magnitude > max) {
                max = magnitude;
            }
        }
    }
    double c = 255 / log(1 + abs(max));

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            double magnitude = sqrt(pow(transformCentered[x][y].real(), 2) + pow(transformCentered[x][y].imag(), 2));
            if (c * log(1 + magnitude) < 0) {
                output(x, y, 0) = 0;
                output(x, y, 1) = 0;
                output(x, y, 2) = 0;
            } else if (c * log(1 + magnitude) > 255) {
                output(x, y, 0) = 255;
                output(x, y, 1) = 255;
                output(x, y, 2) = 255;
            } else {
                output(x, y, 0) = c * log(1 + magnitude);
                output(x, y, 1) = c * log(1 + magnitude);
                output(x, y, 2) = c * log(1 + magnitude);
            }
        }
    }
    output.save_bmp("../../../images/sftmag.bmp");
    return matrix;

}

void SFT::inverse(std::vector<std::vector<std::complex<double>>> matrix) {
    CImg<unsigned char> image(getInputPath().c_str());
    std::complex<double> i;
    i = -1;
    i = sqrt(i);
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            std::complex<double> sum = 0;
            for (int ii = 0; ii < image.width(); ii++) {
                for (int j = 0; j < image.height(); j++) {
                    double angle = 2 * M_PI * ((double)(x * ii) / (double)image.width() + (double)(y * j) / (double)image.height());
                    sum += matrix[x][y] * (cos(angle) + i*sin(angle));
                }
            }
            sum = sum / (double)(image.width() * image.height());
            double mag = sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2));
            image(x, y, 0) = mag;
            image(x, y, 1) = mag;
            image(x, y, 2) = mag;
        }
    }
    image.save_bmp(getOutputPath().c_str());
}

void SFT::transform() {
	cimg::exception_mode(0);
	try {
        std::vector<std::vector<std::complex<double>>> matrix;
        matrix = forward();
        inverse(matrix);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}
}
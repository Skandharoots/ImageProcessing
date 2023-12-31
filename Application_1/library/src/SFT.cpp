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

std::vector<std::complex<double>> SFT::forward() {
    CImg<unsigned char> image(getInputPath().c_str());
    CImg<unsigned char> magnitude(getInputPath().c_str());
    CImg<unsigned char> output(image.width(), image.height(), 1, 3);
    std::complex<double> i;
    i = -1;
    i = sqrt(i);
    std::vector<std::complex<double>> matrix;
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
            matrix.push_back(sum);
            float mag = sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2));
            magnitude(x, y, 0) = 20 * log(1 + mag);
            magnitude(x, y, 1) = 20 * log(1 + mag);
            magnitude(x, y, 2) = 20 * log(1 + mag);
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = 0; y < image.height() / 2; y++) {
            output(x + (image.width()/2), y + (image.height()/2), 0) = magnitude(x, y, 0);
            output(x + (image.width()/2), y + (image.height()/2), 1) = magnitude(x, y, 1);
            output(x + (image.width()/2), y + (image.height()/2), 2) = magnitude(x, y, 2);
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = 0; y < image.height() / 2; y++) {
            output(x - (image.width()/2), y + (image.height()/2), 0) = magnitude(x, y, 0);
            output(x - (image.width()/2), y + (image.height()/2), 1) = magnitude(x, y, 1);
            output(x - (image.width()/2), y + (image.height()/2), 2) = magnitude(x, y, 2);
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            output(x + (image.width()/2), y - (image.height()/2), 0) = magnitude(x, y, 0);
            output(x + (image.width()/2), y - (image.height()/2), 1) = magnitude(x, y, 1);
            output(x + (image.width()/2), y - (image.height()/2), 2) = magnitude(x, y, 2);
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            output(x - (image.width()/2), y - (image.height()/2), 0) = magnitude(x, y, 0);
            output(x - (image.width()/2), y - (image.height()/2), 1) = magnitude(x, y, 1);
            output(x - (image.width()/2), y - (image.height()/2), 2) = magnitude(x, y, 2);
        }
    }
    output.save_bmp("../../../../images/sftmag.bmp");
    return matrix;

}

void SFT::inverse(std::vector<std::complex<double>> matrix) {
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
                    sum += matrix[((image.width() * ii) + j)] * (cos(angle) + i*sin(angle));
                }
            }
            sum = sum / (double)(image.width() * image.height());
            float mag = sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2));
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
        std::vector<std::complex<double>> matrix;
        matrix = forward();
        inverse(matrix);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}
}
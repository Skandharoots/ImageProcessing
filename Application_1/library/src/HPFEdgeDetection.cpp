#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "HPFEdgeDetection.h"
#include "CImg.h"
#include "FFT.h"

using namespace cimg_library;

HPFEdgeDetection::HPFEdgeDetection(std::string arguments, std::string inputPath, std::string outputPath, std::string inputPath2) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;
    this->inputPath2 = inputPath2;
	
}

void HPFEdgeDetection::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string HPFEdgeDetection::getArguments() {
	return this->arguments;
}

HPFEdgeDetection::~HPFEdgeDetection() {
}

std::string HPFEdgeDetection::getInputPath() {
	return this->inputPath;
}

void HPFEdgeDetection::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string HPFEdgeDetection::getInputPath2() {
	return this->inputPath2;
}

void HPFEdgeDetection::setInputPath2(std::string path) {
	this->inputPath2 = path;
}

std::string HPFEdgeDetection::getOutputPath() {
	return this->outputPath;
}

void HPFEdgeDetection::setOutputPath(std::string path) {
	this->outputPath = path;
}

void HPFEdgeDetection::pass() {
	cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> mask(getInputPath2().c_str());
        CImg<unsigned char> magnitude(getInputPath().c_str());

        FFT fft(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::complex<double>> transformOutput;
        std::vector<std::complex<double>> transformMask;
        std::vector<std::complex<double>> filter(image.width() * image.height(), 0.0);

        double cutoffFrequency = stod(getArguments());

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                int index = y * image.width() + x;
                int xx = abs(image.width()/2 - x);
                int yy = abs(image.height()/2 - y);
                filter[index] = 1 - exp(-(xx * xx + yy * yy) / (2 * cutoffFrequency * cutoffFrequency));

            }
        }

        for (int i = 0; i < transformOutput.size(); i++) {
            transformOutput[i] *= filter[i];
        }

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                if (mask(x, y, 0) == 0) {
                    transformOutput[image.width() * y + x] *= 0.0;
                } else {
                    transformOutput[image.width() * y + x] *= 1.0;
                }
            }
        }

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(transformOutput[image.width() * y + x].real(), 2) + pow(transformOutput[image.width() * y + x].imag(), 2));
                magnitude(x, y, 0) = 20 * log(1 + mag);
                magnitude(x, y, 1) = 20 * log(1 + mag);
                magnitude(x, y, 2) = 20 * log(1 + mag);
            }
        }

        magnitude.save_bmp("../../../../images/hpfedmag.bmp");

        fft.inverse(transformOutput);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}
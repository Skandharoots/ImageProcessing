#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "LowPassFilter.h"
#include "CImg.h"
#include "FFT.h"

using namespace cimg_library;

LowPassFilter::LowPassFilter(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;
	
}

void LowPassFilter::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string LowPassFilter::getArguments() {
	return this->arguments;
}

LowPassFilter::~LowPassFilter() {
}

std::string LowPassFilter::getInputPath() {
	return this->inputPath;
}
void LowPassFilter::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string LowPassFilter::getOutputPath() {
	return this->outputPath;
}

void LowPassFilter::setOutputPath(std::string path) {
	this->outputPath = path;
}

void LowPassFilter::pass() {
	cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());

        FFT fft(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::complex<double>> transformOutput;
        std::vector<std::complex<double>> filter(image.width() * image.height(), 0.0);

        double cutoffFrequency = stod(getArguments());

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                int index = y * image.width() + x;
                filter[index] = exp(-(x * x + y * y) / (2 * cutoffFrequency * cutoffFrequency));
            }
        }

        transformOutput = fft.forward();

        for (int i = 0; i < transformOutput.size(); i++) {
            transformOutput[i] *= filter[i];
        }

        fft.inverse(transformOutput);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}
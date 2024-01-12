#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "HighPassFilter.h"
#include "CImg.h"
#include "FFT.h"

using namespace cimg_library;

HighPassFilter::HighPassFilter(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;
	
}

void HighPassFilter::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string HighPassFilter::getArguments() {
	return this->arguments;
}

HighPassFilter::~HighPassFilter() {
}

std::string HighPassFilter::getInputPath() {
	return this->inputPath;
}
void HighPassFilter::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string HighPassFilter::getOutputPath() {
	return this->outputPath;
}

void HighPassFilter::setOutputPath(std::string path) {
	this->outputPath = path;
}

void HighPassFilter::pass() {
	cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> magnitude(getInputPath().c_str());


        FFT fft(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::complex<double>> transformOutput;
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

        transformOutput = fft.forward();

        for (int i = 0; i < transformOutput.size(); i++) {
            transformOutput[i] *= filter[i];
        }
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(transformOutput[image.width() * y + x].real(), 2) + pow(transformOutput[image.width() * y + x].imag(), 2));
                magnitude(x, y, 0) = 20 * log(1 + mag);
                magnitude(x, y, 1) = 20 * log(1 + mag);
                magnitude(x, y, 2) = 20 * log(1 + mag);
            }
        }

        magnitude.save_bmp("../../../../images/hpfmag.bmp");

        fft.inverse(transformOutput);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}
#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "PhaseModification.h"
#include "CImg.h"
#include "FastFourierTransform.h"

using namespace cimg_library;

PhaseModification::PhaseModification(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;
	
}

void PhaseModification::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string PhaseModification::getArguments() {
	return this->arguments;
}

PhaseModification::~PhaseModification() {
}

std::string PhaseModification::getInputPath() {
	return this->inputPath;
}
void PhaseModification::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string PhaseModification::getOutputPath() {
	return this->outputPath;
}

void PhaseModification::setOutputPath(std::string path) {
	this->outputPath = path;
}

void PhaseModification::pass() {
	cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> magnitude(getInputPath().c_str());
        CImg<unsigned char> mag(getInputPath().c_str());

        FastFourierTransform fft(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<double> matrix;
        std::vector<std::complex<double>> transformOutput;
        std::vector<std::complex<double>> transformCentered;
        std::vector<std::complex<double>> resultDecentered;
        std::vector<std::complex<double>> result;
        std::vector<std::complex<double>> filter(image.width() * image.height(), 0.0);

        std::complex<double> i;
        i = -1;
        i = sqrt(i);

        std::string cutoffFrequencies = getArguments();
        auto space = cutoffFrequencies.find(' ');
        double k = stod(cutoffFrequencies.substr(0, space));
        double l = stod(cutoffFrequencies.substr(space + 1));

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                int index = x * image.width() + y;
                filter[index] = exp(-i * 2.0 * M_PI * (((x * k) / image.width()) + ((y * l) / image.height())));
            }
        }

        matrix = fft.forward();
        transformOutput = fft.fft(matrix);
        transformCentered = fft.center(transformOutput);

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double magnitude = sqrt(pow(transformCentered[image.width() * x + y].real(), 2) + pow(transformCentered[image.width() * x + y].imag(), 2));
                mag(x, y, 0) = 20 * log(1 + magnitude);
                mag(x, y, 1) = 20 * log(1 + magnitude);
                mag(x, y, 2) = 20 * log(1 + magnitude);
            }
        }
        mag.save_bmp("../../../../images/fftmag.bmp");

        for (int i = 0; i < transformCentered.size(); i++) {
            transformCentered[i] *= filter[i];
        }

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(transformCentered[image.width() * x + y].real(), 2) + pow(transformCentered[image.width() * x + y].imag(), 2));
                magnitude(x, y, 0) = 20 * log(1 + mag);
                magnitude(x, y, 1) = 20 * log(1 + mag);
                magnitude(x, y, 2) = 20 * log(1 + mag);
            }
        }
        magnitude.save_bmp("../../../../images/pmfmag.bmp");

        resultDecentered = fft.center(transformCentered);
        result = fft.ifft(resultDecentered);

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                result[image.width() * x + y] = result[image.width() * x + y] / ((double) result.size());
                double mag = sqrt(pow(result[image.width() * x + y].real(), 2) + pow(result[image.width() * x + y].imag(), 2));
                if (mag < 0) {
                    image(x, y, 0) = 0;
                    image(x, y, 1) = 0;
                    image(x, y, 2) = 0;
                } else if (mag > 255) {
                    image(x, y, 0) = 255;
                    image(x, y, 1) = 255;
                    image(x, y, 2) = 255;
                } else {
                    image(x, y, 0) = mag;
                    image(x, y, 1) = mag;
                    image(x, y, 2) = mag;
                }

            }
        }
        image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}
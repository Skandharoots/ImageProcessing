#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include <memory>
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

        std::shared_ptr<FastFourierTransform> fft = std::make_shared<FastFourierTransform>(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::vector<std::complex<double>>> matrix;
        std::vector<std::vector<std::complex<double>>> result;
        std::vector<std::vector<std::complex<double>>> filter(image.width(), std::vector<std::complex<double>>(image.height(), 0.0));

        std::complex<double> i;
        i = -1;
        i = sqrt(i);

        std::string cutoffFrequencies = getArguments();
        auto space = cutoffFrequencies.find(' ');
        double k = stod(cutoffFrequencies.substr(0, space));
        double l = stod(cutoffFrequencies.substr(space + 1));

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                filter[x][y] = exp(i * (((-x * k * 2.0 * M_PI) / image.width()) + ((-y * l * 2.0 * M_PI) / image.height()) + ((k + l) * M_PI)));
            }
        }

        matrix = fft->forward();

        double max = 0.0;
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double magnitude = sqrt(pow(matrix[x][y].real(), 2) + pow(matrix[x][y].imag(), 2));
                if (magnitude > max) {
                    max = magnitude;
                }
            }
        }
        double c = 255 / log(1 + abs(max));

        fft->drawSpectrum(matrix, "../../../images/fftmag.bmp", c);

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                matrix[x][y] *= filter[x][y];
            }
        }

        fft->drawSpectrum(matrix, "../../../images/pmfmag.bmp", c);

        result = fft->inverse(matrix);

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(result[x][y].real(), 2) + pow(result[x][y].imag(), 2));
                image(x, y, 0) = mag;
                image(x, y, 1) = mag;
                image(x, y, 2) = mag;
            }
        }
        image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}
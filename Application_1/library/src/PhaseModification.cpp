#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "PhaseModification.h"
#include "CImg.h"
#include "FFT.h"

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

        FFT fft(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::complex<double>> transformOutput;
        std::vector<std::complex<double>> transformCentered(image.width() * image.height(), 0.0);
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
                int index = y * image.width() + x;
                int xx = abs(image.width()/2 - x);
                int yy = abs(image.height()/2 - y);
                filter[index] = exp(i * (((-xx * k * 2 * M_PI) / image.width()) + ((-yy * l * 2 * M_PI) / image.height()) + ((k + l) * M_PI)));
            }
        }

        transformOutput = fft.forward();

        for (int x = 0; x < image.width() / 2; x++) {
            for (int y = 0; y < image.height() / 2; y++) {
                transformCentered[(x + (image.width()/2)) + (y + image.height()/2) * image.width()] = transformOutput[image.width() * y + x];
            }
        }
        for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
            for (int y = 0; y < image.height() / 2; y++) {
                transformCentered[(x - (image.width()/2)) + (y + image.height()/2) * image.width()] = transformOutput[image.width() * y + x];
            }
        }
        for (int x = 0; x < image.width() / 2; x++) {
            for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
                transformCentered[(x + (image.width()/2)) + (y - image.height()/2) * image.width()] = transformOutput[image.width() * y + x];
            }
        }
        for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
            for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
                transformCentered[(x - (image.width()/2)) + (y - image.height()/2) * image.width()] = transformOutput[image.width() * y + x];
            }
        }
        for (int i = 0; i < transformOutput.size(); i++) {
            transformCentered[i] *= filter[i];
        }
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(transformCentered[image.width() * y + x].real(), 2) + pow(transformCentered[image.width() * y + x].imag(), 2));
                magnitude(x, y, 0) = 20 * log(1 + mag);
                magnitude(x, y, 1) = 20 * log(1 + mag);
                magnitude(x, y, 2) = 20 * log(1 + mag);
            }
        }
        magnitude.save_bmp("../../../../images/pmfmag.bmp");
        for (int x = 0; x < image.width() / 2; x++) {
            for (int y = 0; y < image.height() / 2; y++) {
                transformOutput[(x + (image.width()/2)) + (y + image.height()/2) * image.width()] = transformCentered[image.width() * y + x];
            }
        }
        for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
            for (int y = 0; y < image.height() / 2; y++) {
                transformOutput[(x - (image.width()/2)) + (y + image.height()/2) * image.width()] = transformCentered[image.width() * y + x];
            }
        }
        for (int x = 0; x < image.width() / 2; x++) {
            for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
                transformOutput[(x + (image.width()/2)) + (y - image.height()/2) * image.width()] = transformCentered[image.width() * y + x];
            }
        }
        for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
            for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
                transformOutput[(x - (image.width()/2)) + (y - image.height()/2) * image.width()] = transformCentered[image.width() * y + x];
            }
        }
        fft.inverse(transformOutput);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}
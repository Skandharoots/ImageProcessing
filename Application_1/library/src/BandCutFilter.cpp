#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "BandCutFilter.h"
#include "CImg.h"
#include "FFT.h"

using namespace cimg_library;

BandCutFilter::BandCutFilter(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;
	
}

void BandCutFilter::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string BandCutFilter::getArguments() {
	return this->arguments;
}

BandCutFilter::~BandCutFilter() {
}

std::string BandCutFilter::getInputPath() {
	return this->inputPath;
}
void BandCutFilter::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string BandCutFilter::getOutputPath() {
	return this->outputPath;
}

void BandCutFilter::setOutputPath(std::string path) {
	this->outputPath = path;
}

void BandCutFilter::pass() {
	cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> magnitude(getInputPath().c_str());


        FFT fft(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::complex<double>> transformOutput;
        std::vector<std::complex<double>> transformCentered(image.width() * image.height(), 0.0);
        std::vector<std::complex<double>> filterBandCut(image.width() * image.height(), 0.0);

        std::string cutoffFrequencies = getArguments();
        auto space = cutoffFrequencies.find(' ');
        double lowCut = stod(cutoffFrequencies.substr(0, space));
        double highCut = stod(cutoffFrequencies.substr(space + 1));

        double radialCenter = (lowCut + highCut) / 2;
        double bandWidth = highCut - lowCut;

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                int index = y * image.width() + x;
                int xx = abs(image.width()/2 - x);
                int yy = abs(image.height()/2 - y);
                if(sqrt(xx * xx + yy * yy) <= (radialCenter - (bandWidth / 2))
                || sqrt(xx * xx + yy * yy) >= (radialCenter + (bandWidth / 2))) {
                    filterBandCut[index] = 1;
                }
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
            transformCentered[i] *= filterBandCut[i];
        }
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(transformCentered[image.width() * y + x].real(), 2) + pow(transformCentered[image.width() * y + x].imag(), 2));
                magnitude(x, y, 0) = 20 * log(1 + mag);
                magnitude(x, y, 1) = 20 * log(1 + mag);
                magnitude(x, y, 2) = 20 * log(1 + mag);
            }
        }

        magnitude.save_bmp("../../../../images/bcfmag.bmp");

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
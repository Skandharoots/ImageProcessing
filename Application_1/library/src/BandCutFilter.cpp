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

        FFT fft(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::complex<double>> transformOutput;
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
                if(sqrt(x * x + y * y) <= (radialCenter - (bandWidth / 2))
                || sqrt(x * x + y * y) >= (radialCenter + (bandWidth / 2))) {
                    filterBandCut[index] = 1;
                }
            }
        }

        transformOutput = fft.forward();

        for (int i = 0; i < transformOutput.size(); i++) {
            transformOutput[i] *= filterBandCut[i];
        }

        fft.inverse(transformOutput);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}
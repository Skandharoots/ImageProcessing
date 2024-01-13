#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "BandPassFilter.h"
#include "CImg.h"
#include "FFT.h"

using namespace cimg_library;

BandPassFilter::BandPassFilter(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;
	
}

void BandPassFilter::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string BandPassFilter::getArguments() {
	return this->arguments;
}

BandPassFilter::~BandPassFilter() {
}

std::string BandPassFilter::getInputPath() {
	return this->inputPath;
}
void BandPassFilter::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string BandPassFilter::getOutputPath() {
	return this->outputPath;
}

void BandPassFilter::setOutputPath(std::string path) {
	this->outputPath = path;
}

void BandPassFilter::pass() {
	cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());

        FFT fft(getInputPath().c_str(), getOutputPath().c_str());
        CImg<unsigned char> magnitude(getInputPath().c_str());


        std::vector<std::complex<double>> transformOutput;
        std::vector<std::complex<double>> result;
        std::vector<std::complex<double>> filterBandPass(image.width() * image.height(), 0.0);

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
                if(sqrt(xx * xx + yy * yy) >= (radialCenter - (bandWidth / 2))
                && sqrt(xx * xx + yy * yy) <= (radialCenter + (bandWidth / 2))) {
                    filterBandPass[index] = 1;
                }
            }
        }

        transformOutput = fft.forward();

        for (int i = 0; i < transformOutput.size(); i++) {
            transformOutput[i] *= filterBandPass[i];
        }
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(transformOutput[image.width() * y + x].real(), 2) + pow(transformOutput[image.width() * y + x].imag(), 2));
                magnitude(x, y, 0) = 20 * log(1 + mag);
                magnitude(x, y, 1) = 20 * log(1 + mag);
                magnitude(x, y, 2) = 20 * log(1 + mag);
            }
        }

        magnitude.save_bmp("../../../../images/bpfmag.bmp");

        result = fft.inverse(transformOutput);

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double pls = result[image.width() * y + x].real();
                if ((pls + 128) > 255) {
                    image(x, y, 0) = 255;
                    image(x, y, 1) = 255;
                    image(x, y, 2) = 255;
                }
                else if ((pls + 128) < 0) {
                    image(x, y, 0) = 0;
                    image(x, y, 1) = 0;
                    image(x, y, 2) = 0;
                }
                else {
                    image(x, y, 0) = pls + 128;
                    image(x, y, 1) = pls + 128;
                    image(x, y, 2) = pls + 128;
                }
            }
        }
        image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}
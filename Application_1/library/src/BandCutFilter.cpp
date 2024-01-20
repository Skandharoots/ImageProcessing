#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include <memory>
#include "BandCutFilter.h"
#include "CImg.h"
#include "FastFourierTransform.h"

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
        CImg<unsigned char> mag(getInputPath().c_str());


        std::shared_ptr<FastFourierTransform> fft = std::make_shared<FastFourierTransform>(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::vector<std::complex<double>>> matrix;
        std::vector<std::vector<std::complex<double>>> result;
        std::vector<std::vector<std::complex<double>>> filter(image.width(), std::vector<std::complex<double>>(image.height(), 0.0));

        std::string cutoffFrequencies = getArguments();
        auto space = cutoffFrequencies.find(' ');
        double lowCut = stod(cutoffFrequencies.substr(0, space));
        double highCut = stod(cutoffFrequencies.substr(space + 1));

        double radialCenter = (lowCut + highCut) / 2;
        double bandWidth = highCut - lowCut;

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                int xx = abs(image.width()/2 - x);
                int yy = abs(image.height()/2 - y);
                if(sqrt(xx * xx + yy * yy) <= (radialCenter - (bandWidth / 2))
                || sqrt(xx * xx + yy * yy) >= (radialCenter + (bandWidth / 2))) {
                    filter[x][y] = 1;
                }
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

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double magnitude = sqrt(pow(matrix[x][y].real(), 2) + pow(matrix[x][y].imag(), 2));
                if (c * log(1 + magnitude) < 0) {
                    mag(x, y, 0) = 0;
                    mag(x, y, 1) = 0;
                    mag(x, y, 2) = 0;
                } else if (c * log(1 + magnitude) > 255) {
                    mag(x, y, 0) = 255;
                    mag(x, y, 1) = 255;
                    mag(x, y, 2) = 255;
                } else {
                    mag(x, y, 0) = c * log(1 + magnitude);
                    mag(x, y, 1) = c * log(1 + magnitude);
                    mag(x, y, 2) = c * log(1 + magnitude);
                }

            }
        }
        mag.save_bmp("../../../../images/fftmag.bmp");

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                matrix[x][y] *= filter[x][y];
            }
        }

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(matrix[x][y].real(), 2) + pow(matrix[x][y].imag(), 2));
                if (c * log(1 + mag) < 0) {
                    magnitude(x, y, 0) = 0;
                    magnitude(x, y, 1) = 0;
                    magnitude(x, y, 2) = 0;
                } else if (c * log(1 + mag) > 255) {
                    magnitude(x, y, 0) = 255;
                    magnitude(x, y, 1) = 255;
                    magnitude(x, y, 2) = 255;
                } else {
                    magnitude(x, y, 0) = c * log(1 + mag);
                    magnitude(x, y, 1) = c * log(1 + mag);
                    magnitude(x, y, 2) = c * log(1 + mag);
                }
            }
        }
        magnitude.save_bmp("../../../../images/bcfmag.bmp");

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
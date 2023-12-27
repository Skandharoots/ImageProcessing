#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include "FFT.h"
#include "CImg.h"

using namespace cimg_library;
typedef std::complex<double> dcomp;

FFT::FFT(std::string inputPath, std::string outputPath) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
}

FFT::~FFT() {
}

std::string FFT::getInputPath() {
	return this->inputPath;
}
void FFT::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string FFT::getOutputPath() {
	return this->outputPath;
}

void FFT::setOutputPath(std::string path) {
	this->outputPath = path;
}

void FFT::transform() {

	cimg::exception_mode(0);
	try {
        dcomp i;
        i = -1;
        i = sqrt(i);
		CImg<unsigned char> image(getInputPath().c_str());
		CImg<unsigned char> image2(image.width(), image.height(), 1, 3);
        dcomp sum;
        dcomp sum2;

        for(int i = 0; i < image.width(); i++) {
            for(int j = 0; j < image.height(); j++) {
                image2(i, j, 0) = 0;
                image2(i, j, 1) = 0;
                image2(i, j, 2) = 0;
            }
        }

        int k = 0;
        for(int x = 0; x < image.width(); x++) {
            for(int y = 0; y < image.height(); y++) {
                //image2(i, j, 0) = image(i, j, 0) * exp(-i*2*M_PI*image(i, j, 0)*k/image.height())
                sum += image(x, y, 0) * exp(-i*2*3.1415926*x*k/image.height());
            }
        }
		image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::exception("Cannot load or save from the path. Path invalid.\n");
	}
}
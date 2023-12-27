#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <iostream>
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
		CImg<unsigned char> image2(getInputPath().c_str());
        CImg<unsigned char> image3(getInputPath().c_str());
        double real = 0;
        double imaginary = 0;
        double result = 0;
        float avg = 0;
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                avg = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
                image(x, y, 0) = avg;
                image(x, y, 1) = avg;
                image(x, y, 2) = avg;
                avg = 0;
            }
        }

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                // for (int xx = 0; xx < image.width(); xx++) {
                //     real += image(xx, y, 0) * cos((2.0 * 3.1415926 * x * xx) / image.height());
                //     imaginary += image(xx, y, 0) * -1 * sin((2.0 * 3.1415926 * x * xx) / image.height());
                // }
                for (int yy = 0; yy < image.height(); yy++) {
                    real += image(x, yy, 0) * cos((2.0 * 3.1415926 * y * yy) / image.height());
                    imaginary += image(x, yy, 0) * -1 * sin((2.0 * 3.1415926 * y * yy) / image.height());
                }
                result = sqrt(pow(real, 2) + pow(imaginary, 2));
                image2(x, y, 0) = result;
                image2(x, y, 1) = result;
                image2(x, y, 2) = result;
                real = 0;
                imaginary = 0;
                result = 0;

            }
        }
        real = 0;
        imaginary = 0;
        result = 0;
        for (int x = 0; x < image2.width(); x++) {
            for (int y = 0; y < image2.height(); y++) {
                // for (int yy = 0; yy < image.height(); yy++) {
                //     real += image2(x, yy, 0) * cos((2.0 * 3.1415926 * y * yy) / image2.height());
                //     imaginary += image2(x, yy, 0) * -1 * sin((2.0 * 3.1415926 * y * yy) / image2.height());
                // }
                for (int xx = 0; xx < image2.width(); xx++) {
                    real += image2(xx, y, 0) * cos((2.0 * 3.1415926 * x * xx) / image2.width());
                    imaginary += image2(xx, y, 0) * -1 * sin((2.0 * 3.1415926 * x * xx) / image2.width());
                }
                result = sqrt(pow(real, 2) + pow(imaginary, 2));
                image3(x, y, 0) = result;
                image3(x, y, 1) = result;
                image3(x, y, 2) = result;
                real = 0;
                imaginary = 0;
                result = 0;
            }
        }

        
        // for (int x = 0; x < image.width(); x++) {
        //     for (int y = 0; y < image.height(); y++) {
        //         for (int yy = 0; yy < image.height(); yy++) {
        //             real += image(x, yy, 0) * cos((2.0 * 3.1415926 * y * yy) / image.height());
        //             imaginary += image(x, yy, 0) * -1 * sin((2.0 * 3.1415926 * y * yy) / image.height());
        //         }
        //         for (int xx = 0; xx < image.width(); xx++) {
        //             real += image(xx, y, 0) * cos((2.0 * 3.1415926 * x * xx) / image.height());
        //             imaginary += image(xx, y, 0) * -1 *sin((2.0 * 3.1415926 * x * xx) / image.height());
        //         }
        //         result = sqrt(pow(real, 2) + pow(imaginary, 2));
        //         image2(x, y, 0) = result;
        //         image2(x, y, 1) = result;
        //         image2(x, y, 2) = result;

        //         real = 0;
        //         imaginary = 0;
        //         result = 0;
        //     } 
        // }
		image3.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::exception("Cannot load or save from the path. Path invalid.\n");
	}
}
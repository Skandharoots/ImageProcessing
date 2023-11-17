#include <string>
#include <iostream>
#include "CImg.h"
#include "LinearFilter.h"

using namespace cimg_library;


LinearFilter::LinearFilter(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
    this->inputPath = inputPath;
    this->outputPath = outputPath;
}

LinearFilter::~LinearFilter() {

}

std::string LinearFilter::getInputPath() {
    return this->inputPath;
}

void LinearFilter::setInputPath(std::string path) {
    this->inputPath = path;
}

std::string LinearFilter::getOutputPath() {
    return this->outputPath;
}

void LinearFilter::setOutputPath(std::string path) {
    this->outputPath = path;
}

std::string LinearFilter::getArguments() {
    return this->arguments;
}

void LinearFilter::setArguments(std::string path) {
    this->arguments = arguments;
}

void LinearFilter::setMask(int mask[]) {
    if (getArguments() == "-e1") {
            mask[0] = 0;
            mask[1] = -1;
            mask[2] = 0;
            mask[3] = -1;
            mask[4] = 5;
            mask[5] = -1;
            mask[6] = -0;
            mask[7] = -1;
            mask[8] = 0;
        } else if (getArguments() == "-e2") {
            mask[0] = -1;
            mask[1] = -1;
            mask[2] = -1;
            mask[3] = -1;
            mask[4] = 9;
            mask[5] = -1;
            mask[6] = -1;
            mask[7] = -1;
            mask[8] = -1;
        } else if (getArguments() == "-e3") {
            mask[0] = 1;
            mask[1] = -2;
            mask[2] = 1;
            mask[3] = -2;
            mask[4] = 5;
            mask[5] = -2;
            mask[6] = 1;
            mask[7] = -2;
            mask[8] = 1;
        } else {
            throw std::exception("Wrong arguments. Type --help for options");
        }
}

void LinearFilter::linearFilter() {

    cimg::exception_mode(0);
	try {
        
        CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        float sum0 = 0;
        float sum1 = 0;
        float sum2 = 0;
        int k = 0;
        int mask[9];
        setMask(mask);
        for (int x = 1; x < image.width() - 1; x++) {
            for (int y = 1; y < image.height() - 1; y++) {
                for (int i = y - 1; i < y + 2; i++) {
                    for (int j = x - 1; j < x + 2; j++) {
                        sum0 += mask[k] * copy(j, i, 0);
                        sum1 += mask[k] * copy(j, i, 1);
                        sum2 += mask[k] * copy(j, i, 2);
                        k++;
                    }
                }
                if (sum0 > 255) {
                    image(x, y, 0) = 255;
                } else if (sum0 < 0) {
                    image(x, y, 0) = 0;                    
                } else {
                    image(x, y, 0) = sum0;
                }
                if (sum1 > 255) {
                    image(x, y, 1) = 255;
                } else if (sum1 < 0) {
                    image(x, y, 1) = 0;                    
                } else {
                    image(x, y, 1) = sum1;
                }
                if (sum2 > 255) {
                    image(x, y, 2) = 255;
                } else if (sum2 < 0) {
                    image(x, y, 2) = 0;                    
                } else {
                    image(x, y, 2) = sum2;
                }
                //image(x, y, 1) = sum1;
                //image(x, y, 2) = sum2;

                k = 0;
                sum0 = 0;
                sum1 = 0;
                sum2 = 0;
            }
        }
        image.save_bmp(getOutputPath().c_str());
    
    } catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	} catch (std::exception &e) {
        throw std::exception(e.what());
    }
}
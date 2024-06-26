#include <string>
#include <iostream>
#include <vector>
#include "CImg.h"
#include "LinearFilterOptimized.h"

using namespace cimg_library;


LinearFilterOptimized::LinearFilterOptimized(std::string inputPath, std::string outputPath) {
    this->inputPath = inputPath;
    this->outputPath = outputPath;
}

LinearFilterOptimized::~LinearFilterOptimized() {

}

std::string LinearFilterOptimized::getInputPath() {
    return this->inputPath;
}

void LinearFilterOptimized::setInputPath(std::string path) {
    this->inputPath = path;
}

std::string LinearFilterOptimized::getOutputPath() {
    return this->outputPath;
}

void LinearFilterOptimized::setOutputPath(std::string path) {
    this->outputPath = path;
}

void LinearFilterOptimized::setMask(int mask[]) {
    mask[0] = -1;
    mask[1] = -1;
    mask[2] = -1;
    mask[3] = -1;
    mask[4] = 9;
    mask[5] = -1;
    mask[6] = -1;
    mask[7] = -1;
    mask[8] = -1;
    std::cout << "Mask set for N optimalization." << std::endl;
}


void LinearFilterOptimized::linearFilter() {

    cimg::exception_mode(0);
	try {
        
        CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        int mask[9];
        float sum0 = 0;
        setMask(mask);
        for (int x = 1; x < image.width() - 1; x++) {
            for (int y = 1; y < image.height() - 1; y++) {
                sum0 -= copy(x-1, y-1, 0);
                sum0 -= copy(x, y-1, 0);
                sum0 -= copy(x+1, y-1, 0);
                sum0 -= copy(x-1, y, 0);
                
                sum0 -= copy(x+1, y, 0);
                sum0 -= copy(x-1, y+1, 0);
                sum0 -= copy(x, y+1, 0);
                sum0 -= copy(x+1, y+1, 0);
                sum0 += mask[4] * copy(x, y, 0);
                if (sum0 > 255) {
                    image(x, y, 0) = 255;
                    image(x, y, 1) = 255;
                    image(x, y, 2) = 255;
                } else if (sum0 < 0) {
                    image(x, y, 0) = 0;
                    image(x, y, 1) = 0;
                    image(x, y, 2) = 0;                   
                } else {
                    image(x, y, 0) = sum0;
                    image(x, y, 1) = sum0;
                    image(x, y, 2) = sum0;
                }
                sum0 = 0;
                
            }
        }
        image.save_bmp(getOutputPath().c_str());
    
    } catch (CImgIOException e) {
		throw std::logic_error("There was a problem with opening or saving a file. Path not valid.");
	}
}
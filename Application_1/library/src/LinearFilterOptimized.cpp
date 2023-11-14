#include <string>
#include <iostream>
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
    mask[0] = 1;
    mask[1] = 1;
    mask[2] = 1;
    mask[3] = 1;
    mask[4] = -2;
    mask[5] = 1;
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
        float sum0 = 0;
        float sum1 = 0;
        float sum2 = 0;
        int k = 0;
        int mask[9];
        int saved1[3][3];
        int saved2[3][3];
        int x1_offset = 2;
        int x2_offset = 3;
        int y_offset = 0;
        int yo = 0;
        setMask(mask);
        
        for (int y = 1; y < image.height() - 1; y++) {
            for (int x = 1; x < image.width() - 1; x++) {
                for (int i = y - 1; i < y + 2; i++) {
                    for (int j = x - 1; j < x + 2; j++) {
                        if ((j == x1_offset) && (x > x1_offset)) {
                            sum0 += saved1[0][yo];
                            sum1 += saved1[1][yo];
                            sum2 += saved1[2][yo];
                            
                        } else if ((j == x2_offset) && (x > x2_offset)) {
                            sum0 += saved2[0][yo];
                            sum1 += saved2[1][yo];
                            sum2 += saved2[2][yo];
                        }
                         else {
                            sum0 += mask[k] * copy(j, i, 0);
                            sum1 += mask[k] * copy(j, i, 1);
                            sum2 += mask[k] * copy(j, i, 2);
                        }
                        k++;
                    }
                    yo += 1;
                }
                image(x, y, 0) = sum0;
                image(x, y, 1) = sum1;
                image(x, y, 2) = sum2; 
                k = 0;
                yo = 0;
                sum0 = 0;
                sum1 = 0;
                sum2 = 0;
                if (x == x1_offset + 1) {
                    x1_offset += 2;
                    for (int k = 0; k < 3; k++) {
                        saved1[k][0] = copy(x1_offset, y_offset, k);
                        saved1[k][1] = copy(x1_offset, y_offset + 1, k);
                        saved1[k][2] = -copy(x1_offset, y_offset + 2, k);
                    }   
                }
                else if (x == x2_offset + 1) {
                    x2_offset += 2;
                    for (int k = 0; k < 3; k++) {
                        saved2[k][0] = copy(x2_offset, y_offset, k);
                        saved2[k][1] = copy(x2_offset, y_offset + 1, k);
                        saved2[k][2] = -copy(x2_offset, y_offset + 2, k);
                    }   
                }
            }
            y_offset += 1;
            x1_offset = 2;
            x2_offset = 3;
        }
        image.save_bmp(getOutputPath().c_str());
    
    } catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	}
}
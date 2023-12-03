#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include "CImg.h"
#include "Opening.h"

using namespace cimg_library;

Opening::Opening(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
	
}

Opening::~Opening() {

}

void Opening::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string Opening::getArguments() {
	return this->arguments;
}

std::string Opening::getInputPath() {
	return this->input;
}

void Opening::setInputPath(std::string path) {
	this->input = path;
}

std::string Opening::getOutputPath() {
	return this->output;
}

void Opening::setOutputPath(std::string path) {
	this->output = path;
}

void Opening::setMatrix(int matrix[]) {
    if (getArguments() == "1") {
            matrix[0] = -1;
            matrix[1] = -1;
            matrix[2] = -1;
            matrix[3] = -1;
            matrix[4] = 1;
            matrix[5] = 1;
            matrix[6] = -1;
            matrix[7] = -1;
            matrix[8] = -1;
        } else if (getArguments() == "2") {
            matrix[0] = -1;
            matrix[1] = -1;
            matrix[2] = -1;
            matrix[3] = -1;
            matrix[4] = 1;
            matrix[5] = -1;
            matrix[6] = -1;
            matrix[7] = 1;
            matrix[8] = -1;
        } else if (getArguments() == "3") {
            matrix[0] = 1;
            matrix[1] = 1;
            matrix[2] = 1;
            matrix[3] = 1;
            matrix[4] = 1;
            matrix[5] = 1;
            matrix[6] = 1;
            matrix[7] = 1;
            matrix[8] = 1;
        } else if (getArguments() == "4") {
            matrix[0] = -1;
            matrix[1] = 1;
            matrix[2] = -1;
            matrix[3] = 1;
            matrix[4] = 1;
            matrix[5] = 1;
            matrix[6] = -1;
            matrix[7] = 1;
            matrix[8] = -1;
        } else {
            throw std::exception("Wrong arguments. Type --help for options");
        }
}

void Opening::opening() {
	try {
        //Setting up the matrix
        int matrix[9];
        setMatrix(matrix);
        //Initializing needed images using CImg library
		CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> erosion(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        //Erosion on original image
		for (int x = 1; x < image.width() - 1; x++) {
			for (int y = 1; y < image.height() - 1; y++) {
                short int k = 0;
                short int l = 0;
                for (int i = y - 1; i < y + 2; i++) { 
                    for (int j = x - 1; j < x + 2; j++) { 
                        if (image(j, i) != 255 && matrix[k] == 1) {
                            l = 1;
                        }
                        k++;
                    }
                }
                if (l) {
                    erosion(x, y, 0) = 0;
                    erosion(x, y, 1) = 0;
                    erosion(x, y, 2) = 0;
                }
                else {
                    erosion(x, y, 0) = 255;
                    erosion(x, y, 1) = 255;
                    erosion(x, y, 2) = 255;
                }
			}
		}
        for (int x = 0; x < erosion.width(); x++) {
            for (int y = 0; y < erosion.height(); y++) {
                copy(x, y, 0) = erosion(x, y, 0);
                copy(x, y, 1) = erosion(x, y, 1);
                copy(x, y, 2) = erosion(x, y, 2);
            }
        }
        //Dilation on processed image
        for (int x = 1; x < image.width() - 1; x++) {
			for (int y = 1; y < image.height() - 1; y++) {
                short int k = 0;
                for (int i = y - 1; i < y + 2; i++) { 
                    for (int j = x - 1; j < x + 2; j++) { 
                        if (erosion(j, i) == 255 && matrix[k] == 1) {
                            copy(x, y, 0) = 255;
                            copy(x, y, 1) = 255;
                            copy(x, y, 2) = 255;
                        }
                        k++;
                    }
                }
			}
		}
        //Saving file
		copy.save_bmp(getOutputPath().c_str());
	} catch (CImgIOException e) {
		throw std::exception("Cannot open or save file from path provided. Path is invalid.\n");
	} catch (std::exception& e) {
		throw std::exception(e.what());
	}
}
#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include "CImg.h"
#include "Closing.h"

using namespace cimg_library;

Closing::Closing(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
	
}

Closing::~Closing() {

}

void Closing::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string Closing::getArguments() {
	return this->arguments;
}

std::string Closing::getInputPath() {
	return this->input;
}

void Closing::setInputPath(std::string path) {
	this->input = path;
}

std::string Closing::getOutputPath() {
	return this->output;
}

void Closing::setOutputPath(std::string path) {
	this->output = path;
}

void Closing::setMatrix(int matrix[]) {
    if (getArguments() == "1") {
            matrix[0] = -1;
            matrix[1] = -1;
            matrix[2] = -1;
            matrix[3] = -1;
            matrix[4] = 0;
            matrix[5] = 0;
            matrix[6] = -1;
            matrix[7] = -1;
            matrix[8] = -1;
        } else if (getArguments() == "2") {
            matrix[0] = -1;
            matrix[1] = -1;
            matrix[2] = -1;
            matrix[3] = -1;
            matrix[4] = 0;
            matrix[5] = -1;
            matrix[6] = -1;
            matrix[7] = 0;
            matrix[8] = -1;
        } else if (getArguments() == "3") {
            matrix[0] = 0;
            matrix[1] = 0;
            matrix[2] = 0;
            matrix[3] = 0;
            matrix[4] = 0;
            matrix[5] = 0;
            matrix[6] = 0;
            matrix[7] = 0;
            matrix[8] = 0;
        } else if (getArguments() == "4") {
            matrix[0] = -1;
            matrix[1] = 0;
            matrix[2] = -1;
            matrix[3] = 0;
            matrix[4] = 0;
            matrix[5] = 0;
            matrix[6] = -1;
            matrix[7] = 0;
            matrix[8] = -1;
        } else {
            throw std::exception("Wrong arguments. Type --help for options");
        }
}

void Closing::closing() {
	try {
        //Setting up the matrix
        int matrix[9];
        setMatrix(matrix);
        //Initializing needed images using CImg library
		CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> dilation(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        //Dilation on original image
        for (int x = 1; x < image.width() - 1; x++) {
			for (int y = 1; y < image.height() - 1; y++) {
                short int k = 0;
                for (int i = y - 1; i < y + 2; i++) { 
                    for (int j = x - 1; j < x + 2; j++) { 
                        if (image(j, i) == 0 && matrix[k] == 0) {
                            dilation(x, y, 0) = 0;
                            dilation(x, y, 1) = 0;
                            dilation(x, y, 2) = 0;
                        }
                        k++;
                    }
                }
			}
		}
        for (int x = 0; x < dilation.width(); x++) {
            for (int y = 0; y < dilation.height(); y++) {
                copy(x, y, 0) = dilation(x, y, 0);
                copy(x, y, 1) = dilation(x, y, 1);
                copy(x, y, 2) = dilation(x, y, 2);
            }
        }
        //Erosion on processed image
		for (int x = 1; x < image.width() - 1; x++) {
			for (int y = 1; y < image.height() - 1; y++) {
                short int k = 0;
                short int l = 0;
                for (int i = y - 1; i < y + 2; i++) { 
                    for (int j = x - 1; j < x + 2; j++) { 
                        if (dilation(j, i) != 0 && matrix[k] == 0) {
                            l = 1;
                        }
                        k++;
                    }
                }
                if (l) {
                    copy(x, y, 0) = 255;
                    copy(x, y, 1) = 255;
                    copy(x, y, 2) = 255;
                }
                else {
                    copy(x, y, 0) = 0;
                    copy(x, y, 1) = 0;
                    copy(x, y, 2) = 0;
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
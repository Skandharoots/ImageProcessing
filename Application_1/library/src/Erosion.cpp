#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include "CImg.h"
#include "Erosion.h"

using namespace cimg_library;

Erosion::Erosion(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
	
}

Erosion::~Erosion() {

}

void Erosion::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string Erosion::getArguments() {
	return this->arguments;
}

std::string Erosion::getInputPath() {
	return this->input;
}

void Erosion::setInputPath(std::string path) {
	this->input = path;
}

std::string Erosion::getOutputPath() {
	return this->output;
}

void Erosion::setOutputPath(std::string path) {
	this->output = path;
}

void Erosion::setMatrix(int matrix[]) {
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
            throw std::logic_error("Wrong arguments. Type --help for options");
        }
}

void Erosion::erosion() {
	try {
        int matrix[9];
        short int n = 0;
        setMatrix(matrix);
		CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
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
                    copy(x, y, 0) = 0;
                    copy(x, y, 1) = 0;
                    copy(x, y, 2) = 0;
                }
                else {
                    copy(x, y, 0) = 255;
                    copy(x, y, 1) = 255;
                    copy(x, y, 2) = 255;
                }
			}
		}
		copy.save_bmp(getOutputPath().c_str());
	} catch (CImgIOException e) {
		throw std::logic_error("Cannot open or save file from path provided. Path is invalid.\n");
	} catch (std::logic_error& e) {
		throw std::logic_error(e.what());
	}
}
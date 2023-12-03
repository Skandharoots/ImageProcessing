#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include "CImg.h"
#include "HitAndMiss.h"

using namespace cimg_library;

HitAndMiss::HitAndMiss(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
	
}

HitAndMiss::~HitAndMiss() {

}

void HitAndMiss::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string HitAndMiss::getArguments() {
	return this->arguments;
}

std::string HitAndMiss::getInputPath() {
	return this->input;
}

void HitAndMiss::setInputPath(std::string path) {
	this->input = path;
}

std::string HitAndMiss::getOutputPath() {
	return this->output;
}

void HitAndMiss::setOutputPath(std::string path) {
	this->output = path;
}

void HitAndMiss::setMatrix(int matrix[]) {
    if (getArguments() == "11b") {
            matrix[0] = 1;
            matrix[1] = 1;
            matrix[2] = 1;
            matrix[3] = -1;
            matrix[4] = 0;
            matrix[5] = -1;
            matrix[6] = -1;
            matrix[7] = -1;
            matrix[8] = -1;
        } else if (getArguments() == "11c") {
            matrix[0] = -1;
            matrix[1] = -1;
            matrix[2] = 1;
            matrix[3] = -1;
            matrix[4] = 0;
            matrix[5] = 1;
            matrix[6] = -1;
            matrix[7] = -1;
            matrix[8] = 1;
        } else if (getArguments() == "11d") {
            matrix[0] = -1;
            matrix[1] = -1;
            matrix[2] = -1;
            matrix[3] = -1;
            matrix[4] = 0;
            matrix[5] = -1;
            matrix[6] = 1;
            matrix[7] = 1;
            matrix[8] = 1;
        } else if (getArguments() == "11a") {
            matrix[0] = 1;
            matrix[1] = -1;
            matrix[2] = -1;
            matrix[3] = 1;
            matrix[4] = 0;
            matrix[5] = -1;
            matrix[6] = 1;
            matrix[7] = -1;
            matrix[8] = -1;
        } else {
            throw std::exception("Wrong arguments. Type --help for options");
        }
}

void HitAndMiss::ham() {
	try {
        int matrix[9];
        short int n = 0;
        setMatrix(matrix);
		CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
		for (int x = 1; x < image.width() - 1; x++) {
			for (int y = 1; y < image.height() - 1; y++) {
                short int k = 0;
                short int match = 0;
                short int matchinact = 0;
                for (int i = y - 1; i < y + 2; i++) { 
                    for (int j = x - 1; j < x + 2; j++) { 
                        if (image(j, i) == 255 && matrix[k] == 1) {
                            match++;
                        } else if (image(j, i) == 0 && matrix[k] == 0) {
                            match++;
                        } else if (matrix[k] == -1) {
                            matchinact++;
                        }
                        else {
                            match += 0;
                        }
                        k++;
                    }
                }
                if (match == (9 - matchinact)) {
                    copy(x, y, 0) = 255;
                    copy(x, y, 1) = 255;
                    copy(x, y, 2) = 255;
                } else {
                    copy(x, y, 0) = 0;
                    copy(x, y, 1) = 0;
                    copy(x, y, 2) = 0;
                }
			}
		}
		copy.save_bmp(getOutputPath().c_str());
	} catch (CImgIOException e) {
		throw std::exception("Cannot open or save file from path provided. Path is invalid.\n");
	} catch (std::exception& e) {
		throw std::exception(e.what());
	}
}
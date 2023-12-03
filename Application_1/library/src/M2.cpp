#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include "CImg.h"
#include "M2.h"

using namespace cimg_library;

M2::M2(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
	
}

M2::~M2() {

}

void M2::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string M2::getArguments() {
	return this->arguments;
}

std::string M2::getInputPath() {
	return this->input;
}

void M2::setInputPath(std::string path) {
	this->input = path;
}

std::string M2::getOutputPath() {
	return this->output;
}

void M2::setOutputPath(std::string path) {
	this->output = path;
}

void M2::setMatrix(int matrix[]) {
            matrix[0] = -1;
            matrix[1] = 1;
            matrix[2] = -1;
            matrix[3] = 1;
            matrix[4] = 1;
            matrix[5] = 1;
            matrix[6] = -1;
            matrix[7] = 1;
            matrix[8] = -1;
}

void M2::operate() {
	try {
        int matrix[9];
        int myx;
        int myy;
        setMatrix(matrix);
		CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        std::cout << "Please give x coordinate between 0 and " << image.width() << std::endl;
        std::cin >> myx;
        std::cout << "Please give y coordinate between 0 and " << image.height() << std::endl;
        std::cin >> myy;
		
        short int k = 0;
            for (int i = myy - 1; i < myy + 2; i++) { 
                for (int j = myx - 1; j < myx + 2; j++) { 
                    if (image(j, i) == 255 && matrix[k] == 1) {
                        copy(myx, myy, 0) = 255;
                        copy(myx, myy, 1) = 255;
                        copy(myx, myy, 2) = 255;
                    }
                    k++;
                }
            }
            for (int i = myy - 1; i < myy + 2; i++) { 
                for (int j = myx - 1; j < myx + 2; j++) { 
                    if (image(j, i) == 255 && copy(j, i) == 0) {
                        copy(j, i) = 0;
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
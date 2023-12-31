#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include <stack>
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

bool M2::checkInput(int max, std::string input) {
    const std::regex parameter("[0-9]+");
    if (regex_match(input, parameter)) {
        if (stoi(input) <= max && stoi(input) > 0) {
            return true;
        } else {
            return false;
        }   
    }
}

void M2::operate() {
	try {
        int matrix[9];
        std::string myx;
        std::string myy;
        int mx;
        int my;
        bool check = false;
        setMatrix(matrix);
		CImg<unsigned char> A(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        CImg<unsigned char> complement(getInputPath().c_str());
        CImg<unsigned char> X(getInputPath().c_str());
        CImg<unsigned char> Y(A.width(), A.height(), 1, 3);
        CImgDisplay main_disp(A,"Click a point");
        while (!main_disp.is_closed()) {
            main_disp.wait();
            if (main_disp.button() && main_disp.mouse_y()>=0) {
                const int y = main_disp.mouse_y();
                const int x = main_disp.mouse_x();
                mx = x;
                my = y;
                if (mx != 0 && my != 0) {
                    main_disp.close();
                }
            }
        }

        for (int x = 0; x < X.width(); x++) {
            for (int y = 0; y < X.height(); y++) {
                X(x, y, 0) = 255;
                X(x, y, 1) = 255;
                X(x, y, 2) = 255;
                copy(x, y, 0) = 255;
                copy(x, y, 1) = 255;
                copy(x, y, 2) = 255;
            }
        }

        X(mx, my, 0) = 0;
        X(mx, my, 1) = 0;
        X(mx, my, 2) = 0;
        copy(mx, my, 0) = 0;
        copy(mx, my, 1) = 0;
        copy(mx, my, 2) = 0;

        for (int x = 0; x < A.width(); x++) {
            for (int y = 0; y < A.height(); y++) {
                    if (A(x, y, 0) == 0) {
                        complement(x, y, 0) = 255;
                        complement(x, y, 1) = 255;
                        complement(x, y, 2) = 255;
                    }
                    else {
                        complement(x, y, 0) = 0;
                        complement(x, y, 1) = 0;
                        complement(x, y, 2) = 0;
                    }
            }
        }
        
        //Dilation from point
        while(check==false) {
            int a = 0;
            int b = 0;
            for (int x = 1; x < A.width() - 1; x++) {
                for (int y = 1; y < A.height() - 1; y++) {
                    if(X(x, y) == 0) {
                        a++;
                    }
                }
            }

            for (int x = 1; x < A.width() - 1; x++) {
                for (int y = 1; y < A.height() - 1; y++) {
                    short int k = 0;
                    for (int i = y - 1; i < y + 2; i++) { 
                        for (int j = x - 1; j < x + 2; j++) { 
                            if (copy(j, i) == 0 && matrix[k] == 1) {
                                X(x, y, 0) = 0;
                                X(x, y, 1) = 0;
                                X(x, y, 2) = 0;
                            }
                            k++;
                        }
                    }
                }
            }

            for (int x = 1; x < A.width() - 1; x++) {
                for (int y = 1; y < A.height() - 1; y++) {
                    if (complement(x, y) == 0 && X(x, y) == 0) {
                        X(x, y, 0) = 0;
                        X(x, y, 1) = 0;
                        X(x, y, 2) = 0;
                    }
                    else {
                        X(x, y, 0) = 255;
                        X(x, y, 1) = 255;
                        X(x, y, 2) = 255;
                    }
                }
            }

            for (int x = 1; x < A.width() - 1; x++) {
                for (int y = 1; y < A.height() - 1; y++) {
                    copy(x, y, 0) = X(x, y, 0);
                    copy(x, y, 1) = X(x, y, 1);
                    copy(x, y, 2) = X(x, y, 2);
                }
            }

            for (int x = 1; x < A.width() - 1; x++) {
                for (int y = 1; y < A.height() - 1; y++) {
                    if(X(x, y) == 0) {
                        b++;
                    }
                }
            }

            if(a==b) {
                check = true;
            }
        }

        for (int x = 0; x < A.width(); x++) {
			for (int y = 0; y < A.height(); y++) {
                if (A(x, y) == 0 || X(x, y) == 0) {
                    Y(x, y, 0) = 0;
                    Y(x, y, 1) = 0;
                    Y(x, y, 2) = 0;
                }
                else {
                    Y(x, y, 0) = 255;
                    Y(x, y, 1) = 255;
                    Y(x, y, 2) = 255;
                }
                }
            }
            Y.save_bmp(getOutputPath().c_str());
        }
	catch (CImgIOException e) {
		throw std::logic_error("Cannot open or save file from path provided. Path is invalid.\n");
	}
}
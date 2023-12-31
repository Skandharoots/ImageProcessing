#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include <stack>
#include "CImg.h"
#include "RegionGrowing.h"

using namespace cimg_library;

RG::RG(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
	
}

RG::~RG() {

}

void RG::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string RG::getArguments() {
	return this->arguments;
}

std::string RG::getInputPath() {
	return this->input;
}

void RG::setInputPath(std::string path) {
	this->input = path;
}

std::string RG::getOutputPath() {
	return this->output;
}

void RG::setOutputPath(std::string path) {
	this->output = path;
}

void RG::regionGrowing() {
	try {
        int mx;
        int my;
        int t = stoi(getArguments());
        std::cout << t;
        std::stack<int> stack;
		CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        CImgDisplay main_disp(image,"Click a point");
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
        for (int x = 0; x < copy.width(); x++) {
			for (int y = 0; y < copy.height(); y++) {
                copy(x, y, 0) = 0;
                copy(x, y, 1) = 0;
                copy(x, y, 2) = 0;
			}
		}
        stack.push(mx);
        stack.push(my);
        // for (int x = 1; x < image.width() - 1; x++) {
        //     for (int y = 1; y < image.height() - 1; y++) {
                // if (image(mx, my, 0) == image(x, y, 0)) {
                do {
                    int myy = stack.top();
                    stack.pop();
                    int myx = stack.top();
                    stack.pop();
                    for (int i = myy - 1; i < myy + 2; i++) { 
                        for (int j = myx - 1; j < myx + 2; j++) {
                            if(abs(image(myx, myy, 0) - image(j, i, 0)) <= t && 
                            abs(image(myx, myy, 1) - image(j, i, 1)) <= t && 
                            abs(image(myx, myy, 2) - image(j, i, 2)) <= t && 
                            copy(j, i, 0) != 255 && 
                            (i > 0 && i < copy.height() - 1 && j > 0 && j < copy.width() - 1)) {
                            copy(j, i, 0) = 255;
                            copy(j, i, 1) = 255;
                            copy(j, i, 2) = 255;
                            stack.push(j);
                            stack.push(i);
                            }
                        }
                    }
                } while(!stack.empty());
                // copy(x, y, 0) = 255;
                // copy(x, y, 1) = 255;
                // copy(x, y, 2) = 255;
                // }
        //     }
        // }
		copy.save_bmp(getOutputPath().c_str());
	} catch (CImgIOException e) {
		throw std::logic_error("Cannot open or save file from path provided. Path is invalid.\n");
	} catch (std::logic_error& e) {
		throw std::logic_error(e.what());
	}
}
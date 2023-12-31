#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "CImg.h"
#include "Enlarge.h"

using namespace cimg_library;

Enlarge::Enlarge(std::string arguments, std::string inputPath, std::string outputPath) {
	this->arguments = arguments;
	this->input = inputPath;
	this->output = outputPath;
	
}

Enlarge::~Enlarge() {

}

void Enlarge::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string Enlarge::getArguments() {
	return this->arguments;
}

std::string Enlarge::getInputPath() {
	return this->input;
}

void Enlarge::setInputPath(std::string path) {
	this->input = path;
}

std::string Enlarge::getOutputPath() {
	return this->output;
}

void Enlarge::setOutputPath(std::string path) {
	this->output = path;
}

void Enlarge::setScale(float scale) {
	this->scale = scale;
}

float Enlarge::getScale() {
	return this->scale;
}

void Enlarge::convertArguments() {

	std::stringstream ss(getArguments());
	std::string del;
	std::vector<std::string> v;
	float temp = 0;
	const std::regex parameter1("[-](scale)");
	const std::regex parameter2("[0-9]+(.([0-9]*))?");
	while (getline(ss, del, '=')) {
		v.push_back(del);
	}
	if (regex_match(v[0], parameter1) == 1) {
		if (regex_match(v[1], parameter2) == 1 && stof(v[1])>=1) {
			temp = stof(v[1]);
			setScale(temp);
			std::cout << getScale() << "\n";
		}
		else {
			throw std::logic_error("Cannot convert argument value.\n");
		}
	}
	else {
		throw std::logic_error("Wrong arguments! See --help for more info.");
	}

}

void Enlarge::enlarge() {
	try {
		convertArguments();
		CImg<unsigned char> image(getInputPath().c_str()); // create the image from a file (must exist in the working dir)
		int imWidth = static_cast<int>(image.width() * getScale());
        int imHeight = static_cast<int>(image.height() * getScale());
        CImg<unsigned char> enlargedImage(imWidth, imHeight, 1, image.spectrum());
        for (int x = 0; x < imWidth; x++) {
            for (int y = 0; y < imHeight; y++) {
            int imX = static_cast<int>(x / getScale());
            int imY = static_cast<int>(y / getScale());
            for (int z = 0; z < image.spectrum(); z++) {
                enlargedImage(x, y, z) = image(imX, imY, z);
            }
        }
    }
		enlargedImage.save_bmp(getOutputPath().c_str()); // save the modified image to a file
	} catch (CImgIOException e) {
		throw std::logic_error("Cannot open or save file from path provided. Path is invalid.\n");
	} catch (std::logic_error& e) {
		throw std::logic_error(e.what());
	}
}

#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <math.h>
#include "CImg.h"
#include "contrast.h"

using namespace cimg_library;

Contrast::Contrast(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
}

Contrast::~Contrast() {

}

void Contrast::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string Contrast::getArguments() {
	return this->arguments;
}

std::string Contrast::getInputPath() {
	return this->input;
}

void Contrast::setInputPath(std::string path) {
	this->input = path;
}

std::string Contrast::getOutputPath() {
	return this->output;
}

void Contrast::setOutputPath(std::string path) {
	this->output = path;
}

void Contrast::setSlope(float slope) {
	this->slope = slope;
}

float Contrast::getSlope() {
	return this->slope;
}

void Contrast::convertArguments() {

	std::stringstream ss(getArguments());
	std::string del;
	std::vector<std::string> v;
	float temp = 0;
	const std::regex parameter1("[-](slope)");
	const std::regex parameter2("[0-9]+(.([0-9]*))?");
	while (getline(ss, del, '=')) {
		v.push_back(del);
	}
	if (regex_match(v[0], parameter1) == 1) {
		if (regex_match(v[1], parameter2) == 1) {
			temp = stof(v[1]);
			setSlope(temp);
			std::cout << getSlope() << "\n";
		}
		else {
			throw std::logic_error("Cannot convert argument value.\n");
		}
	}
	else {
		throw std::logic_error("Wrong arguments! See --help for more info.");
	}

}

float Contrast::calculate(float val) {
	if (val > 128) {
		float temp = val - 128;
		temp *= getSlope();
		if (128 + temp > 255) {
			val = 255;
		}
		else {
			val = 128 + temp;
		}
	}
	else if (val < 128) {
		float temp = 128 - val;
		temp *= getSlope();
		if (128 - temp < 0) {
			val = 0;
		}
		else {
			val = 128 - temp;
		}
	}
	return val;
}

void Contrast::changeContrast() {
	try {
		convertArguments();
		CImg<unsigned char> image(getInputPath().c_str()); // create the image from a file (must exist in the working dir)
		for (int x = 0; x < image.width(); x++) {
			for (int y = 0; y < image.height(); y++) { // only upper half of the image gets processed
				float valR = image(x, y, 0); // Read red value at coordinates (x, y)
				float valG = image(x, y, 1); // Read green value at coordinates (x, y)
				float valB = image(x, y, 2); // Read blue value at coordinates (x, y)
				image(x, y, 0) = calculate(valR);
				image(x, y, 1) = calculate(valG);
				image(x, y, 2) = calculate(valB);
			}
		}
		image.save_bmp(getOutputPath().c_str()); // save the modified image to a file
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}
	catch (std::logic_error& e) {
		throw std::logic_error(e.what());
	}
	
}
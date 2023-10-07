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
	convertArguments();
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
			std::cout << "Cannot convert parameter value." << std::endl;
		}
	}
	else {
		std::cout << "Wrong arguments! See --help for more info." << std::endl;
	}

}

void Contrast::changeContrast() {
	CImg<unsigned char> image(getInputPath().c_str()); // create the image from a file (must exist in the working dir)
	for (int x = 0; x < image.width(); x++) {
		for (int y = 0; y < image.height(); y++) { // only upper half of the image gets processed
			float valR = image(x, y, 0); // Read red value at coordinates (x, y)
			float valG = image(x, y, 1); // Read green value at coordinates (x, y)
			float valB = image(x, y, 2); // Read blue value at coordinates (x, y)
			float avg = (valR + valG + valB) / 3; // Compute average pixel value (grey)
			if (valR * getSlope() > 255) {
				valR = 255;
			}
			else if (valR * getSlope() < 0) {
				valR = 0;
			}
			else {
				valR *= getSlope();
			}
			if (valG * getSlope() > 255) {
				valG = 255;
			}
			else if (valG * getSlope() < 0) {
				valG = 0;
			}
			else {
				valG *= getSlope();
			}
			if (valB * getSlope() > 255) {
				valB = 255;
			}
			else if (valB * getSlope() < 0) {
				valB = 0;
			}
			else {
				valB *= getSlope();
			}
			image(x, y, 0) = valR;
			image(x, y, 1) = valG;
			image(x, y, 2) = valB;


		}
	}
	image.save_bmp(getOutputPath().c_str()); // save the modified image to a file
}
#include <string>
#include <iostream>
#include <iostream>
#include <sstream>
#include <regex>
#include "AlphaTrimmedMeanFilter.h"
#include "CImg.h"

using namespace cimg_library;


AlphaTrimmedMeanFilter::AlphaTrimmedMeanFilter(std::string values, std::string inputPath, std::string outputPath) {
    this->values = values;
	this->inputPath = inputPath;
    this->outputPath = outputPath;
}

AlphaTrimmedMeanFilter::~AlphaTrimmedMeanFilter() {

}

std::string AlphaTrimmedMeanFilter::getInputPath() {
	return this->inputPath;
}

void AlphaTrimmedMeanFilter::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string AlphaTrimmedMeanFilter::getOutputPath() {
	return this->outputPath;
}

void AlphaTrimmedMeanFilter::setOutputPath(std::string path) {
	this->outputPath = path;
}

std::string AlphaTrimmedMeanFilter::getValues() {
	return this->values;
}

void AlphaTrimmedMeanFilter::setValues(std::string values) {
	this->values = values;
}

int AlphaTrimmedMeanFilter::getD() {
	return this->d;
}

void AlphaTrimmedMeanFilter::setD(int d) {
	this->d = d;
}

void AlphaTrimmedMeanFilter::parseValues() {
	std::stringstream ss(getValues());
	std::string del;
	std::vector<std::string> v;
	int temp = 0;
	const std::regex parameter1("[-](d)");
	const std::regex parameter2("[1-4]{1}");
	while (getline(ss, del, '=')) {
		v.push_back(del);
	}
	if (regex_match(v[0], parameter1) == 1) {
		if (regex_match(v[1], parameter2) == 1) {
			temp = stoi(v[1]);
			setD(temp);
		}
		else {
			throw std::exception("Cannot convert argument value.\n");
		}
	}
	else {
		throw std::exception("Wrong arguments! See --help for more info.");
	}

}

float AlphaTrimmedMeanFilter::sortAndTrim(float box[], int n, int d) {
	int i, j, temp;
	float sum = 0;
	float result = 0;
	for (i = 1; i < n; i++) {
		temp = box[i];
		j = i - 1;
		while (j >= 0 && box[j] > temp) {
			box[j + 1] = box[j];
			j = j -1;
		}
		box[j + 1] = temp;
	}
	for (int k = d; k < sizeof(box) + 1 - d; k++) {
		sum += box[k];
	}
	result = sum / (sizeof(box) + 1 - (2*d));
	return result;
}

void AlphaTrimmedMeanFilter::filter() {
	cimg::exception_mode(0);
	try {
		parseValues();
		CImg<unsigned char> image(getInputPath().c_str());
		CImg<unsigned char> copy(getInputPath().c_str());
		int k = 0;
		const int n = 9;
		int d = getD();
		float box0[n];
		float box1[n];
		float box2[n];
		float mean0 = 0;
        float mean1 = 0;
        float mean2 = 0;
		if (image.spectrum() == 3) {
			for (int x = 1; x < copy.width() - 1; x++) {
					for (int y = 1; y < copy.height() - 1; y++) {
						for (int i = x - 1; i < x + 2; i++) {
							for (int j = y - 1; j < y + 2; j++) {
								box0[k] = copy(i, j, 0);
								box1[k] = copy(i, j, 1);
								box2[k] = copy(i, j, 2);
								k++;
							}
						}
						k = 0;
						image(x, y, 0) = sortAndTrim(box0, n, d);
						image(x, y, 1) = sortAndTrim(box1, n, d);
						image(x, y, 2) = sortAndTrim(box2, n, d);		
					}
			}
		}
		image.save_bmp(getOutputPath().c_str());

	} catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	} catch (std::exception &e) {
		throw std::exception(e.what());
	}

}
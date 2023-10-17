#include <string>
#include <iostream>
#include "AlphaTrimmedMeanFilter.h"
#include "CImg.h"

using namespace cimg_library;


AlphaTrimmedMeanFilter::AlphaTrimmedMeanFilter(std::string inputPath, std::string outputPath) {
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

float AlphaTrimmedMeanFilter::sort(float box[], int n, int d) {
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
		CImg<unsigned char> image(getInputPath().c_str());
		CImg<unsigned char> copy(getInputPath().c_str());
		int k = 0;
		float box0[9];
		float box1[9];
		float box2[9];
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
						image(x, y, 0) = sort(box0, 9, 4);
						image(x, y, 1) = sort(box1, 9, 4);
						image(x, y, 2) = sort(box2, 9, 4);		
					}
			}
		}
		image.save_bmp(getOutputPath().c_str());

	} catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	}

}
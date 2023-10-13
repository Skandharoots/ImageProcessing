#include <string>
#include "AlphaTrimmedMeanFilter.h"

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

void AlphaTrimmedMeanFilter::filter() {

}
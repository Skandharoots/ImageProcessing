#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include "CImg.h"
#include "EFPDF.h"

using namespace cimg_library;

EFPDF::EFPDF(std::string arguments, std::string inputPath, std::string outputPath, std::string histogramPath) {
    this->arguments = arguments;
    this->inputPath = inputPath;
    this->outputPath = outputPath;
    this->histogramPath = histogramPath;
}

EFPDF::~EFPDF() {

}

std::string EFPDF::getInput() {
    return this->inputPath;
}

void EFPDF::setInput(std::string path) {
    this->inputPath = path;
}

std::string EFPDF::getOutput() {
    return this->outputPath;
}

void EFPDF::setOutput(std::string path) {
    this->outputPath = path;
}

std::string EFPDF::getHistogram() {
    return this->histogramPath;
}

void EFPDF::setHistogram(std::string path) {
    this->histogramPath = path;
}

std::string EFPDF::getArguments() {
    return this->arguments;
}

void EFPDF::setArguments(std::string arguments) {
    this->arguments = arguments;
}

double EFPDF::getGMIN() {
    return this->gmin;
}

void EFPDF::setGMIN(double gmin) {
    this->gmin = gmin;
}

double EFPDF::getAlpha() {
    return this->alpha;
}

void EFPDF::setAlpha(double alpha) {
    this->alpha = alpha;
}

void EFPDF::parseArguments() {

    std::stringstream ss(getArguments());
	std::string del;
	std::vector<std::string> v;
    std::vector<std::string> v1;
	int temp = 0;
	const std::regex parameter1("[-](alpha)");
    const std::regex parameter2("[-](gmin)");
	const std::regex parameter3("[1-4]{1}");
    const std::regex parameter4("[0-9]{1,3}");
	while (getline(ss, del, ' ')) {
		v.push_back(del);
	}
    std::stringstream ss1(v[0]);
    std::stringstream ss2(v[1]);
    while(getline(ss1, del, '=')) {
        v1.push_back(del);
    }
	if (regex_match(v1[0], parameter1) == 1) {
		if (regex_match(v1[1], parameter3) == 1) {
			temp = stoi(v1[1]);
			setAlpha(temp);
		}
		else {
			throw std::exception("Cannot convert alpha argument value.\n");
		}
	}
    while(getline(ss2, del, '=')) {
        v1.push_back(del);
    }
	if (regex_match(v1[2], parameter2) == 1) {
		if (regex_match(v1[3], parameter4) == 1) {
			temp = stoi(v1[3]);
			setGMIN(temp);
		}
		else {
			throw std::exception("Cannot convert gmin argument value.\n");
		}
	}
	else {
		throw std::exception("Wrong arguments! See --help for more info.");
	}

}

void EFPDF::efpdfCalculate() {

    cimg::exception_mode(0);
	try {
		parseArguments();
		CImg<unsigned char> image(getInput().c_str());
        // CImg<unsigned char> copy(getInput().c_str());
        CImg<unsigned char> histogram(getHistogram().c_str());
        int arr[256];
        int count = 0;
        int channel = -1;
        int intensity = 0;
        double al = 1 / getAlpha();
        double sum = 0;
        for (int i = 0; i < 256; i++) {
            arr[i] = 0;
        }
        for (int i = 0; i < histogram.width(); i++) {
            for (int j = histogram.height() - 1; j >= 0; j--) {
                if((histogram(i, j, 0) == 255 && histogram(i, j, 1) == 0 && histogram(i, j, 2) == 0)) {
                    channel = 0;
                    count++;
                }
                else if((histogram(i, j, 0) == 0 && histogram(i, j, 1) == 255 && histogram(i, j, 2) == 0)) {
                    channel = 1;
                    count++;
                }
                else if ((histogram(i, j, 0) == 0 && histogram(i, j, 1) == 0 && histogram(i, j, 2) == 255)) {
                    channel = 2;
                    count++;
                }
                else {
                    channel = channel;
                }
            }
            arr[i] = count;
            count = 0;
        }
        //Below needs improvement but works, just not the way it's supposed to
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.width(); y++) {
                for (int i = 0; i <= image(x, y, channel); i++) {
                    sum += arr[i] * 20;
                }
                
                double newval = getGMIN() - (al *  log(1 - (sum / (image.width()*image.height()))));
                // std::cout << "g(f) = " << std::fixed << newval << std::setprecision(5) << std::endl;
                if (image(x, y, channel) + newval > 255) {
                    image(x, y, channel) = 255;    
                }
                if (image(x, y, channel) + newval < 0) {
                    image(x, y, channel) = 0;
                }
                else {
                    image(x, y, channel) += newval;
                }
                sum = 0;
            }
        }
        image.save_bmp(getOutput().c_str());
    } catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	} catch (std::exception &e) {
		throw std::exception(e.what());
	}

}

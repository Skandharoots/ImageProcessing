#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "CImg.h"
#include  "Histogram.h"

using namespace cimg_library;


Histogram::Histogram(std::string channelS, std::string input, std::string output) {
    this->inputPath = input;
    this->outputPath = output;
    this->channelS = channelS;
}

Histogram::~Histogram() {

}

std::string Histogram::getInput() {
    return this->inputPath;
}

void Histogram::setInput(std::string path) {
    this->inputPath = path;
}

std::string Histogram::getOutput() {
    return this->outputPath;
}

void Histogram::setOutput(std::string path) {
    this->outputPath = path;
}

std::string Histogram::getChannel() {
    return this->channelS;
}

void Histogram::setChannel(std::string channel) {
    this->channelS = channel;
}

void Histogram::setChannelVal(int val) {
    this->channel = val;
}

int Histogram::getChannelVal() {
    return this->channel;
}


void Histogram::parseChannel() {

    std::stringstream ss(getChannel());
	std::string del;
	std::vector<std::string> v;
	int temp = 0;
	const std::regex parameter1("[-](c)");
	const std::regex parameter2("[0-2]{1}");
	while (getline(ss, del, '=')) {
		v.push_back(del);
	}
	if (regex_match(v[0], parameter1) == 1) {
		if (regex_match(v[1], parameter2) == 1) {
			temp = stoi(v[1]);
			setChannelVal(temp);
		}
		else {
			throw std::logic_error("Cannot convert argument value.\n");
		}
	}
	else {
		throw std::logic_error("Wrong arguments! See --help for more info.");
	}
}

void Histogram::computeHistogram() {

cimg::exception_mode(0);
	try {
        parseChannel();
        CImg<unsigned char> image(getInput().c_str());
        int chan = getChannelVal();
        int channelArr[256];
        int max = 0;
        for (int i = 0; i < 256; i++) {
            channelArr[i] = 0;
        }
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j++) {
                channelArr[image(i, j, chan)] += 1;
                if(channelArr[image(i, j, chan)] > max) {
                    max = channelArr[image(i, j, chan)];
                }
            }
        }
        CImg<unsigned char> histogram(256, (max / 20), 1, 3);
        for (int i = 0; i < histogram.width(); i++) {
            for (int j = histogram.height() - (channelArr[i] / 20); j < histogram.height(); j++) {
                histogram(i, j, chan) = 255;
                if (chan == 0) {
                    histogram(i, j, 1) = 0;
                    histogram(i, j, 2) = 0;
                }
                else if (chan == 1) {
                    histogram(i, j, 0) = 0;
                    histogram(i, j, 2) = 0;
                }
                else if (chan == 2) {
                    histogram(i, j, 0) = 0;
                    histogram(i, j, 1) = 0;
                }
            }
            
        }
        histogram.save_bmp(getOutput().c_str());
    } catch(CImgIOException e) {
        throw std::logic_error("Cannot open or save file from path provided. Path is invalid.\n");
    } catch (std::logic_error &e) {
        throw std::logic_error(e.what());
    }

}
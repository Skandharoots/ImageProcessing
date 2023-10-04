//
// Created by skand on 03/10/2023.
//

#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "engine.h"
#include "CImg.h"


using namespace cimg_library;

Engine::Engine(std::string command, std::string value, std::string inputPath, std::string outputPath) {
    this->command = command;
    this->value = value;
    this->inputPath = inputPath;
    this->outputPath = outputPath;
}

Engine::~Engine() {

}

void Engine::setCommand(std::string command) {
    this->command = command;
}

std::string Engine::getCommand() {
    return this->command;
}

void Engine::setValue(std::string value) {
    this->value = value;
}

std::string Engine::getValue() {
    return this->value;
}

void Engine::setInputPath(std::string path) {
    this->inputPath = path;
}

std::string Engine::getInputPath() {
    return this->inputPath;
}

void Engine::setOutputPath(std::string path) {
    this->outputPath = path;
}

std::string Engine::getOutputPath() {
    return this->outputPath;
}

int Engine::convertValue(std::string var) {
    std::stringstream ss2(var);
    std::string del2;
    int temp = 0;
    std::vector<std::string> vec;
    const std::regex parameter1("[0-9]+");
    const std::regex parameter2("[-][0-9]+");
    while (getline(ss2, del2, '=')) {
        vec.push_back(del2);
    }
    if (regex_match(vec[1], parameter1) == 1) {
        temp = stoi(vec[1]);
    }
    if (regex_match(vec[1], parameter2)) {
        del2 = vec[1].substr(vec[1].find("-") + 1);
        temp = stoi(del2) * -1;
    }
    else {
        std::cout << "Cannot convert parameter value." << std::endl;
    }
    return temp;
}



std::string Engine::convertInputPath(std::string path) {
    std::stringstream ss(path);
    std::string del2;
    std::vector<std::string> vec;
    while (getline(ss, del2, '=')) {
        vec.push_back(del2);
    }
    if (vec.size() > 1) {
        del2 = vec[1];
    }
    else {
        std::cout << "Cannot convert parameter value." << std::endl;
    }
    return del2;
}

std::string Engine::convertOutputPath(std::string path) {
    std::stringstream ss(path);
    std::string del2;
    std::vector<std::string> vec;
    while (getline(ss, del2, '=')) {
        vec.push_back(del2);
    }
    if (vec.size() > 1) {
        del2 = vec[1];
    }
    else {
        std::cout << "Cannot convert parameter value." << std::endl;
    }
    return del2;
}

 void Engine::openImage() {
     CImg<unsigned char> image(convertInputPath(getInputPath()).c_str()); // create the image from a file (must exist in the working dir)
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height() / 2; y++) { // only upper half of the image gets processed
                float valR = image(x, y, 0); // Read red value at coordinates (x, y)
                float valG = image(x, y, 1); // Read green value at coordinates (x, y)
                float valB = image(x, y, 2); // Read blue value at coordinates (x, y)
                float avg = (valR + valG + valB) / 3; // Compute average pixel value (grey)
                image(x, y, 0) = avg;
                image(x, y, 1) = avg;
                image(x, y, 2) = avg;
            }
        }
        image.save_bmp(convertOutputPath(getOutputPath()).c_str()); // save the modified image to a file
    }



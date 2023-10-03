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

Engine::Engine() {
    
}

Engine::~Engine() {

}

void Engine::setCommand(std::string command) {
    this->command = command;
}

std::string Engine::getCommand() {
    return this->command;
}

void Engine::setName(std::string name) {
    this->name = name;
}

std::string Engine::getName() {
    return this->name;
}

void Engine::setParams(int params) {
    this->params = params;
}

int Engine::getParams() {
    return this->params;
}

void Engine::convertParameter(std::string var) {
    std::stringstream ss2(var);
    std::string del2;
    int temp;
    std::vector<std::string> vec;
    const std::regex parameter("[-][p]");
    while (getline(ss2, del2, '=')) {
        vec.push_back(del2);
    }
    if (regex_match(vec[0], parameter) == 1) {
        setParams(stoi(vec[1]));
    }
    else {
        temp = stoi(vec[1]) * -1;
        setParams(temp);
    }
    
}

 void Engine::openImage() {
        std::string command;
        std::string parameters;
        std::vector<std::string> v;
        const std::regex txt_regex("[a-z]+[ ][-][-][a-z]+[ ][-]([n|p])[=][0-9]+");
        int i = 0;
        int j = 0;
        bool format = false;
        while (format == false) {
            std::cout << "Hello, please provide the parameters according to the format below : \n" << "name --command [-argument=value [...]] \n";
            std::getline(std::cin, command);
            if (std::regex_match(command, txt_regex) != 1) {
                format = false;
            }
            else {
                format = true;
            }
        }
        std::istringstream ss(command);
        std::string del;
        std::string par;
        while (getline(ss, del, ' ')) {
            v.push_back(del);
        }
        setName(v[0]);
        setCommand(v[1]);
        convertParameter(v[2]);
        std::cout << this->name << ", " << this->command << ", " << this->params << "\n";
        CImg<unsigned char> image("../images/lenac.bmp"); // create the image from a file (must exist in the working dir)
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
        image.save_bmp("../images/output/out.bmp"); // save the modified image to a file
    }



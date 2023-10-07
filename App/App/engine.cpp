//
// Created by skand on 03/10/2023.
//

#include <sstream>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "engine.h"
#include "contrast.h"
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

/*int Engine::convertValue(std::string var) {
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
}*/



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

/*std::string Engine::convertOutputPath(std::string path) {
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
*/
 void Engine::openImage() {
     if (command == "--brightness") {
         std::shared_ptr<Brightness> brightness = std::make_shared<Brightness>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
         std::cout << brightness->getArguments() << std::endl;
         std::cout << brightness->getInputPath() << std::endl;
         std::cout << brightness->getOutputPath() << std::endl;
         std::cout << brightness->getValue() << std::endl;
         brightness->changeBrightness();
         std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--contrast") {
         std::shared_ptr<Contrast> contrast = std::make_shared<Contrast>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
         std::cout << contrast->getArguments() << std::endl;
         std::cout << contrast->getInputPath() << std::endl;
         std::cout << contrast->getOutputPath() << std::endl;
         std::cout << contrast->getSlope() << std::endl;
         contrast->changeContrast();
         std::cout << "Operation successful!" << std::endl;
     }
     else {
         std::cout << "Operation failed." << std::endl;
     }

 }



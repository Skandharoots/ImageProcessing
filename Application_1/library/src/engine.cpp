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
#include "GeometricMeanFilter.h"
#include "AlphaTrimmedMeanFilter.h"
#include "MeanSquareError.h"
#include "PeakMeanSquareError.h"
#include "SignalToNoiseRatio.h"
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

std::string Engine::convertInputPath(std::string path) {
    std::stringstream ss(path);
    std::string del2;
    std::vector<std::string> vec;
    while (getline(ss, del2, '=')) {
        vec.push_back(del2);
    }
    if ((vec.size() > 1) && (vec[0]=="-path")) {
        del2 = vec[1];
    }
    else {
        throw std::exception("Cannot convert path value. Type --help for more information\n");
    }
    return del2;
}

 void Engine::openImage() {
     if (command == "--brightness") {
         try {
             std::shared_ptr<Brightness> brightness = std::make_shared<Brightness>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
         
         //std::cout << brightness->getArguments() << std::endl;
         //std::cout << brightness->getInputPath() << std::endl;
         //std::cout << brightness->getOutputPath() << std::endl;
         //std::cout << brightness->getValue() << std::endl;
             brightness->changeBrightness();
             std::cout << "Operation successful!" << std::endl;
         }
         catch (std::exception& e) {
             std::cout << "There was an error. " << e.what() << std::endl;
         }
     }
     else if (command == "--contrast") {
         try {
             std::shared_ptr<Contrast> contrast = std::make_shared<Contrast>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
             contrast->changeContrast();
             std::cout << "Operation successful!" << std::endl;
         }
         catch (std::exception& e) {
             std::cout << "There was an error. " << e.what() << std::endl;
         }
     }
     else if (command == "--gmean") {
        try {
            std::shared_ptr<GeometricMeanFilter> gmean = std::make_shared<GeometricMeanFilter>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
            gmean->filter();
            std::cout << "Operation successful!" << std::endl;
        }
        catch (std::exception& e) {
            std::cout << "There was an error. " << e.what() << std::endl;
        }
     }
     else if (command == "--alpha") {
        std::shared_ptr<AlphaTrimmedMeanFilter> alpha = std::make_shared<AlphaTrimmedMeanFilter>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        alpha->filter();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--mse") {
        std::shared_ptr<MeanSquareError> mse = std::make_shared<MeanSquareError>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        mse->calculate();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--pmse") {
        std::shared_ptr<PeakMeanSquareError> pmse = std::make_shared<PeakMeanSquareError>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        pmse->calculate();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--snr") {
        std::shared_ptr<SignalToNoiseRatio> snr = std::make_shared<SignalToNoiseRatio>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        snr->calculate();
        std::cout << "Operation successful!" << std::endl;
     }
     else {
         throw std::exception("Wrong operation specified. Type --help for more information\n");
     }

 }



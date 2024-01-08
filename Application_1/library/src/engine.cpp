//
// Created by skand on 03/10/2023.
//

#include <sstream>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "Engine.h"
#include "Contrast.h"
#include "Negative.h"
#include "Enlarge.h"
#include "Shrink.h"
#include "FlipDiagonal.h"
#include "FlipHorizontal.h"
#include "FlipVertical.h"
#include "GeometricMeanFilter.h"
#include "AlphaTrimmedMeanFilter.h"
#include "MeanSquareError.h"
#include "PeakMeanSquareError.h"
#include "SignalToNoiseRatio.h"
#include "PeakSignalToNoiseRatio.h"
#include "MaximumDifference.h"
#include "Histogram.h"
#include "EFPDF.h"
#include "Mean.h"
#include "StandardDeviation.h"
#include "Variance.h"
#include "VariationCoefficient.h"
#include "VariationCoefficient2.h"
#include "AssymetryCoefficient.h"
#include "FlatteningCoefficient.h"
#include "InformationSourceEntropy.h"
#include "LinearFilter.h"
#include "LinearFilterOptimized.h"
#include "RobertsOperator2.h"
#include "Dilation.h"
#include "Erosion.h"
#include "Closing.h"
#include "Opening.h"
#include "HitAndMiss.h"
#include "M2.h"
#include "RegionGrowing.h"
#include "FFT.h"
#include "SFT.h"
#include "LowPassFilter.h"
#include "HighPassFilter.h"
#include "BandPassFilter.h"
#include "BandCutFilter.h"
#include "CImg.h"


using namespace cimg_library;

Engine::Engine(std::string command, std::string value, std::string inputPath, std::string outputPath, std::string inputPath2) {
    this->command = command;
    this->value = value;
    this->inputPath = inputPath;
    this->outputPath = outputPath;
    this->inputPath2 = inputPath2;
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

void Engine::setInputPath2(std::string path) {
    this->inputPath2 = path;
}

std::string Engine::getInputPath2() {
    return this->inputPath2;
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
        throw std::logic_error("Cannot convert path value. Type --help for more information\n");
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
         catch (std::logic_error& e) {
             std::cout << "There was an error. " << e.what() << std::endl;
         }
     }
     else if (command == "--contrast") {
         try {
             std::shared_ptr<Contrast> contrast = std::make_shared<Contrast>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
             contrast->changeContrast();
             std::cout << "Operation successful!" << std::endl;
         }
         catch (std::logic_error& e) {
             std::cout << "There was an error. " << e.what() << std::endl;
         }
     }
     else if (command == "--negative") {
        try {
            std::shared_ptr<Negative> negative = std::make_shared<Negative>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
            negative->negate();
            std::cout << "Operation successful!" << std::endl;
        }
        catch (std::logic_error& e) {
            std::cout << "There was an error. " << e.what() << std::endl;
        }
     }
     else if (command == "--vflip") {
        try {
            std::shared_ptr<FlipVertical> vflip = std::make_shared<FlipVertical>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
            vflip->flip();
            std::cout << "Operation successful!" << std::endl;
        }
        catch (std::logic_error& e) {
            std::cout << "There was an error. " << e.what() << std::endl;
        }
     }
     else if (command == "--hflip") {
        try {
            std::shared_ptr<FlipHorizontal> hflip = std::make_shared<FlipHorizontal>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
            hflip->flip();
            std::cout << "Operation successful!" << std::endl;
        }
        catch (std::logic_error& e) {
            std::cout << "There was an error. " << e.what() << std::endl;
        }
     }
     else if (command == "--dflip") {
        try {
            std::shared_ptr<FlipDiagonal> flipDiagonal = std::make_shared<FlipDiagonal>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
            flipDiagonal->flip();
            std::cout << "Operation successful!" << std::endl;
        }
        catch (std::logic_error& e) {
            std::cout << "There was an error. " << e.what() << std::endl;
        }
     }
     else if (command == "--enlarge") {
        try {
            std::shared_ptr<Enlarge> enlarge = std::make_shared<Enlarge>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
            enlarge->enlarge();
            std::cout << "Operation successful!" << std::endl;
        }
        catch (std::logic_error& e) {
            std::cout << "There was an error. " << e.what() << std::endl;
        }
     }
     else if (command == "--shrink") {
        try {
            std::shared_ptr<Shrink> shrink = std::make_shared<Shrink>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
            shrink->shrink();
            std::cout << "Operation successful!" << std::endl;
        }
        catch (std::logic_error& e) {
            std::cout << "There was an error. " << e.what() << std::endl;
        }
     }
     else if (command == "--gmean") {
        try {
            std::shared_ptr<GeometricMeanFilter> gmean = std::make_shared<GeometricMeanFilter>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
            gmean->filter();
            std::cout << "Operation successful!" << std::endl;
        }
        catch (std::logic_error& e) {
            std::cout << "There was an error. " << e.what() << std::endl;
        }
     }
     else if (command == "--alpha") {
        std::shared_ptr<AlphaTrimmedMeanFilter> alpha = std::make_shared<AlphaTrimmedMeanFilter>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
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
     else if (command == "--psnr") {
        std::shared_ptr<PeakSignalToNoiseRatio> psnr = std::make_shared<PeakSignalToNoiseRatio>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        psnr->calculate();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--md") {
        std::shared_ptr<MaximumDifference> md = std::make_shared<MaximumDifference>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        md->calculate();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--histogram") {
        std::shared_ptr<Histogram> hist = std::make_shared<Histogram>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        hist->computeHistogram();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--hexponent") {
        std::shared_ptr<EFPDF> efpdf = std::make_shared<EFPDF>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()), convertInputPath(getInputPath2()));
        efpdf->efpdfCalculate();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--cmean") {
        std::shared_ptr<Mean> cmean = std::make_shared<Mean>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        cmean->calculateMean();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--cstdev") {
        std::shared_ptr<StandardDeviation> cstdev = std::make_shared<StandardDeviation>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        cstdev->calculateStandardDeviation();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--cvariance") {
        std::shared_ptr<Variance> cvariance = std::make_shared<Variance>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        cvariance->calculateVariance();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--cvarcoi") {
        std::shared_ptr<VariationCoefficient> cvarcoi = std::make_shared<VariationCoefficient>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        cvarcoi->calculateVariationCoefficient();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--cvarcoii") {
        std::shared_ptr<VariationCoefficient2> cvarcoii = std::make_shared<VariationCoefficient2>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        cvarcoii->calculateVariationCoefficient2();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--casyco") {
        std::shared_ptr<AssymetryCoefficient> casyco = std::make_shared<AssymetryCoefficient>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        casyco->calculateAssymetryCoefficient();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--cflaco") {
        std::shared_ptr<FlatteningCoefficient> cflaco = std::make_shared<FlatteningCoefficient>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        cflaco->calculateFlatteningCoefficient();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--cise") {
        std::shared_ptr<InfSourceEntropy> ise = std::make_shared<InfSourceEntropy>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        ise->calculateInfSourceEntropy();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--sedgesharp") {
        std::shared_ptr<LinearFilter> sexdeti = std::make_shared<LinearFilter>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        sexdeti->linearFilter();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--sedgesharpopt") {
        std::shared_ptr<LinearFilterOptimized> sexdetiopt = std::make_shared<LinearFilterOptimized>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        sexdetiopt->linearFilter();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--orobertsii") {
        std::shared_ptr<RobertsOperator2> orobertsii = std::make_shared<RobertsOperator2>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        orobertsii->filter();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--dilation") {
        std::shared_ptr<Dilation> dilation = std::make_shared<Dilation>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        dilation->dilation();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--erosion") {
        std::shared_ptr<Erosion> erosion = std::make_shared<Erosion>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        erosion->erosion();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--opening") {
        std::shared_ptr<Opening> opening = std::make_shared<Opening>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        opening->opening();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--closing") {
        std::shared_ptr<Closing> closing = std::make_shared<Closing>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        closing->closing();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--htnms") {
        std::shared_ptr<HitAndMiss> htnms = std::make_shared<HitAndMiss>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        htnms->ham();
        std::cout << "Operation successful!" << std::endl;
     } else if (command == "--m2") {
        std::shared_ptr<M2> m2 = std::make_shared<M2>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        m2->operate(); 
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--rg") {
        std::shared_ptr<RG> rg = std::make_shared<RG>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        rg->regionGrowing(); 
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--fft") {
        std::shared_ptr<FFT> fft = std::make_shared<FFT>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        fft->transform();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--sft") {
        std::shared_ptr<SFT> sft = std::make_shared<SFT>(convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        sft->transform();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--lpf") {
        std::shared_ptr<LowPassFilter> lpf = std::make_shared<LowPassFilter>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        lpf->pass();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--hpf") {
        std::shared_ptr<HighPassFilter> hpf = std::make_shared<HighPassFilter>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        hpf->pass();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--bpf") {
        std::shared_ptr<BandPassFilter> bpf = std::make_shared<BandPassFilter>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        bpf->pass();
        std::cout << "Operation successful!" << std::endl;
     }
     else if (command == "--bcf") {
        std::shared_ptr<BandCutFilter> bcf = std::make_shared<BandCutFilter>(getValue(), convertInputPath(getInputPath()), convertInputPath(getOutputPath()));
        bcf->pass();
        std::cout << "Operation successful!" << std::endl;
     }
     else {
         throw std::logic_error("Wrong operation specified. Type --help for more information\n");
     }

 }



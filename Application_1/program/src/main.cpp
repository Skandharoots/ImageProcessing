// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//This project is designed by students of Politechnika Łódzka from the faculty IFE Information Technology
//The authors are 
//Marek Kopania 234760
//Filip Krylecki 242220

#include <iostream>
#include <iomanip>
#include <chrono>
#include "CImg.h"
#include "engine.h"
#include "help.h"

using namespace std;

int main(int argc, char* argv[])
{
    
    auto startTime = std::chrono::steady_clock::now();
    std::shared_ptr<Engine> engine;
    try {
        if (argc == 2) {
            string operation(argv[1]);
            if (operation == "--help") {
                std::shared_ptr<Help> help = make_shared<Help>();
                help->printHelp();
            }
            else {
                throw std::exception("Type --help to see possible commands.");
            }
        }
        else if (argc == 6) {
            string operation(argv[1]);
            string arg2(argv[2]);
            string arg3(argv[4]);
            string in;
            string out;
            if ((arg2 == "--input") && (arg3 == "--output")) {
                in = argv[3];
                out = argv[5];
            }
            else if ((arg2 == "--input") && (arg3 == "--histogram")) {
                in = argv[3];
                out = argv[5];
            }
            else {
                throw std::exception("Wrong formula for command. Type --help to see the correct phrase.\n");
            }
            engine = make_shared<Engine>(operation, "", in, out, "");
            engine->openImage();
            
        }
        else if (argc == 7) {
            string operation(argv[1]);
            string params(argv[2]);
            string arg2(argv[3]);
            string arg3(argv[5]);
            string in;
            string out;
            if (arg2 == "--input") {
                in = argv[4];
            }
            else if (arg2 == "--output") {
                out = argv[4];
            }
            else {
                throw std::exception("Wrong formula for command. Type --help to see the correct phrase.\n");
            }
            if (arg3 == "--output") {
                out = argv[6];
            }
            else if (arg3 == "--input") {
                in = argv[6];
            }
            else {
                throw std::exception("Wrong formula for command. Type --help to see the correct phrase.\n");
            }
            engine = make_shared<Engine>(operation, params, in, out, "");
            engine->openImage();
            
        }
        else if (argc == 9) {
            string operation(argv[1]);
            string params(argv[2]);
            string arg2(argv[3]);
            string arg3(argv[5]);
            string arg4(argv[7]);
            string in;
            string out;
            string in2;
            if (arg2 == "--input") {
                in = argv[4];
            }
            else if (arg2 == "--output") {
                out = argv[4];
            }
            else {
                throw std::exception("Wrong formula for command. Type --help to see the correct phrase.\n");
            }
            if (arg3 == "--output") {
                out = argv[6];
            }
            else if (arg3 == "--input") {
                in = argv[6];
            }
            else {
                throw std::exception("Wrong formula for command. Type --help to see the correct phrase.\n");
            }
            if (arg4 == "--hist") {
                in2 = argv[8];
            }
            else {
                throw std::exception("Wrong formula for command. Type --help to see the correct phrase.\n");
            }
            engine = make_shared<Engine>(operation, params, in, out, in2);
            engine->openImage();
        }
        else {
            throw std::exception("Type --help for information.\n");
        }
        const auto endTimepoint = std::chrono::steady_clock::now();
        const auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
        .time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch();
        std::cout << "Execution time = " << fixed << elapsedTime.count() / 1000 << std::setprecision(20);
        std::cout << " ms" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "There was an error. " << e.what() << endl;
    }
    return 0;
}


// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CImg.h"
#include "engine.h"
#include "help.h"

using namespace std;

int main(int argc, char* argv[])
{
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
        else if (argc == 7) {
            string operation(argv[1]);
            string params(argv[2]);
            string arg2(argv[3]);
            string arg3(argv[5]);
            string in;
            string out;
            cout << "Arguments: " << params << endl;
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
            engine = make_shared<Engine>(operation, params, in, out);
            engine->openImage();
        }
        else {
            throw std::exception("Type --help for information.\n");
        }
    }
    catch (std::exception& e) {
        std::cout << "There was an error. " << e.what() << endl;
    }
    return 0;
}


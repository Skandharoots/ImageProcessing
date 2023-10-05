// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CImg.h"
#include "engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    //cout << operation << " " << val << " " << in << " " << out << endl;
    //cout << argc;
    std::shared_ptr<Engine> engine;
        if (argc == 2) {
            string operation(argv[1]);
            if (operation == "--help") {
                cout << "Here are some useful tips for the operations of the program." << std::endl;
                cout << "The syntax for the operations is as follows." << std::endl;
                cout << "FileName --operation [-arg1='number' -arg2='number...] --input -path='path to the file' --output -path='path of the output'" << std::endl;
                cout << "The available operations for the --operations except for the --help are:" << endl;
                cout << "--brightness: This operation reduces or increases the brightness of the picture. -value='number' can be negative or positive." << endl;
                cout << "--contrast: This operation increases the contrast of the picture. -value='number' can be positive or negative." << endl;
                cout << endl;

            }
            else {
                cout << "Type --help to see possible commands." << endl;
            }
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
                std::cout << "Wrong formula for command. Type --help to see the correct phrase.\n";
            }
            if (arg3 == "--output") {
                out = argv[6];
            }
            else if (arg3 == "--input") {
                in = argv[6];
            }
            else {
                std::cout << "Wrong formula for command. Type --help to see the correct phrase.\n";
            }
            //string in(argv[4]);
            //string out(argv[6]);
            engine = make_shared<Engine>(operation, params, in, out);
            //cout << engine->getCommand() << " " << engine->getValue() << endl << engine->getInputPath() << endl << engine->getOutputPath() << endl;
            engine->openImage();
        }
        else {
            std::cout << "Type --help for information.\n";
        }
    return 0;
}


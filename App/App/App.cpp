// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CImg.h"
#include "engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    std::shared_ptr<Engine> engine;
    string operation(argv[1]);
    //cout << operation << " " << val << " " << in << " " << out << endl;
    //cout << argc;
    if (operation == "--help") {
        cout << "Here are some useful tips for the operations of the program." << std::endl;
        cout << "The syntax for the operations is as follows." << std::endl;
        cout << "FileName --operation -value='number' --input -path='path to the file' --output -path='path of the output'" << std::endl;
        cout << "The available operations for the --operations except for the --help are:" << endl;
        cout << "--brightness: This operation reduces or increases the brightness of the picture. -value='number' can be negative or positive." << endl;
        cout << "--contrast: This operation increases the contrast of the picture. -value='number' can be positive or negative." << endl;
        cout << endl;

    }
    else if (argc == 7) {
         string val(argv[2]);
         string in(argv[4]);
         string out(argv[6]);
         engine = make_shared<Engine>(operation, val, in, out);
         cout << engine->getCommand() << " " << engine->getValue() << endl << engine->getInputPath() << endl << engine->getOutputPath() << endl;
         //engine->openImage();
         cout << "Value: " << engine->convertValue(engine->getValue());
    }
    else {
        cout << "Wrong formula entered. For help type --help.";
    }
    return 0;
}


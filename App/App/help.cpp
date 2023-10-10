#include <iostream>
#include "help.h"

using namespace std;

Help::Help() {}

Help::~Help() {}

void Help::printHelp() {

    cout << "Here are some useful tips for the operations of the program." << endl;
    cout << "The syntax for the operations is as follows:" << endl;
    cout << "**************************************************************************************************************************************************" << endl;
    cout << "FileName --operation [-arg1=\"number\" -arg2=\"number\"...] --input -path=\"path/image.bmp\" --output -path=\"path/image.bmp\"" << endl;
    cout << "**************************************************************************************************************************************************" << endl;
    cout << "If there are no arguments needed just provide empty \"[]\"" << endl;
    cout << "The available operations for the --operation except for the --help are:" << endl;
    cout << "**************************************************************************************************************************************************" << endl;
    cout << "--brightness: This operation reduces or increases the brightness of the picture. -value=\"number\" can be negative like \"-42\" or positive." << endl;
    cout << "--contrast: This operation increases the contrast of the picture. -value=\"number\" can be a float." << endl;
    cout << "Range from 0.0 to 1.0 decreases the contrast. Range from 1 to 255 increases it." << endl;
}
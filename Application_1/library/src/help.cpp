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
    cout << "--negative: This operation negates intensity values of pixels. Bright pixels become dark, and dark pixels become bright" << endl;
    cout << "--hflip: This operation performs horizontal flip on the image" << endl;
    cout << "--vflip: This operation performs vertical flip on the image" << endl;
    cout << "--dflip: This operation performs diagonal flip on the image" << endl;
    cout << "--shrink: This operation shrinks size of an image by given number."<< endl;
    cout << "\"-scale=number\", where number varies from 1 to infinity. The width and height are then divided by the scale"<< endl;
    cout << "--enlarge: This operation enlarges size of an image by given number."<< endl;
    cout << "\"-scale=number\", where number varies from 1 to infinity. The width and height are then multiplied by the scale"<< endl;
    cout << "--gmean: This operation performs a geometrical mean of a box of 9 pixels in the nearest neighbourhood of each pixel in an image."<< endl;
    cout << "Then the value of outcome intensity is assigned to each channel of the pixel, except border ones."<< endl;
    cout << "--alpha: This operation performs an alpha trim on an image, which takes 9 pixels in the nearest neighbourhood of each pixel in an image."<< endl;
    cout << "Then it sorts the pixels by increasing value and trims the sort by value d. The intensity of the pixel is then assigned the mean of the sort."<< endl;
    cout << "\"-d=number\", where number can be 1, 2, 3 or 4. This argument dictates the number of values inside the sorted array."<< endl;
    cout << "--mse: This operation calculates a mean square error between an original and processed image"<< endl;
    cout << "--pmse: This operation calculates a peak mean square error between an original and processed image"<< endl;
    cout << "--snr: This operation calculates a signal to noise ratio between an original and processed image"<< endl;
    cout << "--psnr: This operation calculates a peak signal to noise ratio between an original and processed image"<< endl;
    cout << "--md: This operation calculates a maximum difference between an original and processed image"<< endl;
}
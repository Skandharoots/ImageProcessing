#include <iostream>
#include "help.h"

using namespace std;

Help::Help() {}

Help::~Help() {}

void Help::printHelp() {

    cout << "Here are some useful tips for the operations of the program." << endl;
    cout << "The syntax for the operations is as follows:" << endl;
    cout << "**************************************************************************************************************************************************" << endl;
    cout << "FileName --operation \"-arg1=\"number\" -arg2=\"number\"...\" --input -path=\"path/image.bmp\" --output -path=\"path/image.bmp\"" << endl;
    cout << "**************************************************************************************************************************************************" << endl;
    cout << "If there are no arguments needed do not provide anything." << endl;
    cout << "The available operations for the --operation except for the --help are:" << endl;
    cout << "**************************************************************************************************************************************************" << endl;
    cout << "--brightness: This operation reduces or increases the brightness of the picture. \"-value=number\" can be negative like \"-42\" or positive." << endl << endl;
    cout << "--contrast: This operation increases the contrast of the picture. -value=\"number\" can be a float." << endl;
    cout << "Range from 0.0 to 1.0 decreases the contrast. Range from 1 to 255 increases it." << endl << endl;
    cout << "--negative: This operation negates intensity values of pixels. Bright pixels become dark, and dark pixels become bright" << endl << endl;
    cout << "--hflip: This operation performs horizontal flip on the image" << endl << endl;
    cout << "--vflip: This operation performs vertical flip on the image" << endl << endl;
    cout << "--dflip: This operation performs diagonal flip on the image" << endl << endl;
    cout << "--shrink: This operation shrinks size of an image by given number."<< endl;
    cout << "\"-scale=number\", where number varies from 1 to infinity. The width and height are then divided by the scale"<< endl << endl;
    cout << "--enlarge: This operation enlarges size of an image by given number."<< endl;
    cout << "\"-scale=number\", where number varies from 1 to infinity. The width and height are then multiplied by the scale"<< endl << endl;
    cout << "--gmean: This operation performs a geometrical mean of a box of 9 pixels in the nearest neighbourhood of each pixel in an image."<< endl;
    cout << "Then the value of outcome intensity is assigned to each channel of the pixel, except border ones."<< endl << endl;
    cout << "--alpha: This operation performs an alpha trim on an image, which takes 9 pixels in the nearest neighbourhood of each pixel in an image."<< endl;
    cout << "Then it sorts the pixels by increasing value and trims the sort by value d. The intensity of the pixel is then assigned the mean of the sort."<< endl;
    cout << "\"-d=number\", where number can be 1, 2, 3 or 4. This argument dictates the number of trimmed values inside the sorted array."<< endl << endl;
    cout << "For the next operations, the input path is for the original image and the output path is for the image that is supposed to be compared with the original" << endl << endl;
    cout << "--mse: This operation calculates a mean square error between an original and processed image"<< endl << endl;
    cout << "--pmse: This operation calculates a peak mean square error between an original and processed image"<< endl << endl;
    cout << "--snr: This operation calculates a signal to noise ratio between an original and processed image"<< endl << endl;
    cout << "--psnr: This operation calculates a peak signal to noise ratio between an original and processed image"<< endl << endl;
    cout << "--histogram: This operation makes a histogram out of input image"<< endl << endl;
    cout << "--hexponent: This operation performs an exponential final probability density function, a quality improvement method"<< endl;
    cout << "\"-hist=path\": Where path is a path to a histogram of an image"<< endl << endl;
    cout << "--cmean: This operation calculates a mean of an image"<< endl << endl;
    cout << "--cstdev: This operation calculates a standard deviation of an image"<< endl << endl;
    cout << "--cvariance: This operation calculates a variance of an image"<< endl << endl;
    cout << "--cvarcoi: This operation calculates a variation coefficient I of an image"<< endl << endl;
    cout << "--cvarcoii: This operation calculates a variation coefficient II of an image"<< endl << endl;
    cout << "--casyco: This operation calculates an assymetry coefficient of an image"<< endl << endl;
    cout << "--cflaco: This operation calculates a flattening coefficient of an image"<< endl << endl;
    cout << "--cise: This operation calculates an information source entropy of an image"<< endl << endl;
    cout << "--sedgesharp: This operation performs an edge sharpening of an image, a linear image filtration algorithm in spatial domain basing on convolution"<< endl << endl;
    cout << "--sedgesharpopt: This operation performs an edge sharpening filter on an image, but it is an optimalised version of original edge sharpening code"<< endl << endl;
    cout << "--orobertsii: This operation performs a Roberts Operator II on an image, a non-linear image filtration algorithm in spatial domain"<< endl << endl;
    cout << "--dilation: This operation performs a dilation on an input image, according to the chosen matrix"<< endl << endl;
    cout << "--erosion: This operation performs an erosion on an input image, according to the chosen matrix"<< endl << endl;
    cout << "--opening: This operation performs opening on an input image, according to the chosen matrix"<< endl << endl;
    cout << "--closing: This operation performs closing on an input image, according to the chosen matrix"<< endl << endl;
    cout << "\"1\" or \"2\" or \"3\" or \"4\": For matrix choice for dilation, erosion, opening, closing operations"<< endl << endl;
    cout << "--htnms: This operation performs hit or miss operasion on an input image, according to the chosen matrix"<< endl;
    cout << "\"11a\" or \"11b\" or \"11c\" or \"11d\" or \"12a\" or \"12b\" or \"12c\" or \"12d\": For matrix choice for dilation, erosion, opening, closing operations"<< endl << endl;
    cout << "--M2: This operation performs M2 operation on an input image"<< endl << endl;
    cout << "--rg: This operation performs region growing on an input image"<< endl << endl;
}
// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CImg.h"
#include "engine.h"

using namespace std;

int main()
{
    std::shared_ptr<Engine> e = std::make_shared<Engine>();
    std::cout << "Hello. Processing\n";
    e->openImage();
    std::cout << "Check out your results.\n";
    return 0;
}


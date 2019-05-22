#include <iostream>

#include "BackgroundFiltering.h"

int main() {
    std::cout << "Hello World !\n";

    Webcam& webcam = Webcam::getInstance();
    BackgroundFiltering filtering;

    int delay = 10;
    for (;;)
    {
        webcam.update();
        filtering.update();

        char c = (char) cv::waitKey(delay);
        if (c == 27) break;
    }

    std::cout << "\nBye World !\n";
    return 0;
}


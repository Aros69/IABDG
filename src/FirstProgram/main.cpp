#include <iostream>

#include "Webcam.h"

int main() {
    std::cout << "Hello World !\n";

    Webcam& webcam = Webcam::getInstance();

    int delay = 10;
    for (;;) //Show the image captured in the window and repeat
    {
        webcam.update();
        //std::cout<<&webcam<<" "<<&webcam2<<" "<<&webcam3<<"\n";

        char c = (char) cv::waitKey(delay);
        if (c == 27) break;
    }

    std::cout << "\nBye World !\n";
    return 0;
}


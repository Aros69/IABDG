#include <iostream>

#include "Webcam.h"

int main() {
    std::cout << "Hello World !\n";

    const char *WIN_RF = "TestWindow";
    cv::namedWindow(WIN_RF, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(WIN_RF, 400, 0);
    cv::Ptr<cv::BackgroundSubtractor> pBackSub = cv::createBackgroundSubtractorKNN();
    cv::Mat otherFrame, newFrame;

    Webcam& webcam = Webcam::getInstance();

    int delay = 10;
    for (;;) //Show the image captured in the window and repeat
    {
        webcam.update();
        pBackSub->apply(webcam.getActualFrame(), otherFrame, 0);

        //pBackSub->getBackgroundImage(newFrame);

        imshow(WIN_RF, otherFrame);

        char c = (char) cv::waitKey(delay);
        if (c == 27) break;
    }

    cv::destroyWindow(WIN_RF);
    std::cout << "\nBye World !\n";
    return 0;
}


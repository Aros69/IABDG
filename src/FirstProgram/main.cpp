#include <iostream>

#include "BackgroundFiltering.h"
#include "BodyPartRecognition.h"
#include "Game.h"

int main() {
    std::cout << "Hello World !\n";

    Webcam &webcam = Webcam::getInstance();
    BackgroundFiltering backgroundFiltering;
    Game game;

    int delay = 10;
    for (;;) {
        webcam.update();
        backgroundFiltering.update(webcam.getActualFrame());

        cv::Mat filteredImg = backgroundFiltering.getActualFrame().clone();
        cv::Mat originalImg = webcam.getActualFrame().clone();
        std::vector<cv::Point> contourPoints =
                BodyPartRecognition::bodyRecognition(filteredImg, originalImg);
        //std::cout << "Nb Point " << contourPoints.size() << "\n";
        //cv::Mat t = originalImg.clone();
        game.update(webcam.getActualFrame().clone(), contourPoints);

        imshow(webcam.getWindowName(), game.getModifiedFrame());


        char c = (char) cv::waitKey(delay);
        if (c == 27) break;
    }

    std::cout << "\nBye World !\n";
    return 0;
}


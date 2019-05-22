#include "BackgroundFiltering.h"

BackgroundFiltering::BackgroundFiltering() {
    WIN_RF = "Background Filtering";
    cv::namedWindow(WIN_RF, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(WIN_RF, 400, 0);
    backgroundSubstractor = cv::createBackgroundSubtractorKNN(2000, 200, false);
    //backgroundSubstractor = cv::createBackgroundSubtractorMOG2();
}

BackgroundFiltering::~BackgroundFiltering() {
    cv::destroyWindow(WIN_RF);
}

void BackgroundFiltering::update() {
    backgroundSubstractor->apply(webcam.getActualFrame(), frame);

    imshow(WIN_RF, frame);
}


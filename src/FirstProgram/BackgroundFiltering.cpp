#include "BackgroundFiltering.h"

BackgroundFiltering::BackgroundFiltering() {
    //WIN_RF = "Background Filtering";
    //cv::namedWindow(WIN_RF, cv::WINDOW_AUTOSIZE);
    backgroundSubstractor = cv::createBackgroundSubtractorKNN(2000, 200, false);
    //backgroundSubstractor = cv::createBackgroundSubtractorMOG2();
}

BackgroundFiltering::~BackgroundFiltering() {
    //cv::destroyWindow(WIN_RF);
}

void BackgroundFiltering::update() {
    //backgroundSubstractor->apply(webcam.getActualFrame(), frame);
    //imshow(WIN_RF, frame);
}

void BackgroundFiltering::update(cv::Mat newFrame) {
    backgroundSubstractor->apply(newFrame, frame);
    //imshow(WIN_RF, frame);
}


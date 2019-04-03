#include "Webcam.h"

Webcam *Webcam::instance_;
Webcam::Webcam() {
    webcam = cv::VideoCapture(0);
    WIN_RF = "Webcam";
    frameNumber = -1;
    instance_ = this;
    cv::namedWindow(WIN_RF, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(WIN_RF, 400, 0);         //750,  2 (bernat =0)
}

Webcam::~Webcam() {
    cv::destroyWindow(WIN_RF);
}

const cv::Mat &Webcam::getActualFrame() const {
    return actualFrame;
}

int Webcam::getFrameNumber() const {
    return frameNumber;
}

Webcam& Webcam::getInstance() {
    if (instance_ == nullptr) {
        instance_ = new Webcam();
    }
    return *instance_;
}

void Webcam::update() {
    webcam >> actualFrame;
    if (actualFrame.empty()) {
        std::cout << " < < <  Game over!  > > > ";
        exit(0);
    }
    ++frameNumber;
    //std::cout << "Frame: " << frameNumber << "\n";
    imshow(WIN_RF, actualFrame);
}
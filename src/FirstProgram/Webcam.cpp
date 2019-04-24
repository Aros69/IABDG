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

Webcam &Webcam::getInstance() {
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
    rectangle(actualFrame, cv::Point(10, 2), cv::Point(100, 20),
              cv::Scalar(255, 255, 255), -1);
    putText(actualFrame, std::to_string(frameNumber), cv::Point(15, 15),
              cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
    //std::cout << "Frame: " << frameNumber << "\n";
    imshow(WIN_RF, actualFrame);
}
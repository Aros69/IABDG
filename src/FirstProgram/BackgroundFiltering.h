#ifndef PROJETIMGANAL_BACKGROUNDFILTERING_H
#define PROJETIMGANAL_BACKGROUNDFILTERING_H

#include "Webcam.h"
#include "BodyPartRecognition.h"

class BackgroundFiltering {
private:
    Webcam &webcam = Webcam::getInstance();
    const char *WIN_RF;
    cv::Ptr<cv::BackgroundSubtractor> backgroundSubstractor;
    cv::Mat frame;

public:
    BackgroundFiltering();

    ~BackgroundFiltering();

    void update();

    void update(cv::Mat newFrame);

    const cv::Mat &getActualFrame() const { return frame; };
};


#endif //PROJETIMGANAL_BACKGROUNDFILTERING_H

/**
 * Singleton Class controlling the webcam.
 * It also define a window which show what the webcam sees
 */

#ifndef PROJETIMGANAL_WEBCAM_H
#define PROJETIMGANAL_WEBCAM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

class Webcam {
private:
    static Webcam *instance_;
    cv::VideoCapture webcam;
    const char *WIN_RF;
    cv::Mat actualFrame;
    int frameNumber;

    Webcam();

    Webcam(Webcam &w);

    Webcam(Webcam &&w);

public:
    ~Webcam();

    static Webcam &getInstance();

    void update();

    const cv::Mat &getActualFrame() const;

    int getFrameNumber() const;

};

#endif //PROJETIMGANAL_WEBCAM_H

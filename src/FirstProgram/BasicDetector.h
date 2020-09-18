#ifndef PROJETIMGANAL_BASICDETECTOR_H
#define PROJETIMGANAL_BASICDETECTOR_H

#include <opencv2/core/mat.hpp>
#include <list>
#include <chrono>

class BasicDetector {
public:

    BasicDetector() {};

    ~BasicDetector() {};

    const cv::Mat &update(const cv::Mat &, std::vector<cv::Point>);

    void draw();

    bool isOver() { return over; }

    void changeOver() { over = !over; };

private:
    cv::Mat frame;

    int stateDetected = 0;
    std::vector<cv::Point> playerContour;
    bool over = false;

    bool isBackButtonPressed = false;
    std::chrono::time_point<std::chrono::system_clock> endTimer;
};


#endif //PROJETIMGANAL_BASICDETECTOR_H

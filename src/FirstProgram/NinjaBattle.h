#ifndef PROJETIMGANAL_NINJABATTLE_H
#define PROJETIMGANAL_NINJABATTLE_H


#include <opencv2/core/mat.hpp>
#include <list>
#include <chrono>

class NinjaBattle {
public:

    NinjaBattle() {};

    ~NinjaBattle() {
        for (auto p : ballsLocation) {
            delete p;
            p = nullptr;
        }
    }

    const cv::Mat &update(const cv::Mat &, std::vector<cv::Point>);

    void draw();

    bool isOver() { return over; }

private:
    cv::Mat frame;
    int score = 0;
    std::vector<cv::Point> playerContour;
    std::list<cv::Point *> ballsLocation;
    int nbBall = 5;
    bool over = false;

    bool isBackButtonPressed = false;
    std::chrono::time_point<std::chrono::system_clock> endTimer;
};


#endif //PROJETIMGANAL_NINJABATTLE_H

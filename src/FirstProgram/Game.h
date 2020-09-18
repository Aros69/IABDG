#ifndef PROJETIMGANAL_GAME_H
#define PROJETIMGANAL_GAME_H

#include <vector>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/video.hpp>
//#include <opencv2/cv.hpp>
#include "NinjaBattle.h"
#include "BasicDetector.h"

class Game {
public:
    Game() {
        ninjaBattle = new NinjaBattle;
        backgroundSubstractor = cv::createBackgroundSubtractorKNN(
                2000, 200, false);
    };

    ~Game() {
        delete ninjaBattle;
        ninjaBattle = nullptr;
    }

    void update(cv::Mat webcamFrame, std::vector<cv::Point> contour);

    const cv::Mat &getFrame() { return frame; };

    const cv::Mat &getModifiedFrame() { return modifiedFrame; };

    void drawPlayerContour();

    void drawMenu();

    void updateMenu();

    void updatePlayerContour();

    void updateKNN();

    void drawKNN();

private:
    std::vector<cv::Point> countourJoueur;
    cv::Mat frame;
    cv::Mat modifiedFrame;

    std::chrono::time_point<std::chrono::system_clock> endTimer1;
    std::chrono::time_point<std::chrono::system_clock> endTimer2;
    std::chrono::time_point<std::chrono::system_clock> endTimer3;
    std::chrono::time_point<std::chrono::system_clock> endTimer4;

    bool isInMenu = true;
    bool isShowingCountour = false;
    bool isInGame = false;
    bool isInDetector = false;
    bool isInKNN = false;

    bool isContourButtonPressed = false;
    bool isJeu1ButtonPressed = false;
    bool isBackButtonPressed = false;
    bool isDetectorButtonPressed = false;
    bool isKNNButtonPressed = false;

    NinjaBattle *ninjaBattle;
    BasicDetector basicDetector;

    cv::Ptr<cv::BackgroundSubtractor> backgroundSubstractor;
};


#endif //PROJETIMGANAL_GAME_H

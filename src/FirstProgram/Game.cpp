#include <opencv2/imgproc.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>
#include "Game.h"
#include "Webcam.h"


void Game::drawPlayerContour() {
    for (auto p : countourJoueur) {
        cv::circle(modifiedFrame, p, 1, cvScalar(0, 255, 0), 1);
    }
    if (isBackButtonPressed) {
        cv::circle(modifiedFrame, cv::Point(550, 350), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Retour", cv::Point(500, 350),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    } else {
        cv::circle(modifiedFrame, cv::Point(550, 350), 70,
                   cv::Scalar(100, 100, 100), -1);
        cv::circle(modifiedFrame, cv::Point(540, 340), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Retour", cv::Point(490, 340),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
}

void Game::drawMenu() {
    if (isContourButtonPressed) {
        cv::circle(modifiedFrame, cv::Point(110, 110), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Contour", cv::Point(50, 115),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    } else {
        cv::circle(modifiedFrame, cv::Point(110, 110), 70,
                   cv::Scalar(100, 100, 100), -1);
        cv::circle(modifiedFrame, cv::Point(100, 100), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Contour", cv::Point(40, 105),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
    if (isJeu1ButtonPressed) {
        cv::circle(modifiedFrame, cv::Point(540, 110), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Jeu ", cv::Point(500, 115),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    } else {
        cv::circle(modifiedFrame, cv::Point(540, 110), 70,
                   cv::Scalar(100, 100, 100), -1);
        cv::circle(modifiedFrame, cv::Point(550, 100), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Jeu", cv::Point(510, 105),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
    if (isDetectorButtonPressed) {
        cv::circle(modifiedFrame, cv::Point(540, 310), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Detector", cv::Point(480, 315),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    } else {
        cv::circle(modifiedFrame, cv::Point(540, 310), 70,
                   cv::Scalar(100, 100, 100), -1);
        cv::circle(modifiedFrame, cv::Point(550, 300), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Detector", cv::Point(490, 305),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }

    if (isKNNButtonPressed) {
        cv::circle(modifiedFrame, cv::Point(110, 310), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "KNN", cv::Point(70, 315),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    } else {
        cv::circle(modifiedFrame, cv::Point(110, 310), 70,
                   cv::Scalar(100, 100, 100), -1);
        cv::circle(modifiedFrame, cv::Point(100, 300), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "KNN", cv::Point(60, 305),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
};

void Game::updateMenu() {
    bool isPressedButton1 = false;
    bool isPressedButton2 = false;
    bool isPressedButton3 = false;
    bool isPressedButton4 = false;
    auto it = countourJoueur.begin();
    do {
        double dist = sqrt(pow(it->x - 100, 2) + pow(it->y - 100, 2));
        if (dist < 70) {
            isPressedButton1 = true;
        }
        dist = sqrt(pow(it->x - 550, 2) + pow(it->y - 100, 2));
        if (dist < 70) {
            isPressedButton2 = true;
        }
        dist = sqrt(pow(it->x - 550, 2) + pow(it->y - 300, 2));
        if (dist < 70) {
            isPressedButton3 = true;
        }
        dist = sqrt(pow(it->x - 100, 2) + pow(it->y - 300, 2));
        if (dist < 70) {
            isPressedButton4 = true;
        }
        it++;
    } while (!isPressedButton1 && !isPressedButton2 && !isPressedButton3 &&
             !isPressedButton4 && it != countourJoueur.end());
    if (!isPressedButton1) {
        isContourButtonPressed = false;
    } else if (!isContourButtonPressed) {
        isContourButtonPressed = true;
        endTimer1 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    } else if (endTimer1 < std::chrono::system_clock::now()) {
        isInMenu = false;
        isShowingCountour = true;
    }
    if (!isPressedButton2) {
        isJeu1ButtonPressed = false;
    } else if (!isJeu1ButtonPressed) {
        isJeu1ButtonPressed = true;
        endTimer2 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    } else if (endTimer2 < std::chrono::system_clock::now()) {
        isInMenu = false;
        isInGame = true;
    }
    if (!isPressedButton3) {
        isDetectorButtonPressed = false;
    } else if (!isDetectorButtonPressed) {
        isDetectorButtonPressed = true;
        endTimer3 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    } else if (endTimer3 < std::chrono::system_clock::now()) {
        isInMenu = false;
        isInDetector = true;
    }
    if (!isPressedButton4) {
        isKNNButtonPressed = false;
    } else if (!isKNNButtonPressed) {
        isKNNButtonPressed = true;
        endTimer4 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    } else if (endTimer4 < std::chrono::system_clock::now()) {
        isInMenu = false;
        isInKNN = true;
    }
}

void Game::updatePlayerContour() {
    bool isPressedButton1 = false;
    auto it = countourJoueur.begin();
    do {
        double dist = sqrt(pow(it->x - 550, 2) + pow(it->y - 350, 2));
        if (dist < 70) {
            isPressedButton1 = true;
        }
        it++;
    } while (!isPressedButton1 && it != countourJoueur.end());
    if (!isPressedButton1) {
        isBackButtonPressed = false;
    } else if (!isBackButtonPressed) {
        isBackButtonPressed = true;
        endTimer1 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    } else if (endTimer1 < std::chrono::system_clock::now()) {
        isInMenu = true;
        isShowingCountour = false;
    }
}

void Game::updateKNN() {
    bool isPressedButton1 = false;
    auto it = countourJoueur.begin();
    do {
        double dist = sqrt(pow(it->x - 550, 2) + pow(it->y - 350, 2));
        if (dist < 70) {
            isPressedButton1 = true;
        }
        it++;
    } while (!isPressedButton1 && it != countourJoueur.end());
    if (!isPressedButton1) {
        isBackButtonPressed = false;
    } else if (!isBackButtonPressed) {
        isBackButtonPressed = true;
        endTimer1 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    } else if (endTimer1 < std::chrono::system_clock::now()) {
        isInMenu = true;
        isShowingCountour = false;
    }
}

void Game::drawKNN() {
    backgroundSubstractor->apply(frame, modifiedFrame);
    if (isBackButtonPressed) {
        cv::circle(modifiedFrame, cv::Point(550, 350), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Retour", cv::Point(500, 350),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    } else {
        cv::circle(modifiedFrame, cv::Point(550, 350), 70,
                   cv::Scalar(100, 100, 100), -1);
        cv::circle(modifiedFrame, cv::Point(540, 340), 70, cv::Scalar(0, 0, 0),
                   -1);
        putText(modifiedFrame, "Retour", cv::Point(490, 340),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
}

void Game::update(cv::Mat webcamFrame, std::vector<cv::Point> contour) {
    frame = webcamFrame.clone();
    modifiedFrame = frame.clone();
    countourJoueur = contour;

    if (contour.size() < 5000) {
        if (isInMenu) {
            updateMenu();
            drawMenu();
        } else if (isShowingCountour) {
            updatePlayerContour();
            drawPlayerContour();
        } else if (isInGame) {
            modifiedFrame = ninjaBattle->update(frame, countourJoueur);
            if (ninjaBattle->isOver()) {
                isInMenu = true;
                isInGame = false;
                delete ninjaBattle;
                ninjaBattle = new NinjaBattle();
            }
        } else if (isInDetector) {
            modifiedFrame = basicDetector.update(frame, countourJoueur);
            if (basicDetector.isOver()) {
                isInMenu = true;
                isInDetector = false;
                basicDetector.changeOver();
            }
        } else if (isInKNN) {
            updateKNN();
            drawKNN();
        }
    } else {
        putText(modifiedFrame,
                "Contour trop grand.",
                cv::Point(40, 120), cv::FONT_HERSHEY_DUPLEX, 1,
                cv::Scalar(0, 0, 255), 2);
        putText(modifiedFrame,
                "On attends une meilleure detection.",
                cv::Point(40, 160), cv::FONT_HERSHEY_DUPLEX, 1,
                cv::Scalar(0, 0, 255), 2);
        for (auto p : countourJoueur) {
            cv::circle(modifiedFrame, p, 1, cvScalar(0, 255, 0), 1);
        }
    }

}
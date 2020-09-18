
#include "BasicDetector.h"
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <iostream>

const cv::Mat &
BasicDetector::update(const cv::Mat &f, std::vector<cv::Point> contour) {
    frame = f.clone();
    playerContour = contour;

    // Récupération donnée
    cv::Point plusHaut = cv::Point(1000, 1000);
    cv::Point plusHautGauche = cv::Point(1000, 1000);
    cv::Point plusHautDroit = cv::Point(1000, 1000);
    cv::Point plusLongGauche = cv::Point(1000, 1000);
    cv::Point plusLongDroit = cv::Point(-1, 1000);
    for (auto p : playerContour) {
        if (p.y < plusHaut.y) {
            plusHaut = p;
        }
        if (p.x < 200 && p.y < plusHautGauche.y) {
            plusHautGauche = p;
        }
        if (p.x > 400 && p.y < plusHautDroit.y) {
            plusHautDroit = p;
        }
        if (p.x < plusLongGauche.x) {
            plusLongGauche = p;
        }
        if (p.x > plusLongDroit.x) {
            plusLongDroit = p;
        }
    }
    if (plusHautGauche.x < 200 && plusHautGauche.y < frame.rows / 4 &&
        plusHautDroit.x > 400 && plusHautDroit.y < frame.rows / 4) {
        stateDetected = 3;
    } else if (plusHaut.x < 200 && plusHaut.y < frame.rows / 4) {
        // Bras gauche
        stateDetected = 2;
    } else if (plusHaut.x > 400 && plusHaut.y < frame.rows / 4) {
        // Bras droit
        stateDetected = 1;
    } else if (plusLongGauche.x < 20 && plusHautDroit.x > frame.cols - 20) {
        // Croix
        stateDetected = 6;
    } else if (plusLongGauche.x < 20) {
        // Bras gauche tendu horizontale
        stateDetected = 4;
    } else if (plusHautDroit.x > frame.cols - 20) {
        // Bras droit tendu horizontale
        stateDetected = 5;
    } else {
        // Rien detecte
        stateDetected = 0;
    }

    bool isPressedButton1 = false;
    auto it = playerContour.begin();
    do {
        double dist = sqrt(pow(it->x - 540, 2) + pow(it->y - 430, 2));
        if (dist < 40) {
            isPressedButton1 = true;
        }
        it++;
    } while (!isPressedButton1 && it != playerContour.end());
    if (!isPressedButton1) {
        isBackButtonPressed = false;
    } else if (!isBackButtonPressed) {
        isBackButtonPressed = true;
        endTimer = std::chrono::system_clock::now() + std::chrono::seconds(3);
    } else if (endTimer < std::chrono::system_clock::now()) {
        over = true;
    }

    draw();
    return frame;
}


void BasicDetector::draw() {
    if (isBackButtonPressed) {
        cv::circle(frame, cv::Point(560, 440), 40, cv::Scalar(0, 0, 0), -1);
        putText(frame, "Quit", cv::Point(530, 450),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 1);
    } else {
        cv::circle(frame, cv::Point(560, 440), 40, cv::Scalar(100, 100, 100),
                   -1);
        cv::circle(frame, cv::Point(550, 430), 40, cv::Scalar(0, 0, 0), -1);
        putText(frame, "Quit", cv::Point(520, 440),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 1);
    }

    cv::rectangle(frame, cv::Point(0, 400), cv::Point(500, 500),
                  cv::Scalar(0, 0, 0), -1);
    std::string text;
    if (stateDetected == 0) {
        text = "Rien de special, bras baisse";
    } else if (stateDetected == 1) {
        text = "Bras droit en haut";
    } else if (stateDetected == 2) {
        text = "Bras gauche en haut";
    } else if (stateDetected == 3) {
        text = "2 bras leves";
    } else if (stateDetected == 4) {
        text = "Bras gauche tendu a gauche";
    } else if (stateDetected == 5) {
        text = "Bras droit tendu a droite";
    } else if (stateDetected == 6) {
        text = "Croix";
    } else {
        text = "Rien";
    }
    putText(frame, text, cv::Point(10, 450), cv::FONT_HERSHEY_DUPLEX, 1,
            cv::Scalar(255, 255, 255), 1);
}
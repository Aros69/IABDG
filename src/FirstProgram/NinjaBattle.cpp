#include <opencv2/imgproc.hpp>
#include <cmath>
#include <iostream>
#include "NinjaBattle.h"

const cv::Mat &
NinjaBattle::update(const cv::Mat &f, std::vector<cv::Point> contour) {
    frame = f.clone();
    playerContour = contour;
    // Création de nouvelles balles
    for (int i = ballsLocation.size(); i < nbBall; ++i) {
        int x, y;
        bool ok;
        do {
            x = rand() % 150;
            y = (rand() % 300) + 100;
            if (rand() % 2 == 0) {
                x = frame.cols - x;
            }
            ok = true;
            for (auto p2:ballsLocation) {
                if (p2 != nullptr) {
                    double dist = sqrt(
                            pow(p2->x - x, 2) + pow(p2->y - y, 2));
                    if (dist < 100) {
                        ok = false;
                    }
                }
            }
        } while (!ok);
        ballsLocation.push_back(new cv::Point(x, y));
    }

    std::list<cv::Point *> toRemove;
    for (auto p : playerContour) {
        for (auto m : ballsLocation) {
            bool notRemoved = true;
            for (auto l : toRemove) {
                notRemoved = notRemoved && !(m->x == l->x && m->y == l->y);
            }
            if (notRemoved) {
                double dist = sqrt(
                        pow(m->x - p.x, 2) + pow(m->y - p.y, 2));
                if (dist < 50) {
                    toRemove.push_back(m);
                    ++score;
                }
            }
        }
    }
    for (auto p: toRemove) {
        ballsLocation.remove(p);
    }

    bool isPressedButton1 = false;
    auto it = playerContour.begin();
    do {
        double dist = sqrt(pow(it->x - 480, 2) + pow(it->y - 60, 2));
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


void NinjaBattle::draw() {
    if (isBackButtonPressed) {
        cv::circle(frame, cv::Point(490, 50), 40, cv::Scalar(0, 0, 0), -1);
        putText(frame, "Quit", cv::Point(460, 60),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 1);
    } else {
        cv::circle(frame, cv::Point(490, 50), 40, cv::Scalar(100, 100, 100),
                   -1);
        cv::circle(frame, cv::Point(480, 60), 40, cv::Scalar(0, 0, 0), -1);
        putText(frame, "Quit", cv::Point(450, 70),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 1);
    }

    cv::rectangle(frame, cv::Point(200, 0), cv::Point(400, 50),
                  cv::Scalar(0, 0, 0), 50);
    putText(frame, std::string("Score : ").append(std::to_string(score)),
            cv::Point(200, 50), cv::FONT_HERSHEY_DUPLEX, 1,
            cv::Scalar(255, 255, 255), 2);
    for (auto p:ballsLocation) {
        cv::circle(frame, *p, 1, cv::Scalar(255, 0, 0), 50);
    }
}
#ifndef PROJETIMGANAL_BODYPARTRECOGNITION_H
#define PROJETIMGANAL_BODYPARTRECOGNITION_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

class BodyPartRecognition {

public:

    /**
     * Search in the picture arms and highlight them : doesn't work for now
     * @param picture the picture where we want to recognize arm
     * @return the picture with the arm highlight
     */
    static cv::Mat armRecognition(cv::Mat picture);

    static std::vector<cv::Point> bodyRecognition(cv::Mat & filteredPicture, cv::Mat & picture);

private:
    static void condefects(std::vector<cv::Vec4i> convexityDefectsSet,
                           std::vector<cv::Point> mycontour, cv::Mat &original);
};


#endif //PROJETIMGANAL_BODYPARTRECOGNITION_H

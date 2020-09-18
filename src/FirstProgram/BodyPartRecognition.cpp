
#include "BodyPartRecognition.h"


cv::Mat BodyPartRecognition::armRecognition(cv::Mat picture) {
    //std::cout << "Begining of the arm recognition\n";
    std::list<cv::Point> pointList;
    cv::Mat temp = cv::Mat(picture.rows, picture.cols, picture.type());
    cv::circle(temp, cv::Point(temp.cols / 2, temp.rows / 2), 500,
               cv::Scalar(0, 0, 0), -1);
    for (int row = 0; row < picture.rows; ++row) {
        for (int col = 0; col < picture.cols / 4; ++col) {
            if ((picture.at<int>(row, col) > 0)
                || (picture.at<int>(row, col) < -1)) {
                cv::circle(temp, cv::Point(col * 4, row), 1,
                           cv::Scalar(255, 255, 255), -1);
                pointList.push_back(cv::Point(col * 4, row));
            }
        }
    }
    /*cv::Mat res = cv::Mat(picture.rows, picture.cols, picture.type());
    cv::circle(res, cv::Point(res.cols / 2, res.rows / 2), 500,
               cvScalar(0, 0, 0), -1);
    for (auto point : pointList) {
        bool hasNeighbhor = false;
        for (int i = point.x - 2; i < point.x + 2; i++) {
            for (int j = point.y - 2; j < point.y + 2; ++j) {
                // Checking out of bound and not in the middle
                if (i > 0 && i < temp.cols && i != point.x && j != point.y &&
                    j > 0 && j < temp.rows) {
                    if ((temp.at<int>(j, i) > 0)
                        || (temp.at<int>(j, i) < -1)) {
                        hasNeighbhor = true;
                    }
                }
            }
        }
        if (hasNeighbhor) {
            //std::cout<<"Suppression du point\n";
            cv::circle(res, point, 1,
                       cvScalar(255, 255, 255), -1);
        }
    }*/
    return temp;
}

std::vector<cv::Point>
BodyPartRecognition::bodyRecognition(cv::Mat &filteredPicture,
                                     cv::Mat &picture) {
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    int largest_area = 0;
    int largest_contour_index = 0;

    findContours(filteredPicture, contours, hierarchy, cv::RETR_TREE,
                 cv::CHAIN_APPROX_SIMPLE);

    /// Find the convex hull,contours and defects for each contour
    std::vector<std::vector<cv::Point> > hull(contours.size());
    std::vector<std::vector<int> > inthull(contours.size());
    std::vector<std::vector<cv::Vec4i> > defects(contours.size());
    for (int i = 0; i < contours.size(); i++) {
        convexHull(cv::Mat(contours[i]), hull[i], false);
        convexHull(cv::Mat(contours[i]), inthull[i], false);
        if (inthull[i].size() > 3)
            convexityDefects(contours[i], inthull[i], defects[i]);
    }

    //find  hulland contour and defects end here
    //this will find largest contour
    for (int i = 0; i < contours.size(); i++) // iterate through each contour.
    {
        double a = contourArea(contours[i], false); //  Find the area of contour
        if (a > largest_area) {
            largest_area = a;
            largest_contour_index = i;                //Store the index of largest contour
        }

    }

    //search for largest contour has end
    if (contours.size() > 0) {
        drawContours(picture, contours, largest_contour_index,
                     CV_RGB(0, 255, 0), 2, 8, hierarchy);
        //std::cout<<contours[largest_contour_index].size()<<"\n";
        //if want to show all contours use below one
        //drawContours(original,contours,-1, CV_RGB(0, 255, 0), 2, 8, hierarchy);
        bool drawBluePolygon = true;
        if (drawBluePolygon)
            drawContours(picture, hull, largest_contour_index,
                         CV_RGB(0, 0, 255), 2, 8, hierarchy);
        //if want to show all hull, use below one
        //drawContours(original,hull,-1, CV_RGB(0, 255, 0), 2, 8, hierarchy);
        bool drawPoints = true;
        if (drawPoints)
            condefects(defects[largest_contour_index],
                       contours[largest_contour_index], picture);
    }
    return contours[largest_contour_index];
}

void BodyPartRecognition::condefects(std::vector<cv::Vec4i> convexityDefectsSet,
                                     std::vector<cv::Point> mycontour,
                                     cv::Mat &original) {
    for (int cDefIt = 0; cDefIt < convexityDefectsSet.size(); cDefIt++) {

        int startIdx = convexityDefectsSet[cDefIt].val[0];
        cv::Point ptStart(mycontour[startIdx]);

        int endIdx = convexityDefectsSet[cDefIt].val[1];
        cv::Point ptEnd(mycontour[endIdx]);

        int farIdx = convexityDefectsSet[cDefIt].val[2];
        cv::Point ptFar(mycontour[farIdx]);

        double depth =
                static_cast<double>(convexityDefectsSet[cDefIt].val[3]) / 256;
        //cout << "depth" << depth << endl;
        //display start points
        circle(original, ptStart, 5, CV_RGB(255, 0, 0), 2, 8);
        //display all end points
        circle(original, ptEnd, 5, CV_RGB(255, 255, 0), 2, 8);
        //display all far points
        circle(original, ptFar, 5, CV_RGB(0, 0, 255), 2, 8);
    }

}
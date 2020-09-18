#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
//#include <cv.hpp>

static void onMouse(int event, int x, int y, int, void *userdata) {
  if (event != cv::EVENT_LBUTTONDOWN) { return; }
  cv::Mat *frame = static_cast<cv::Mat *>(userdata);
  cv::Mat frameModified;

  const char *WIN_RF2 = "ComputedWebcam";
  cv::namedWindow(WIN_RF2, cv::WINDOW_NORMAL);
  cv::resizeWindow(WIN_RF2, frame->cols, frame->rows);

  // Cartoon filter
  //cv::bilateralFilter(*frame, frameModified, 15, 100, 100);
  // Color space change (gray here)
  //cv::cvtColor(*frame, frameModified, cv::COLOR_RGB2HLS);
  // Draw circle
  frameModified = *frame;
  cv::circle(frameModified, cv::Point(x, y), 100, cv::Scalar(255, 255, 255), -1);

  imshow("ComputedWebcam", frameModified);
}

int main() {
  std::cout << "Hello World !\n";

  int frameNum = -1;          // Frame counter
  int delay = 10;
  cv::VideoCapture webcam(0);

  const char *WIN_RF = "Webcam";

  // Windows
  cv::namedWindow(WIN_RF, cv::WINDOW_AUTOSIZE);
  cv::moveWindow(WIN_RF, 400, 0);         //750,  2 (bernat =0)

  cv::Mat frameReference;

  for (;;) //Show the image captured in the window and repeat
  {
    webcam >> frameReference;
    if (frameReference.empty()) {
      std::cout << " < < <  Game over!  > > > ";
      break;
    }
    ++frameNum;

    cv::setMouseCallback(WIN_RF, onMouse, &frameReference);

    //std::cout << "Frame: " << frameNum << "\n";
    imshow(WIN_RF, frameReference);

    char c = (char) cv::waitKey(delay);
    if (c == 27) break;
  }
  cv::destroyAllWindows();

  std::cout << "\nBye World !\n";
  return 0;
}

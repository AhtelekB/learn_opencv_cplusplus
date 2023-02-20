#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

////////////////// Basic Functions //////////////////

std::string resources = "/home/ahtelek/Desktop/ahtelek/code/opencv_cplusplus/Resources/";

int main()
{
    std::string path = resources + "test.png";
    cv::Mat img = cv::imread(path);
    cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    // 灰度（grayscale）
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // 高斯模糊（Gaussian Blur）
    cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 3, 0);

    // 边缘检测器（canny edge detector）
    cv::Canny(imgBlur, imgCanny, 25, 75);

    // 结构元素核（kernel）
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

    // 膨胀（dilate）
    cv::dilate(imgCanny, imgDil, kernel);

    // 腐蚀（erode）
    cv::erode(imgDil, imgErode, kernel);

    // cv::imshow("img", img);
    // cv::imshow("img gray", imgGray);
    // cv::imshow("gauss", imgBlur);
    cv::imshow("canny", imgCanny);
    cv::imshow("dilate", imgDil);
    cv::imshow("erode", imgErode);
    cv::waitKey(0);

    return 0;
}
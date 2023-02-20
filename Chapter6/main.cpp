#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

////////////////// Color Detection //////////////////

cv::Mat imgHSV, mask;

// lambo.png
// int hmin = 0, smin = 110, vmin = 153;
// int hmax = 19, smax = 240, vmax = 255;

// shapes.png
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;

std::string resources = "/home/ahtelek/Desktop/ahtelek/code/opencv_cplusplus/Resources/";

int main()
{

    // std::string path = resources+"lambo.png";
    std::string path = resources + "shapes.png";

    cv::Mat img = cv::imread(path);

    // HSV颜色空间 （H色调，S饱和度，V明度）
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    // 追踪栏窗口
    cv::namedWindow("Trackbars");

    // 追踪导轨
    cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
    cv::createTrackbar("SAt Max", "Trackbars", &smax, 255);
    cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
    cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while (true)
    {
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);

        // 上限值和下限值的范围，输出蒙版（遮罩）
        cv::inRange(imgHSV, lower, upper, mask);

        cv::imshow("img", img);
        cv::imshow("imgSHV", imgHSV);
        cv::imshow("imgMask", mask);

        cv::waitKey(1);
    }
    return 0;
}
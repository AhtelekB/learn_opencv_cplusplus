#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

////////////////// Draw Shapes and Text //////////////////

int main()
{

    // 空图像（Blank Image）
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));

    // 圆（circle）
    cv::circle(img, cv::Point(256, 256), 155, cv::Scalar(0, 69, 255), cv::FILLED);

    // 矩形（rectangle）
    cv::rectangle(img, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255, 255, 255), cv::FILLED);

    // 直线（line）
    cv::line(img, cv::Point(130, 296), cv::Point(382, 296), cv::Scalar(255, 255, 255), 2);

    // 文字（putText）
    cv::putText(img, "AhtelekB's Blog", cv::Point(137, 262), cv::FONT_HERSHEY_DUPLEX, 0.9, cv::Scalar(0, 69, 255), 2);

    cv::imshow("img", img);

    cv::waitKey(0);
}
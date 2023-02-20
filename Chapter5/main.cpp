#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

////////////////// Warp Images //////////////////

float width = 250, hight = 350;
cv::Mat matrix, imgWarp;

std::string resources = "/home/ahtelek/Desktop/ahtelek/code/opencv_cplusplus/Resources/";

int main()
{
    std::string path = resources + "cards.jpg";
    cv::Mat img = cv::imread(path);

    cv::Point2f src[4] = {{529, 142}, {771, 190}, {405, 395}, {674, 457}};
    cv::Point2f dst[4] = {{0.0f, 0.0f}, {width, 0.0f}, {0.0f, hight}, {width, hight}};

    matrix = cv::getPerspectiveTransform(src, dst);
    cv::warpPerspective(img, imgWarp, matrix, cv::Point(width, hight));

    for (int i = 0; i < 4; i++)
    {
        cv::circle(img, src[i], 10, cv::Scalar(0, 69, 255), cv::FILLED);
    }

    cv::imshow("img", img);
    cv::imshow("imgWarp", imgWarp);
    cv::waitKey(0);
    return 0;
}
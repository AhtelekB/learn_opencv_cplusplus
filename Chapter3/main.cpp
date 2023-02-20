#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

std::string resources = "/home/ahtelek/Desktop/ahtelek/code/opencv_cplusplus/Resources/";

//////////////////// Resize and Crop //////////////////
int main()
{
    std::string path = resources + "test.png";
    cv::Mat img = cv::imread(path);
    cv::Mat imgResize, imgCrop;

    // std::cout << img.size() << std::endl;

    // 缩放图片（resize）
    cv::resize(img, imgResize, cv::Size(), 0.5, 0.5);

    // 剪切图片（crop）
    cv::Rect roi(200, 100, 300, 300);
    imgCrop = img(roi);

    cv::imshow("img", img);
    cv::imshow("imgResize", imgResize);
    cv::imshow("Crop", imgCrop);

    cv::waitKey(0);
    return 0;
}
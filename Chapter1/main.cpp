#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

std::string resources = "/home/ahtelek/Desktop/ahtelek/code/opencv_cplusplus/Resources/";

////////////////// Images //////////////////
// int main()
// {
//     std::string path = resources + "test.png";
//     cv::Mat img = cv::imread(path);
//     cv::imshow("img", img);
//     cv::waitKey(0);
//     return 0;
// }

////////////// Videos //////////////////
// int main()
// {

//     std::string path = resources + "test_video.mp4";
//     cv::VideoCapture cap(path);
//     cv::Mat img;

//     while (true)
//     {
//         cap.read(img);
//         cv::imshow("img", img);
//         cv::waitKey(20);
//     }
//     return 0;
// }

////////////////// webcam //////////////////
// int main()
// {
//     cv::VideoCapture cap(0);
//     cv::Mat img;

//     while (true)
//     {

//         cap.read(img);
//         cv::imshow("img", img);
//         cv::waitKey(1);
//     }
//     return 0;
// }
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

////////////////// Color Detection //////////////////

std::string resources = "/home/ahtelek/Desktop/ahtelek/code/opencv_cplusplus/Resources/";

int main()
{
    std::string path = resources + "test.png";
    cv::Mat img = cv::imread(path);

    cv::CascadeClassifier faceCascade;
    faceCascade.load(resources + "haarcascade_frontalface_default.xml");

    if (faceCascade.empty())
    {
        std::cout << "XML file not loaded" << std::endl;
    }

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    for (int i = 0; i < faces.size(); i++)
    {
        cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);
    }

    cv::imshow("img", img);
    cv::waitKey(0);
    return 0;
}
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

////////////////// Project 3 //////////////////

std::string resources = "/home/ahtelek/Desktop/ahtelek/code/opencv_cplusplus/Resources/";

int main()
{
    cv::Mat img;
    cv::VideoCapture cap("http://192.168.10.39:4747/video");

    cv::CascadeClassifier plateCascade;
    plateCascade.load(resources + "haarcascade_russian_plate_number.xml");

    if (plateCascade.empty())
    {
        std::cout << "XML file not loaded" << std::endl;
    }

    std::vector<cv::Rect> plates;

    while (true)
    {

        cap.read(img);

        plateCascade.detectMultiScale(img, plates, 1.1, 10);

        for (int i = 0; i < plates.size(); i++)
        {
            cv::Mat imgCrop = img(plates[i]);
            cv::imshow(std::to_string(i), imgCrop);
            cv::imwrite(resources + "Plates/" + std::to_string(i) + ".png", imgCrop);
            cv::rectangle(img, plates[i].tl(), plates[i].br(), cv::Scalar(255, 0, 255), 3);
        }

        cv::imshow("img", img);
        cv::waitKey(1);
    }
    // return 0;
}
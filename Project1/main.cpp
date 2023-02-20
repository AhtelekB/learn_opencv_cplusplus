#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

////////////////// Project 1 //////////////////
cv::Mat img;
std::vector<std::vector<int>> newPoints;

std::vector<std::vector<int>> myColors{{124, 48, 117, 143, 170, 255}, // 紫色（Purple）
                                       {68, 72, 156, 102, 126, 255}}; // 绿色（Green）

std::vector<cv::Scalar> myColorValues{{255, 0, 255}, // 紫色（Purple）
                                      {0, 255, 0}};  // 绿色（Green）

cv::Point getContours(cv::Mat imgDil)
{

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    cv::Point myPoint(0, 0);

    for (int i = 0; i < contours.size(); i++)
    {
        auto area = cv::contourArea(contours[i]);
        std::cout << area << std::endl;

        std::string objectType;

        if (area > 1000)
        {
            auto peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            // cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 2);
            // cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 2);
            std::cout << conPoly[i].size() << std::endl;
            boundRect[i] = cv::boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;

            cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 2);
            cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
        }
    }
    return myPoint;
}

std::vector<std::vector<int>> findColor(cv::Mat img)
{
    cv::Mat imgHSV;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    for (int i = 0; i < myColors.size(); i++)
    {
        cv::Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
        cv::Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
        cv::Mat mask;
        cv::inRange(imgHSV, lower, upper, mask);
        //        cv::imshow(std::to_string(i), mask);
        cv::Point myPoint = getContours(mask);
        if (myPoint.x != 0 && myPoint.y != 0)
        {
            newPoints.push_back({myPoint.x, myPoint.y, i});
        }
    }
    return newPoints;
}

void drawOnCanvas(std::vector<std::vector<int>> newPoints, std::vector<cv::Scalar> myColorValues)
{
    for (int i = 0; i < newPoints.size(); i++)
    {
        cv::circle(img, (cv::Point(newPoints[i][0], newPoints[i][1])), 10, myColorValues[newPoints[i][2]], cv::FILLED);
    }
}

int main()
{
    cv::VideoCapture cap(0);

    while (true)
    {
        cap.read(img);
        newPoints = findColor(img);
        drawOnCanvas(newPoints, myColorValues);

        cv::imshow("Video", img);
        cv::waitKey(1);
    }
}
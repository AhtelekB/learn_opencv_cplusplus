#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

std::string resource = "/home/ahtelek/Desktop/ahtelek/code/opencv_cplusplus/Resources/";
cv::Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode, imgWarp, imgCrop;
std::vector<cv::Point> initialPoints, docPoints;
float w = 420, h = 596;

std::vector<cv::Point> getContours(cv::Mat imgDil)
{

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    std::vector<cv::Point> biggest;
    int maxArea;

    for (int i = 0; i < contours.size(); i++)
    {
        auto area = cv::contourArea(contours[i]);
        std::cout << area << std::endl;

        std::string objectType;

        if (area > 1000)
        {
            auto peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            if (area > maxArea && conPoly[i].size() == 4)
            {
                // drawContours(imgOriginal, conPoly, i, cv::Scalar(255, 0, 255), 5);
                biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            }

            // drawContours(imgOriginal, conPoly, i, cv::Scalar(255, 0, 255), 2);
            // cv::rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
        }
    }
    return biggest;
}

cv::Mat preProcessing(cv::Mat img)
{
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
    cv::Canny(imgBlur, imgCanny, 25, 75);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(imgCanny, imgDil, kernel);
    // cv::erode(imgDil, imgErode, kernel);
    return imgDil;
}

void drawPoints(std::vector<cv::Point> points, cv::Scalar color)
{
    for (int i = 0; i < points.size(); i++)
    {
        cv::circle(imgOriginal, points[i], 10, color, cv::FILLED);
        cv::putText(imgOriginal, std::to_string(i), points[i], cv::FONT_HERSHEY_PLAIN, 4, color, 4);
    }
}

std::vector<cv::Point> reorder(std::vector<cv::Point> points)
{
    std::vector<cv::Point> newPoints;
    std::vector<int> sumPoints, subPoints;

    for (int i = 0; i < 4; i++)
    {
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }
    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 1
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 2
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 3

    return newPoints;
}

cv::Mat getWarp(cv::Mat img, std::vector<cv::Point> points, float w, float h)
{
    cv::Point2f src[4] = {points[0], points[1], points[2], points[3]};
    cv::Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
    cv::warpPerspective(img, imgWarp, matrix, cv::Point(w, h));

    return imgWarp;
}

int main()
{
    std::string path = resource + "paper.jpg";
    imgOriginal = cv::imread(path);
    cv::resize(imgOriginal, imgOriginal, cv::Size(), 0.5, 0.5);

    // 预处理(Preprpcessing)
    imgThre = preProcessing(imgOriginal);
    // Get Contours - Biggest
    initialPoints = getContours(imgThre);
    // drawPoints(initialPoints, cv::Scalar(0, 0, 255));
    docPoints = reorder(initialPoints);
    // drawPoints(docPoints, cv::Scalar(0, 255, 0));

    // Warp
    imgWarp = getWarp(imgOriginal, docPoints, w, h);

    // Crop
    int cropVal = 10;
    cv::Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
    imgCrop = imgWarp(roi);

    cv::imshow("img", imgOriginal);
    cv::imshow("img Dilation", imgThre);
    cv::imshow("img Warp", imgWarp);
    cv::imshow("img Crop", imgCrop);
    cv::waitKey(0);
}

#ifndef HISTOGRAM_H
#define HISTOGRAM_H
/*
 * TO DO; conver histogram equalization functions into Histogram class
 * includes: 1. histogram drawing
 *           2. grayscale histogram equalization
 *           3. adaptive histogram equalization
 *           4. image converstion functions from OpenCV Mat format to QIMAGE
*/
//OpenCV Library
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <QImage>
#include <QDebug>


class Histogram
{
public:
    Histogram();
    Histogram(std::string);

    void histoEqualiz();

private:
    cv::Mat src;
    QImage hisEqua_src_gray;
    QImage hisEqua_src_color;

};


#endif // HISTOGRAM_H

#pragma once

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Label_Def.h"

using namespace std;

class CLabel{
private://Image Buffer
    cv::Mat m_image_org;
    cv::Mat m_image_gry;

public:
    cv::Rect Image_Label(cv::Mat _img_org, int _label_class);

private:
    cv::Mat Binary_Scale_Down(cv::Mat _img_org, unsigned int _label_class);

};

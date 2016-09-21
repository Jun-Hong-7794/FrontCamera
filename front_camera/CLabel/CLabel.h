#pragma once

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Label_Def.h"

typedef struct _LABEL_ROI_RECT{

    int width;
    int height;

    int left;
    int top;

}ROI_RECT;

using namespace std;

class CLabel{
private://Image Buffer
    cv::Mat m_image_org;
    cv::Mat m_image_gry;

public:
    cv::Rect Image_Label(cv::Mat _img_org, int _label_class);
    bool Image_Label(cv::Mat _img_org, int _label_class,
                     ROI_RECT *_rect_ary, int _max_label_num, int &_label_number,
                     int _label_max_size, int _label_min_size);

private:
    cv::Mat Binary_Scale_Down(cv::Mat _img_org, unsigned int _label_class);

};

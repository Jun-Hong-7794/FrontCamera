#pragma once

#include "../CLabel/CLabel.h"

#define TRAFFIC_SIGNAL_NUMBER 4

#define LABELIMAGE_SIZE_MAX 40*40
#define LABELIMAGE_SIZE_MIN 10*10

#define NUMBER_OF_LABELS 5
struct HSV_AVERAGE{
    int h_avg;
    int s_avg;
    int v_avg;
};

class CMission{

public:
    CMission();
    ~CMission();

private:
    CLabel m_clabel;

private:
    cv::Mat m_pedestrian_prv_img;

public:
    bool Mission_Traffic_signal(cv::Mat _org_image, cv::Mat _seg_image,int &_signal_rst,
                                cv::Mat &_rst_img, cv::Mat &_rst_signal_img);
    int Get_Traffic_Signal_Number(cv::Mat* _image_list,int _n);
    void HSV_Average_Result(cv::Mat _img, HSV_AVERAGE &_hsv_avg);

    bool Mission_Traffic_sign(cv::Mat _org_image, cv::Mat _seg_image,int &_sign_rst,cv::Mat &_rst_img);

    bool Mission_Pedestrian(cv::Mat _org_image, cv::Mat _seg_image,int &_sign_rst,cv::Mat &_rst_img);
    void Image_Subtract(cv::Mat _img_1, cv::Mat _img_2, cv::Mat &_img_rst);

    bool Mission_Incident(cv::Mat _org_image, cv::Mat _seg_image,int &_sign_rst,cv::Mat &_rst_img);

    bool Mission_Dummy_Car(cv::Mat _org_image, cv::Mat _seg_image,int &_sign_rst,cv::Mat &_rst_img);

    bool Mission_Normal_Car(cv::Mat _org_image, cv::Mat _seg_image,int &_sign_rst,cv::Mat &_rst_img);
};

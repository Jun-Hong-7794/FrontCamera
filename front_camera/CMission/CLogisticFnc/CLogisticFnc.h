#pragma once

#include<cmath>
#include<iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>

typedef struct _LOGISTIC_FUNCTION_PARAMETER{

    double x;
    double x0;

    double L;
    double k;

}LOGISTIC_PARM;

class CLogisticFnc{

public:
    CLogisticFnc();
    ~CLogisticFnc();
private:
   const double mc_euler_number;
   LOGISTIC_PARM m_logistic_parm;

private:
   double LogisticFnc(LOGISTIC_PARM _logistic_parm);

public:
   cv::Mat LogisticFnc(cv::Mat _org_img, LOGISTIC_PARM _logistic_parm);
};

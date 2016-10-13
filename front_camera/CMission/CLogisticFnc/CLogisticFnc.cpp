#include "CLogisticFnc.h"

CLogisticFnc::CLogisticFnc() :
    mc_euler_number(std::exp(1)){
//    mc_euler_number = std::exp(1);
}

CLogisticFnc::~CLogisticFnc(){

}

double CLogisticFnc::LogisticFnc(LOGISTIC_PARM _logistic_parm){

    //f(x) = L / (1 + e^(-k * (x - x0))

    double euler_power = (-1) * _logistic_parm.k *(_logistic_parm.x - _logistic_parm.x0);

    double euler_factor = pow((double) mc_euler_number,euler_power);

//    double euler_factor = (euler_number)^(euler_power);

    return (_logistic_parm.L / (1 + euler_factor));
}

cv::Mat CLogisticFnc::LogisticFnc(cv::Mat _org_img, LOGISTIC_PARM _logistic_parm){

    unsigned char *img_data = (unsigned char*)_org_img.data;

    for(int i = 0; i < _org_img.rows; i++){
            for(int j = 0; j < _org_img.cols*3; j += 3){

                _logistic_parm.x = img_data[i*_org_img.cols*3 + j + 0];
                img_data[i*_org_img.cols*3 + j + 0] = LogisticFnc(_logistic_parm);

                _logistic_parm.x = img_data[i*_org_img.cols*3 + j + 1];
                img_data[i*_org_img.cols*3 + j + 1] = LogisticFnc(_logistic_parm);

                _logistic_parm.x = img_data[i*_org_img.cols*3 + j + 2];
                img_data[i*_org_img.cols*3 + j + 2] = LogisticFnc(_logistic_parm);
            }
    }



    return _org_img;
}

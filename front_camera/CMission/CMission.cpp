#include "CMission.h"

CMission::CMission(){

}
CMission::~CMission(){

}

//Traffic_Signal Mission

bool CMission::Mission_Traffic_signal(cv::Mat _org_image, cv::Mat _seg_image,int &_signal_rst,
                                      cv::Mat &_rst_img,cv::Mat &_rst_signal_img){

    //Image Labeling
    _rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_SIGNAL));

    cv::Mat *signal_image_list = new cv::Mat[TRAFFIC_SIGNAL_NUMBER];
    cv::Mat *signal_hsv_image_list = new cv::Mat[TRAFFIC_SIGNAL_NUMBER];

    int width = (int)(_rst_img.cols / TRAFFIC_SIGNAL_NUMBER);
    int height = (int)(_rst_img.rows);

    //Get Devided Image By TRAFFIC_SIGNAL_NUMBER
    for(int i = 0;i < TRAFFIC_SIGNAL_NUMBER;i++){
        signal_image_list[i] = _rst_img(cv::Rect((i*width),0,width,height));

        cv::cvtColor(_rst_img(cv::Rect((i*width),0,width,height)),
                             signal_hsv_image_list[i],CV_BGR2HSV);

    }

    _signal_rst = Get_Traffic_Signal_Number(signal_hsv_image_list, TRAFFIC_SIGNAL_NUMBER);

    signal_image_list[_signal_rst].copyTo(_rst_signal_img);
//    cv::imshow("Result", signal_image_list[signal_number]);

    delete[] signal_image_list;
    delete[] signal_hsv_image_list;
    return true;
}

int CMission::Get_Traffic_Signal_Number(cv::Mat* _image_list,int _n){

    //-1: Can not find
    // 0: Red, 1: Yellow, 2: Green(Left), 3: Green(Straight)
    int signal_number = -1;
    int max_saturation = 0;
    HSV_AVERAGE *hsv_avg = new HSV_AVERAGE[_n];
    memset(hsv_avg,0,sizeof(HSV_AVERAGE)*_n);

    for(int i = 0; i < _n; i++){
        HSV_Average_Result(_image_list[i],hsv_avg[i]);

//        cout << "Number : " << i <<endl;
//        cout << "H : " << hsv_avg[i].h_avg << endl;
//        cout << "S : " << hsv_avg[i].s_avg << endl;
//        cout << "V : " << hsv_avg[i].v_avg << endl << endl;
    }

    for(int i = 0; i < _n; i++){
        if(hsv_avg[i].s_avg >= max_saturation){
            max_saturation = hsv_avg[i].s_avg;
            signal_number = i;
        }
    }

    delete[] hsv_avg;
    return signal_number;
}

void CMission::HSV_Average_Result(cv::Mat _img, HSV_AVERAGE &_hsv_avg){


    int width = _img.cols * 3;
    int height = _img.rows;

    if(width == 0 || height == 0){
        return;
    }

    for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j += 3){

                _hsv_avg.h_avg += _img.data[i*width + j + 0];
                _hsv_avg.s_avg += _img.data[i*width + j + 1];
                _hsv_avg.v_avg += _img.data[i*width + j + 2];

            }
    }

    _hsv_avg.h_avg /= _img.cols;
    _hsv_avg.s_avg /= _img.cols;
    _hsv_avg.v_avg /= _img.cols;
}


//Traffic_Signal Mission

bool CMission::Mission_Traffic_sign(cv::Mat _org_image, cv::Mat _seg_image,int &_sign_rst,cv::Mat &_rst_img){

    _rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_SIGN));

    _sign_rst = 0;

    return true;
}

bool CMission::Mission_Pedestrian(cv::Mat _org_image, cv::Mat _seg_image,int &_pedestrian_rst,cv::Mat &_rst_img){

    _rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_PEDASTRAIN));

    _pedestrian_rst = 0;

    return true;
}

bool CMission::Mission_Incident(cv::Mat _org_image, cv::Mat _seg_image,int &_incidence_rst,cv::Mat &_rst_img){

    _rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_SIGNAL));

    _incidence_rst = 0;

    return true;
}

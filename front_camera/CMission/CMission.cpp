#include "CMission.h"

CMission::CMission(){

    fl_lenet_init = false;

    m_model_file = "/home/jun/Workspace/Learning_Model_Weight/2016-09-22-Lenet/example/lenet_sign/deploy.prototxt";
    m_weight_file = "/home/jun/Workspace/Learning_Model_Weight/2016-09-22-Lenet/example/lenet_sign/Training/lenet_sign_iter_20000.caffemodel";
    m_mean_file = "/home/jun/Workspace/Learning_Model_Weight/2016-09-22-Lenet/data/lenet_sign/lenet_sign_train_mean.binaryproto";
    m_label_file = "/home/jun/Workspace/Learning_Model_Weight/2016-09-22-Lenet/example/lenet_sign/label_file.txt";

    m_lenet.net_initialize(m_model_file.toUtf8().constData(),m_weight_file.toUtf8().constData(),
                           m_mean_file.toUtf8().constData(),m_label_file.toUtf8().constData());
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

bool CMission::Mission_Traffic_sign(cv::Mat _org_image, cv::Mat _seg_image,
                                    int &_sign_rst,cv::Mat &_rst_img, bool _fl_save, CSaveImg *_csave){
    int numberOfLabel = 0;
    int label_index = 0;
    cv::Rect roi_rect[NUMBER_OF_LABELS];
    cv::Mat* rst_img_ary = 0;

    //_rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_SIGN));

    if(!m_clabel.Image_Label(_seg_image, LABEL_SIGN,
                         roi_rect, NUMBER_OF_LABELS, numberOfLabel,
                         LABELIMAGE_SIZE_MAX, LABELIMAGE_SIZE_MIN)){
        _sign_rst = 0;
        return false;
    }
    else{
        rst_img_ary = new cv::Mat[numberOfLabel];

        float prob_max = 0.0;
        float prob_sign = 0.0;

        for(int i = 0; i < numberOfLabel; i++){

            if(roi_rect[i].height == 0)
                continue;

            rst_img_ary[i] = _org_image(roi_rect[i]);

            if(_fl_save)
                _csave->Save_Image(rst_img_ary[i],-1);

            int lenet_rst = Lenet_Analisys(rst_img_ary[i],prob_sign);

            if(lenet_rst != 0){
                if(prob_max < prob_sign){
                    _sign_rst = lenet_rst;
                    prob_max  = prob_sign;
                    label_index = i;
                }
            }
        }
    }

    if(roi_rect[label_index].height == 0)
        return false;
    else
        _rst_img = _org_image(roi_rect[label_index]);


    if(rst_img_ary != 0)
        delete[] rst_img_ary;

    return true;
}

int CMission::Lenet_Analisys(cv::Mat _img, float &_prob){

    std::vector<Prediction> prediction;
    prediction = m_lenet.Classify(_img);

    std::string classify_rst = prediction[0].first;
    _prob = prediction[0].second;

    if(classify_rst == "P1")
        return 1;
    else if(classify_rst == "P2")
        return 2;
    else if(classify_rst == "P3")
        return 3;
    else if(classify_rst == "P4")
        return 4;
    else if(classify_rst == "Stop")
        return 5;

    return 0;
}

bool CMission::Mission_Pedestrian(cv::Mat _org_image, cv::Mat _seg_image,int &_pedestrian_rst,cv::Mat &_rst_img){

    if(m_pedestrian_prv_img.rows == 0 || m_pedestrian_prv_img.cols == 0)
        m_pedestrian_prv_img = _org_image.clone();


    //Image_Subtract(_org_image, m_pedestrian_prv_img, _rst_img);
    _rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_PEDASTRAIN));

    _pedestrian_rst = 0;

    return true;
}

void CMission::Image_Subtract(cv::Mat _img_1, cv::Mat _img_2, cv::Mat &_img_rst){
    cv::absdiff(_img_1,_img_2,_img_rst);
    m_pedestrian_prv_img = _img_1.clone();
    cv::imshow("aa",_img_rst);
}


bool CMission::Mission_Incident(cv::Mat _org_image, cv::Mat _seg_image,int &_incidence_rst,cv::Mat &_rst_img){

    _rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_SIGNAL));

    _incidence_rst = 0;

    return true;
}

bool CMission::Mission_Dummy_Car(cv::Mat _org_image, cv::Mat _seg_image,int &_incidence_rst,cv::Mat &_rst_img){

    _rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_DUMMY_CAR));

    _incidence_rst = 0;

    return true;
}

bool CMission::Mission_Normal_Car(cv::Mat _org_image, cv::Mat _seg_image,int &_sign_rst,cv::Mat &_rst_img){

    _rst_img = _org_image(m_clabel.Image_Label(_seg_image,LABEL_CAR));

    _sign_rst = 0;

    return true;
}

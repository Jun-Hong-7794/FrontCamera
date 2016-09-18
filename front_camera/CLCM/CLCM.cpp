#include "CLCM.h"

CLCM::CLCM(){

    fl_log_play_lcm_init = false;
}

CLCM::~CLCM(){

}

void CLCM::LCM_Log_Subscribe(QString _path, cv::Mat &_img){

    eurecar::vision_lane vision_lane_data;

    if(!fl_log_play_lcm_init){
        if(!m_log_play_lcm.good()){
            std::cout << "log play lcm init fail!" << std::endl;
            return;
        }
        else{
            m_log_play_lcm.subscribe("vision_lane",&Log_Handler::handleMessage,&m_log_handler_obj);
            fl_log_play_lcm_init = true;
        }
    }

    if(m_log_play_lcm.handle() != 0){
        std::cout << "log play lcm handle error!" << std::endl;
        return;
    }

    m_log_handler_obj.Get_Vision_Data(vision_lane_data);

    //std::cout << "vision_lane Time Stamp : " << vision_lane_data.timestamp << std::endl;

    QString image_name = "/" + QString::number(vision_lane_data.timestamp) + ".jpg";
    _path += image_name;

    std::string current_locale_text = _path.toLocal8Bit().constData();
   _img = cv::imread(current_locale_text);

//   cv::imshow("LCM log image",_img);
//   cv::waitKey(10);
    return;
}

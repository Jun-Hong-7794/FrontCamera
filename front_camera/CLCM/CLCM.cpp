#include "CLCM.h"

CLCM::CLCM(){

    fl_log_play_lcm_init = false;
}

CLCM::~CLCM(){

}

void CLCM::LCM_Log_Subscribe(cv::Mat &_img){

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
    return;
}

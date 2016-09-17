#pragma once
#include <iostream>

#include <QString>

#include <lcm/lcm-cpp.hpp>
#include "eurecar/vision_lane.hpp"
#include "eurecar/vision_front_cam.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>

class Log_Handler{

private:
    eurecar::vision_lane m_vision_lane;
    lcm::ReceiveBuffer* m_rbuf;
    std::string m_chan;
public:
    ~Log_Handler() {}

public:
    void handleMessage(const lcm::ReceiveBuffer* rbuf,
                       const std::string& chan,
                       const eurecar::vision_lane* msg)
    {
        //m_rbuf = rbuf;
        m_chan = chan;
        memcpy(&m_vision_lane,msg,sizeof(eurecar::vision_lane));
    }

    void Get_Vision_Data(eurecar::vision_lane &_data){
        memcpy(&_data,&m_vision_lane,sizeof(eurecar::vision_lane));
    }
};

class CLCM{

private:
    bool fl_log_play_lcm_init;

    cv::String m_log_image_dir;

    lcm::LCM m_log_play_lcm;
    Log_Handler m_log_handler_obj;

public:
    CLCM();
    ~CLCM();

public:
    void LCM_Publish(eurecar::vision_front_cam _front_cam_rst);

    void LCM_Subscribe();
    void LCM_Log_Subscribe(QString _path,cv::Mat &_img);


};

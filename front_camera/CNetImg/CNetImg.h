#pragma once

#include <iostream>
#include "CNetImg/csocket.h"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>

#define TCP_BUFFSIZE 3440640
#define HEAD_PROTOCOL -1
#define TAIL_PROTOCOL -2

class CNetImg{

private:
    CClient *mp_client;

public:
    bool Socket_Init(char* _server_ip, int _server_port);
    void Socket_Close();

    bool Image_From_Net(cv::Mat &_img);
};

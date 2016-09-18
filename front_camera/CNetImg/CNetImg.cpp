#include "CNetImg.h"

CNetImg::CNetImg(){
    fl_socket_stream = false;
}

bool CNetImg::Socket_Init(char *_server_ip, int _server_port){

    mp_client = new CClient;

    if(mp_client->socket_init(_server_ip, _server_port, (char *)"192.168.3.5",1234) == -1)
        return false;

    fl_socket_stream = true;

    return true;
}

void CNetImg::Socket_Close(){

    if(mp_client == NULL)
        return;

    fl_socket_stream = false;
    QThread::msleep(100);
    mp_client->socket_close();

    delete mp_client;
    mp_client = NULL;


}

bool CNetImg::Image_From_Net(cv::Mat &_img){

    int data_size = 0;
    int recv_size = 0;

    char *byte_arry = new char[TCP_BUFFSIZE];

    bool fl_head = false;
    bool fl_cont = false;
    bool fl_tail = false;

    int connection_check = 0;

    while(fl_socket_stream){

        char tmp_protocol = 0;
        if(!fl_head){
            connection_check = mp_client->receive_data(&tmp_protocol,sizeof(char));
            if(tmp_protocol == HEAD_PROTOCOL)
                fl_head = true;
            else
                continue;
        }
        if(!fl_cont){
            recv_size = TCP_BUFFSIZE - data_size;
            data_size += mp_client->receive_data(&byte_arry[data_size], recv_size);
            if(data_size == TCP_BUFFSIZE)
            {
                data_size = 0;
                fl_cont = true;
            }
            else
                continue;
        }
        if(!fl_tail){
            mp_client->receive_data(&tmp_protocol, sizeof(char));
            if(tmp_protocol == TAIL_PROTOCOL){
                fl_head = false;
                fl_cont = false;
                fl_tail = false;
                break;
            }
            else
                continue;
        }

        if( connection_check < 0)
            break;
    }

    _img = cv::Mat(672,1280,CV_8UC4,byte_arry).clone();
    cvtColor(_img,_img,CV_BGRA2BGR);

    delete[] byte_arry;

    if(_img.rows == 0 || _img.cols == 0)
        return false;

    return true;
}


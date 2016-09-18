#include "CNetImg/csocket.h"

CClient::~CClient(){
    if(fl_socket_open){
        close(m_client_socket);
        fl_socket_open = false;
    }
}

int CClient::socket_init(char *_server_ip,int _server_port,char *_client_ip,int _client_port){

    memset( &m_server_addr, 0, sizeof( m_server_addr));
    m_server_addr.sin_family     = PF_INET;
    m_server_addr.sin_port       = htons(_server_port);
    m_server_addr.sin_addr.s_addr= inet_addr( _server_ip);

    if(_client_ip != 0){
        memset( &m_client_addr,0,sizeof(m_client_addr));
        m_client_addr.sin_family = PF_INET;
        m_client_addr.sin_addr.s_addr = inet_addr(_client_ip);
        if(_client_port != 0){
            m_client_addr.sin_port = htons(_client_port);
        }
    }

    int option = 1;
    setsockopt(m_client_socket, SOL_SOCKET, SO_REUSEADDR, &option , sizeof(option));

    if( -1 == bind( m_client_socket, (struct sockaddr*)&m_client_addr, sizeof( m_client_addr) ) )
    {
        printf( "bind() 실행 에러n");
        return -1;
    }

    while( -1 == ::connect( m_client_socket, (struct sockaddr*)&m_server_addr, sizeof( m_server_addr) ) )
    {
        printf( "접속 실패n");
        //return -1;
    }

    fl_socket_open = true;

   return 1;
}

int CClient::receive_data(void * _data,int _data_size){

    int tmp_recv_data_size = 0;

    tmp_recv_data_size = read (m_client_socket, (char *)_data, sizeof(char) * _data_size);

    if(tmp_recv_data_size == -1)
        printf("Fail to Read");

    return tmp_recv_data_size;
}

int CClient::send_data(void *_data,int _data_size){

    int tmp_send_data_size = 0;

    tmp_send_data_size =
            write(m_client_socket, (char *)_data, sizeof(char) * _data_size);

    if(tmp_send_data_size == -1)
        printf("Fail to Send");

    return tmp_send_data_size;
}

void CClient::socket_close(){
    if(fl_socket_open){
        close(m_client_socket);
        fl_socket_open = false;
    }
    else
        printf("Have Closed!");
}

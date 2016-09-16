#ifndef CSOCKET
#define CSOCKET

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class CClient{

private:
    int   m_client_socket;
    bool fl_socket_open;
    struct sockaddr_in   m_server_addr;
    struct sockaddr_in  m_client_addr;
public:
    ~CClient();
    int socket_init(char *server_ip,int server_port,char *client_ip = 0,int client_port = 0);

    int receive_data(void *,int);
    int send_data(void *,int);

    void socket_close();

};


#endif // CSOCKET


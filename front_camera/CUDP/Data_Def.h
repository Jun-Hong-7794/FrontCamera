#ifndef DATA_DEF
#define DATA_DEF

#pragma pack(1)
typedef struct _SERVER_TO_CLIENT_DATA_PACKET{

    char header_1;//u
    char header_2;//s

    int command_1;
    int command_2;

    char tail___1;//r
    char tail___2;//g
}DATA_PACKET;

typedef struct _SERVER_TO_CLIENT_CHECK_PACKET{

    char header_1;//u
    char header_2;//s

    bool data_check;// 1: ok, 0: false

    char tail___1;//r
    char tail___2;//g
}CHECK_PACKET;


#endif // DATA_DEF


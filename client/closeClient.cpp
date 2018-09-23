#include "header.h"
#include "clientglobal.h"

void closeClient(){
    int sock = create_socket("","",false);
    string sendstring=clientIP+":"+clientPort+"*|?"+to_string(3);
    send(sock , sendstring.c_str() , sendstring.length() , 0 );
    close(sock);
    exit(0);
}
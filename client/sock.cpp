#include "header.h"
#include "clientglobal.h"

int create_socket(){

    int sock = 0; 
    struct sockaddr_in serv_addr; 
    // char *hello = "shared..."; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        log("Socket creation error"); 
        return -1; 
    } 
    // cout<<"sock fd created"<<endl;
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(atoi(tracker1Port.c_str())); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, tracker1IP.c_str() , &serv_addr.sin_addr)<=0)  
    { 
        log("Invalid address/ Address not supported"); 
        return -1; 
    } 
//    cout<<"inet pton"<<endl;
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        log("Connection Failed"); 
        return -1; 
    } 
    // cout<<"connected"<<endl;
    log("connected");
    return sock;
}

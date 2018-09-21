#include "header.h"
#include "clientglobal.h"

int create_socket(string ip, string port, bool connectToIP){

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
    if(connectToIP) serv_addr.sin_port = htons(atoi(port.c_str())); 
    else    serv_addr.sin_port = htons(atoi(tracker1Port.c_str())); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    string sendIP;
    if(connectToIP) sendIP=ip;
    else    sendIP=tracker1IP;
    if(inet_pton(AF_INET, sendIP.c_str() , &serv_addr.sin_addr)<=0)  
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
    cout<<"connected"<<endl;
    log("connected");
    return sock;
}

void startListening(){
    int server_fd; 
    struct sockaddr_in address; 
    int addrlen;

    // int server_fd; 
    // struct sockaddr_in address; 
    int opt = 1; 
    // int addrlen = sizeof(address); 

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {   
        // perror("socket failed"); 
        log("socket failed");
        exit(EXIT_FAILURE); 
    } 
    //    cout<<"socket fd created"<<endl;
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        // perror("setsockopt");
        log("setsockopt error"); 
        exit(EXIT_FAILURE); 
    } 
    // cout<<"setsocketopt"<<endl;

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = inet_addr(clientIP.c_str()); 
    address.sin_port = htons( atoi(clientPort.c_str()) ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        // perror("bind failed"); 
        log("bind failed");
        exit(EXIT_FAILURE); 
    } 
    // cout<<"socket binded"<<endl;
    if (listen(server_fd, 3) < 0) 
    { 
        // perror("listen"); 
        log("listen error");
        exit(EXIT_FAILURE); 
    } 
    cout<<"listening"<<endl;

    while(1){
        cout<<"in while";
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            // perror("accept"); 
            log("error in accepting request");
            exit(EXIT_FAILURE); 
        }
        log("request accepted "); 
        char buffer[1024]={0};
        read( new_socket , buffer, 1024);
        cout<<buffer<<endl;
    }
}
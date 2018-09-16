#include "header.h"
#include "clientglobal.h"

void initializeGlobalVariables(string client_IP_port, string t1_IP_port, string t2_IP_port){

    int index = client_IP_port.find_first_of(":");
    clientIP=client_IP_port.substr(0,index);
    clientPort=client_IP_port.substr(index+1,4);

    index = t1_IP_port.find_first_of(":");
    tracker1IP=t1_IP_port.substr(0,index);
    tracker1Port=t1_IP_port.substr(index+1,4);

    index = t2_IP_port.find_first_of(":");
    tracker2IP=t2_IP_port.substr(0,index);
    tracker2Port=t2_IP_port.substr(index+1,4);
}

void shareDetailsOfExistingTorrent(){
    // scan .mtorrent folder
    // share details of each .mtorrent file to tracker
}

void notifyTracker(){

    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "shared..."; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return; 
    } 
    cout<<"sock fd created"<<endl;
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(atoi(tracker1Port.c_str())); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, tracker1IP.c_str() , &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return; 
    } 
   cout<<"inet pton"<<endl;
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return; 
    } 
    cout<<"connected"<<endl;
    cout<<"sending"<<endl;
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer );  
}

void share(string filePath, string mtorrentName){
    createTorrentFile(mtorrentName, filePath);
    notifyTracker();
}

int main(int argc, char **argv){
    if(argc < 5){
        cout<<"too few arguments"<<endl;
        return 1;
    }
    string client_IP_port=argv[1];
    string t1_IP_port=argv[2];
    string t2_IP_port=argv[3];
    logfile=argv[4];
    initializeGlobalVariables(client_IP_port, t1_IP_port, t2_IP_port);

    shareDetailsOfExistingTorrent();

    share("extra/CLRS.pdf", ".mtorrent/clrs.mtorrent");

    return 0;
}
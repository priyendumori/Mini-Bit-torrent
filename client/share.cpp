#include "header.h"
#include "clientglobal.h"

void shareDetailsOfExistingTorrent(){
    // scan mtorrent folder
    // share details of each .mtorrent file to tracker
}

void notifyTracker(string mtorrentName){

    string sendstring = getStringToSend(mtorrentName, 0);

    int sock = create_socket("","",false);
    // cout<<"sending"<<endl;
    send(sock , sendstring.c_str() , sendstring.length() , 0 ); 
    // printf("Hello message sent\n"); 
    // valread = read( sock , buffer, 1024); 
    // printf("%s\n",buffer );  
}

void share(string filePath, string mtorrentName){
    createTorrentFile(mtorrentName, filePath);
    notifyTracker(mtorrentName);
}
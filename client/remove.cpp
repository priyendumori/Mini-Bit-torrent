#include "header.h"
#include "clientglobal.h"


void removeTorrent(string mtorrentName){
    // cout<<"in remove"<<endl;
    string sendstring=getStringToSend(mtorrentName, 1);
    // cout<<"s to send "<<sendstring<<endl;
    
    int sock=create_socket("","",false);
    // cout<<"sending"<<endl;
    send(sock , sendstring.c_str() , sendstring.length() , 0 ); 
    // printf("Hello message sent\n"); 
    // valread = read( sock , buffer, 1024); 
    // printf("%s\n",buffer );  

    /********************************************************
    have to add code to delete the mtorrent file
    *********************************************************/
}
#include "header.h"
#include "clientglobal.h"


void removeTorrent(string mtorrentName){
    // cout<<"in remove"<<endl;

    if(!file_exists("./mTorrent/"+mtorrentName)){
        cout<<"FAILURE: FILE_NOT_FOUND"<<endl;
        return;
    }

    string sendstring=getStringToSend(mtorrentName, 1);
    // cout<<"s to send "<<sendstring<<endl;
    
    int sock=create_socket("","",false);
    // cout<<"sending"<<endl;
    log("remove request sent for "+mtorrentName);
    send(sock , sendstring.c_str() , sendstring.length() , 0 );
    log("entry corresponding to "+mtorrentName+" removed "); 
    // printf("Hello message sent\n"); 
    // valread = read( sock , buffer, 1024); 
    // printf("%s\n",buffer );  
    mtorrentName="./mTorrent/"+mtorrentName;
    remove(mtorrentName.c_str());
    log(mtorrentName+" removed from file system ");
    cout<<"SUCCESS: FILE_REMOVED"<<endl;
    close(sock);
}
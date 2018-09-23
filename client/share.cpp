#include "header.h"
#include "clientglobal.h"

void shareDetailsOfExistingTorrent(){
    // scan mtorrent folder
    string foldername="./mTorrent";
    DIR* dirp = opendir(foldername.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        // v.push_back(dp->d_name);
        if(dp->d_name=="." || dp->d_name=="..") continue;
        string n=dp->d_name;
        int in=n.find_last_of(".");
        string ext=n.substr(in+1);
        if(ext!="mtorrent") continue;

        // cout<<"for "<< dp->d_name <<endl;
        // string send=getStringToSend(dp->d_name, 0);
        // cout<<"senf....."<<send<<endl<<endl;
        notifyTracker(dp->d_name);

    }
    closedir(dirp);
    log("details from mTorrent folder shared");
    // share details of each .mtorrent file to tracker
}

void notifyTracker(string mtorrentName){

    string sendstring = getStringToSend(mtorrentName, 0);

    int sock = create_socket("","",false);
    // cout<<"sending"<<endl;
    log("sending request to notify tracker about "+mtorrentName);
    send(sock , sendstring.c_str() , sendstring.length() , 0 ); 
    log("tracker notified about "+mtorrentName);
    // printf("Hello message sent\n"); 
    // valread = read( sock , buffer, 1024); 
    // printf("%s\n",buffer );  
    close(sock);
}

void share(string filePath, string mtorrentName){
    createTorrentFile(mtorrentName, filePath);
    notifyTracker(mtorrentName);
}
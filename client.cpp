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

void share(string filePath, string mtorrentName){
    createTorrentFile(mtorrentName, filePath);
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
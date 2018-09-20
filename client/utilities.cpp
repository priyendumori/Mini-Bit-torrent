#include "header.h"
#include "clientglobal.h"


string getStringToSend(string mtorrentName, int type){
    mtorrentName="mTorrent/"+mtorrentName;
    string send;
    ifstream mt;
    mt.open(mtorrentName);
    string path,hashOfHash;
    for(int i=0;i<5;i++){
        string temp;
        getline(mt, temp);
        if(i==2){
            path=temp;
        }
        if(i==4){
            hashOfHash=stringhash(temp);
        }
    }
    mt.close();

    send=hashOfHash+"|";
    send+=clientIP+":"+clientPort+"|";
    send+=path+"|"+to_string(type);

    return send;
}

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

vector<string> tokenize(string str, string d){
    char *token = strtok((char *)str.c_str(), d.c_str()); 

    vector<string> s;
    while (token != NULL){ 
        s.push_back(token);
        token = strtok(NULL, d.c_str());
    }

    return s;
}
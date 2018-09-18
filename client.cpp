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

    // share("extra/CLRS.pdf", "clrs.mtorrent");

    //sleep(15);
    // cout<<"calling remove"<<endl;
    // removeTorrent("clrs.mtorrent");

    while(1){
        string command;
        cout<<"ready to take command "<<endl;
        getline(cin, command);
        cout<<"cc "<<command<<endl;
        char *token = strtok((char *)command.c_str(), " "); 
        // Keep printing tokens while one of the 
        // delimiters present in str[]. 
        vector<string> s;
        while (token != NULL){ 
            s.push_back(token);
            token = strtok(NULL, " ");
        }

        cout<<"Sssssssssssss "<< s.size()<<endl;
        for(auto i:s) cout<<i<<endl;

        if(s[0] == "share"){
            share(s[1], s[2]);
        }
        else if(s[0] == "get"){
            //
        }
        else if(s[0] == "remove"){
            removeTorrent(s[1]);
        }
        else{
            cout<<"invalid command "<<endl;
        }

    }
    return 0;
}
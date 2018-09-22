#include "header.h"
#include "clientglobal.h"

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

    thread t(startListening);
    t.detach();

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
        
        vector<string> s=tokenize(command, " ");

        cout<<"Sssssssssssss "<< s.size()<<endl;
        for(auto i:s) cout<<i<<endl;

        if(s[0] == "share"){
            share(s[1], s[2]);
        }
        else if(s[0] == "get"){
            get(s[1], s[2]);
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
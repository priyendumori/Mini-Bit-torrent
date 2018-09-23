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

    shareDetailsOfExistingTorrent();
    log("existing torrent information shared to tracker");
    thread t(startListening);
    t.detach();

    while(1){
        string command;
        // cout<<"ready to take command "<<endl;
        getline(cin, command);
        // cout<<"cc "<<command<<endl;
        string ccommand;
        for(int i=0;i<command.size();i++){
            if(command[i]=='\\'){
                ccommand+=command[i+1];
                i++;
            }
            else if(command[i]==' '){
                ccommand+="*|?";
            }
            else{ 
                ccommand+=command[i];
            }
            
        }

        // cout<<"command "<<command<<endl;
        // cout<<"ccommand "<<ccommand<<endl;
        vector<string> s=tokenize(ccommand, "*|?");
        
        // cout<<"Sssssssssssss "<< s.size()<<endl;
        for(auto i:s) cout<<i<<endl;

        if(s[0] == "share"){
            if(s.size()>=3) share(s[1], s[2]);
            else    cout<<"FAILURE: INVALID_ARGUMENT"<<endl;
        }
        else if(s[0] == "get"){
            if(s.size()>=3) get(s[1], s[2]);
            else    cout<<"FAILURE: INVALID_ARGUMENT"<<endl;
        }
        else if(s[0] == "remove"){
            if(s.size()>=2) removeTorrent(s[1]);
            else    cout<<"FAILURE: INVALID_ARGUMENT"<<endl;
        }
        else if(s[0]=="exit"){
            closeClient();
        }
        else if(s[0]=="show"){
            if(s[1]=="downloads"){
                show_down();
            }
            else{
                cout<<"invalid command "<<endl;    
            }
        }
        else{
            cout<<"invalid command "<<endl;
        }
    }
    return 0;
}
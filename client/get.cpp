#include "header.h"
#include "clientglobal.h"

void get(string mtorrentName, string downpath){
    // cout<<"in here"<<endl;
    string sendstring=getStringToSend(mtorrentName, 2);
    // cout<<"s to send "<<sendstring<<endl;
    char buffer[1024] = {0};
    
    int sock=create_socket("","",false);

    // cout<<"sending"<<endl;
    send(sock , sendstring.c_str() , sendstring.length() , 0 ); 

    read( sock , buffer, 1024); 
    // printf("buf %s\n",buffer );  

    vector<string> seeder;
    seeder = tokenize(buffer, "|");
    vector<pair<string,string> > seederpair;
    for(int i=0;i<seeder.size();i+=2){
        seederpair.push_back({seeder[i], seeder[i+1]});
    }
    for(auto i:seederpair) cout<<i.first<<" "<<i.second<<endl;

    char *token = strtok((char *)seederpair[0].first.c_str(), ":");
    string ip=token;
    token = strtok(NULL, ":"); 
    string port=token;
    cout<<"sending request to "<<ip<<":"<<port<<endl;
    int cl_sock=create_socket(ip, port, true);
    cout<<"sending"<<endl;
    send(cl_sock , "hello" , 5 , 0 );
}
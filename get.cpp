#include "header.h"
#include "clientglobal.h"

void get(string mtorrentName, string downpath){
    cout<<"in here"<<endl;
    string sendstring=getStringToSend(mtorrentName, 2);
    cout<<"s to send "<<sendstring<<endl;
    char buffer[1024] = {0};
    int valread; 
    
    int sock=create_socket();

    cout<<"sending"<<endl;
    send(sock , sendstring.c_str() , sendstring.length() , 0 ); 

    valread = read( sock , buffer, 1024); 
    printf("buf %s\n",buffer );  

    vector<string> seeder;
    seeder = tokenize(buffer, "|");

    for(auto i:seeder) cout<<i<<endl;
}
#include "header.h"
#include "clientglobal.h"

void download(vector<pair<string, string> > seederpair, string mtorrentName, string downpath){
    mtorrentName="mTorrent/"+mtorrentName;
    ifstream mt;
    mt.open(mtorrentName);
    string path;
    int size;
    for(int i=0;i<5;i++){
        string temp;
        getline(mt, temp);

        if(i==2){
            path=temp;
        }
        if(i==3){
            cout<<"ddsfd "<<temp<<endl;
            size=stoi(temp);
        }
    }
    mt.close();
    int chunkcount=ceil(size/524288.0);

    char *token = strtok((char *)seederpair[0].first.c_str(), ":");
    string ip=token;
    token = strtok(NULL, ":"); 
    string port=token;
    // cout<<"sending request to "<<ip<<":"<<port<<endl;
    int cl_sock=create_socket(ip, port, true);
    // cout<<"sending"<<endl;
    send(cl_sock , path.c_str() , path.length() , 0 );

    char buffer[524788]={0};
    ofstream file;
    file.open(downpath);
    while(chunkcount>=0){
        memset(buffer,0,sizeof(buffer));
        int rec_l=read( cl_sock , buffer, 524788);
        file.write(buffer, rec_l);
        // cout<<buffer;
        chunkcount--;
    }
    file.close();
}

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

    thread t(download, ref(seederpair), ref(mtorrentName), ref(downpath));
    t.join();
    
}
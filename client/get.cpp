#include "header.h"
#include "clientglobal.h"

void download(vector<pair<string, string> > seederpair, string mtorrentName, string downpath){
    mtorrentName="./mTorrent/"+mtorrentName;
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
    // int chunkcount=ceil(size/524288.0);

    char *token = strtok((char *)seederpair[0].first.c_str(), ":");
    string ip=token;
    token = strtok(NULL, ":"); 
    string port=token;
    cout<<"sending request to gggt "<<ip<<":"<<port<<endl;
    cout<<"sdgsgfsdgfd ip "<<ip<<" port "<<port<<endl;
    int cl_sock=create_socket(ip, port, true);
    cout<<"sending"<<endl;
    send(cl_sock , path.c_str() , path.length() , 0 );

    char buffer[524288]={0};
    ofstream file;
    file.open(downpath);
    

    int rec_l;
    do{
        rec_l=read( cl_sock , buffer, 524288);
        file.write(buffer, rec_l);
    }while(rec_l>0);
    file.close();

    cout<<"DOWNLOADED......"<<endl;

    close(cl_sock);
}

void get(string mtorrentName, string downpath){
    cout<<"in here"<<endl;
    string sendstring=getStringToSend(mtorrentName, 2);
    cout<<"s to send "<<sendstring<<endl;
    string hash(sendstring);
    hash=hash.substr(0,hash.find_first_of("*|?"));
    cout<<"hash ......  "<<hash<<endl; 
    char buffer[1024] = {0};
    
    int sock=create_socket("","",false);

    cout<<"sending"<<endl;
    send(sock , sendstring.c_str() , sendstring.length() , 0 ); 
    cout<<"trying to read"<<endl;
    read( sock , buffer, 1024); 
    printf("buf %s\n",buffer );  

    vector<string> seeder;
    seeder = tokenize(buffer, "*|?");
    vector<pair<string,string> > seederpair;
    for(int i=0;i<seeder.size();i+=2){
        seederpair.push_back({seeder[i], seeder[i+1]});
    }
    for(auto i:seederpair) cout<<i.first<<" "<<i.second<<endl;

    if(downpath[0]!='/' && downpath[0]!='~'){
        char buffer[1000];
        getcwd(buffer, 1000);
        // cout<<buffer<<endl;
        string pwd(buffer);
        downpath=pwd+"/"+downpath;
    }

    string shareinfo=hash+"*|?"+clientIP+":"+clientPort+"*|?"+downpath+"*|?"+"0";
    cout<<"sadaaddfdsfd "<<shareinfo<<endl;
    send(sock , shareinfo.c_str() , shareinfo.length() , 0 ); 

    thread t(download, seederpair, mtorrentName, downpath);
    t.detach();
    // t.join();
    close(sock);
    
}
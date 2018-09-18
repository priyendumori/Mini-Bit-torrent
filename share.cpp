#include "header.h"
#include "clientglobal.h"


string stringhash(string s){
    unsigned char hashbuf[20]; // == 20
    unsigned char hash[40];

    SHA1((unsigned char *)s.c_str(), s.length() , hashbuf);

    //cout<<buffer<<endl;

    for(int i=0;i<20;i++){
        sprintf((char *)&(hash[i*2]), "%02x",hashbuf[i]);            
    }

    string hashstring((char *)hash);
    return hashstring;
}

void shareDetailsOfExistingTorrent(){
    // scan mtorrent folder
    // share details of each .mtorrent file to tracker
}


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


void notifyTracker(string mtorrentName){

    string sendstring = getStringToSend(mtorrentName, 0);

    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    // char *hello = "shared..."; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return; 
    } 
    cout<<"sock fd created"<<endl;
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(atoi(tracker1Port.c_str())); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, tracker1IP.c_str() , &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return; 
    } 
   cout<<"inet pton"<<endl;
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        
        return; 
    } 
    cout<<"connected"<<endl;
    cout<<"sending"<<endl;
    send(sock , sendstring.c_str() , sendstring.length() , 0 ); 
    printf("Hello message sent\n"); 
    //valread = read( sock , buffer, 1024); 
    //printf("%s\n",buffer );  
}

void removeTorrent(string mtorrentName){
    cout<<"in remove"<<endl;
    string sendstring=getStringToSend(mtorrentName, 1);
    cout<<"s to send "<<sendstring<<endl;
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    // char *hello = "shared..."; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return; 
    } 
    cout<<"sock fd created"<<endl;
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(atoi(tracker1Port.c_str())); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, tracker1IP.c_str() , &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return; 
    } 
   cout<<"inet pton"<<endl;
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        
        return; 
    } 
    cout<<"connected"<<endl;
    cout<<"sending"<<endl;
    // send(sock , sendstring.c_str() , sendstring.length() , 0 ); 
    // printf("Hello message sent\n"); 
    // valread = read( sock , buffer, 1024); 
    // printf("%s\n",buffer );  

    /********************************************************
    have to add code to delete the mtorrent file
    *********************************************************/
}

void share(string filePath, string mtorrentName){
    createTorrentFile(mtorrentName, filePath);
    notifyTracker(mtorrentName);
}
#include "header.h"
#include "clientglobal.h"

void get(string mtorrentName, string downpath){
    string sendstring=getStringToSend(mtorrentName, 2);
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
    send(sock , sendstring.c_str() , sendstring.length() , 0 ); 

    valread = read( sock , buffer, 1024); 
    printf("buf %s\n",buffer );  

    vector<string> seeder;

    char *token = strtok(buffer, "|"); 
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    while (token != NULL){ 
        seeder.push_back(token);
        token = strtok(NULL, "|");
    }

    for(auto i:seeder) cout<<i<<endl;
}

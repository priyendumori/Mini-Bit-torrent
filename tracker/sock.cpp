#include "header.h"
#include "trackerglobal.h"

extern int server_fd; 
extern struct sockaddr_in address; 
extern int addrlen;

void createSocket(){
    // int server_fd; 
    // struct sockaddr_in address; 
    int opt = 1; 
    // int addrlen = sizeof(address); 

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {   
        // perror("socket failed"); 
        log("socket failed");
        exit(EXIT_FAILURE); 
    } 
    //    cout<<"socket fd created"<<endl;
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        // perror("setsockopt");
        log("setsockopt error"); 
        exit(EXIT_FAILURE); 
    } 
    // cout<<"setsocketopt"<<endl;

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = inet_addr(mytrackerIP.c_str());//INADDR_ANY; 
    address.sin_port = htons( atoi(mytrackerport.c_str()) ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        // perror("bind failed"); 
        log("bind failed");
        exit(EXIT_FAILURE); 
    } 
    // cout<<"socket binded"<<endl;
    if (listen(server_fd, 3) < 0) 
    { 
        // perror("listen"); 
        log("listen error");
        exit(EXIT_FAILURE); 
    } 
    
}

void serveRequest(int new_socket){
    char buffer[1024] = {0}; 

    read( new_socket , buffer, 1024); 
    cout<<buffer<<endl;

    char *token = strtok(buffer, "*|?"); 
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    vector<string> s;
    while (token != NULL){ 
        s.push_back(token);
        token = strtok(NULL, "*|?"); 
    } 

    cout<<"rec "<<endl;
    for(auto i:s) cout<<i<<endl;


    if(s[s.size()-1] == "0"){
        //share
        insert(s,false);
    }
    else if(s[s.size()-1] == "1"){
        //remove
        remove(s);
    }
    else if(s[s.size()-1] == "2"){
        //get
        sendSeederList(s, new_socket);
    }
    else if(s[s.size()-1] == "3"){
        clientOffLine(s);
    }
    //insert(buffer, false);
    //remove(buffer);
    for(auto i:seedermap){
        cout<<i.first<<":"<<endl;
        for(auto j:i.second){
            cout<<j.first<<" "<<j.second<<endl;
        }
        cout<<endl<<endl;
    }
    cout<<"map end"<<endl;
    
    // printf("%s\n",buffer ); 
    // send(new_socket , "hello" , strlen("hello") , 0 ); 
    // printf("Hello message sent\n"); 
}

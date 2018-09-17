#include "header.h"
#include "trackerglobal.h"

map<string, map<string, string> > seedermap; // map< hash, map<socket, file>>

void insert(char buffer[], bool callfromfile){
    ofstream seeders;
    string bufback(buffer);

    char *token = strtok(buffer, "|"); 
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    vector<string> s;
    while (token != NULL){ 
        s.push_back(token);
        token = strtok(NULL, "|"); 
    } 
    // seedermap[s[0]].push_back({s[1], s[2]});
    if(seedermap.find(s[0]) == seedermap.end() ){
        seedermap[s[0]][s[2]]=s[1];
        if(!callfromfile){
            seeders.open(seeder_list.c_str(), ios::app);
            seeders<< bufback <<endl;
            seeders.close();
        }
    }
    else{
        if(seedermap[s[0]].find(s[2]) == seedermap[s[0]].end() ){
            seedermap[s[0]][s[2]]=s[1];
            if(!callfromfile){
                seeders.open(seeder_list.c_str(), ios::app);
                seeders<< bufback <<endl;
                seeders.close();
            }
        }
    }
}

void loadSeederFromFile(){
    ifstream seeders;
    seeders.open(seeder_list.c_str());
    
    string temp;
    while(getline(seeders, temp)){
        insert((char *)temp.c_str(), true);
    }
    seeders.close();
}

int connect(){
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    
    
    cout<<"start"<<endl;
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {   
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       cout<<"socket fd created"<<endl;
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"setsocketopt"<<endl;
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( 1235 ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"socket binded"<<endl;
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"listening"<<endl;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"accepted"<<endl;
    return new_socket;
}

int main(int argc, char **argv){

    if(argc < 4){
        cout<<"too few arguments"<<endl;
        return 1;
    }
    string mytracker_IP_port=argv[1];
    string othertracker_IP_port=argv[2];
    seeder_list=argv[3];
    logfile=argv[4];


    loadSeederFromFile();
    char buffer[1024] = {0}; 
    int valread;
    int new_socket=connect();

    valread = read( new_socket , buffer, 1024); 
    cout<<"calling iinsert"<<endl;
    cout<<buffer<<endl;
    insert(buffer, false);

    cout<<"printing "<<endl;
    for(auto i:seedermap){
        cout<<i.first<<" ";
        for(auto j:i.second){
            cout<<j.first<<" "<<j.second;
        }
        cout<<endl;
    }
    
    // printf("%s\n",buffer ); 
    send(new_socket , "hello" , strlen("hello") , 0 ); 
    printf("Hello message sent\n"); 
}
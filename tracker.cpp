#include "header.h"
#include "trackerglobal.h"

map<string, map<string, string> > seedermap; // map< hash, map<socket, file>>
void writeSeederToFile();

mutex mtx;
fstream seeders;

fstream getFileStream(int mode){
    fstream seeders;
    mtx.lock();
    if(mode==0) seeders.open(seeder_list.c_str(), ios::app);
    else if(mode==1) seeders.open(seeder_list.c_str(), ios::out);
    else if(mode==2) seeders.open(seeder_list.c_str(), ios::in);
    return seeders;
}

void insert(vector<string> s, bool callfromfile){
    // ofstream seeders;
    //string bufback(buffer);
/*
    char *token = strtok(buffer, "|"); 
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    vector<string> s;
    while (token != NULL){ 
        s.push_back(token);
        token = strtok(NULL, "|"); 
    }*/ 
    string entry= s[0]+"|"+s[1]+"|"+s[2] ;
    cout<<"finding "<<s[0]<<endl;
    if(seedermap.find(s[0]) == seedermap.end() ){
        cout<<"not found";
        seedermap[s[0]][s[1]]=s[2];
        if(!callfromfile){
            seeders = getFileStream(0);
            cout<<"entering...."<<endl;
            seeders<< entry <<endl;
            seeders.close();
            mtx.unlock();
        }
    }
    else{
        cout<<"found"<<endl;
        cout<<"finding "<<s[1]<<endl;
        if(seedermap[s[0]].find(s[1]) == seedermap[s[0]].end() ){
            cout<<"not found"<<endl;
            seedermap[s[0]][s[1]]=s[2];
            if(!callfromfile){
                seeders = getFileStream(0);
                cout<<"entering...."<<endl;
                seeders<< entry <<endl;
                seeders.close();
                mtx.unlock();
            }
        }
    }
}

void remove(vector<string> s){
    cout<<"in remove"<<endl;
    // ofstream seeders;
/*
    char *token = strtok(buffer, "|"); 
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    vector<string> s;
    while (token != NULL){ 
        s.push_back(token);
        token = strtok(NULL, "|"); 
    } 
*/
    cout<<"finding in map "<<s[0]<<endl;
    if(seedermap.find(s[0]) != seedermap.end()){
        cout<<s[0]<<" hash found"<<endl;
        seedermap[s[0]].erase(s[1]);
        cout<<s[1]<<" erased from "<<s[0]<<endl;
        cout<<"size "<<seedermap[s[0]].size()<<endl;
        if(seedermap[s[0]].size() == 0){
            cout<<"map empty"<<endl;
            seedermap.erase(s[0]);
        }
    }

    writeSeederToFile();

    cout<<"After remove"<<endl;
    for(auto i:seedermap){
        cout<<i.first<<":"<<endl;
        for(auto j:i.second){
            cout<<j.first<<" "<<j.second<<endl;
        }
        cout<<endl<<endl;
    }
}

string getList(string hash){
    string list;
    for(auto i:seedermap){
        for(auto j:i.second){
            list+=j.first+"|"+j.second+"|";
        }
    }
    return list;
}

void sendSeederList(vector<string> s, int new_socket){
    string list = getList(s[0]);
    send(new_socket , list.c_str() , list.length() , 0 );
} 

void loadSeederFromFile(){

    // ifstream seeders;
    seeders = getFileStream(2);
    
    string temp;
    while(getline(seeders, temp)){
        //insert((char *)temp.c_str(), true);
        char *token = strtok((char *)temp.c_str(), "|"); 
        // Keep printing tokens while one of the 
        // delimiters present in str[]. 
        vector<string> s;
        while (token != NULL){ 
            s.push_back(token);
            token = strtok(NULL, "|"); 
        } 
        
        insert(s, true);

    }
    seeders.close();
    mtx.unlock();
}

void writeSeederToFile(){
    // ofstream seeders;
    seeders = getFileStream(1);

    for(auto i:seedermap){
        for(auto j:i.second){
            seeders<<i.first<<"|"<<j.first<<"|"<<j.second<<endl;
        }
    }
    seeders.close();
    mtx.unlock();
}

int server_fd; 
struct sockaddr_in address; 
int addrlen = sizeof(address); 

void createSocket(){
    // int server_fd; 
    // struct sockaddr_in address; 
    int opt = 1; 
    // int addrlen = sizeof(address); 
    
    
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
    
}

void serveRequest(int new_socket){
    char buffer[1024] = {0}; 
    int valread;

    valread = read( new_socket , buffer, 1024); 
    cout<<buffer<<endl;

    char *token = strtok(buffer, "|"); 
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    vector<string> s;
    while (token != NULL){ 
        s.push_back(token);
        token = strtok(NULL, "|"); 
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
    //insert(buffer, false);
    //remove(buffer);
    for(auto i:seedermap){
        cout<<i.first<<":"<<endl;
        for(auto j:i.second){
            cout<<j.first<<" "<<j.second<<endl;
        }
        cout<<endl<<endl;
    }
    
    // printf("%s\n",buffer ); 
    // send(new_socket , "hello" , strlen("hello") , 0 ); 
    // printf("Hello message sent\n"); 
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

    for(auto i:seedermap){
        cout<<i.first<<":"<<endl;
        for(auto j:i.second){
            cout<<j.first<<" "<<j.second<<endl;
        }
        cout<<endl<<endl;
    }

    createSocket();
    while(1){
        int new_socket;
        cout<<"listening"<<endl;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        thread t(serveRequest, std::ref(new_socket));
        t.join();
    }
}
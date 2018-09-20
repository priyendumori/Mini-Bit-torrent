#include "header.h"
#include "trackerglobal.h"

int server_fd; 
struct sockaddr_in address; 
int addrlen = sizeof(address);

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
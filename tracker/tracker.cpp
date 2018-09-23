#include "header.h"
#include "trackerglobal.h"

int server_fd; 
struct sockaddr_in address; 
int addrlen = sizeof(address);

void log(string s){
    logmtx.lock();
    logger.open(logfile.c_str(), ios::app);

    time_t tt; 
    struct tm * ti; 
    time (&tt); 
    ti = localtime(&tt); 
    string datetime=asctime(ti);
    datetime.pop_back();
    logger<<datetime<<" -> "; 
    logger<<s<<endl;

    logger.close();
    logmtx.unlock();
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
    
    int index = mytracker_IP_port.find_first_of(":");
    mytrackerIP=mytracker_IP_port.substr(0,index);
    mytrackerport=mytracker_IP_port.substr(index+1,4);
    
    index = othertracker_IP_port.find_first_of(":");
    othertrackerIP=othertracker_IP_port.substr(0,index);
    othertrackerport=othertracker_IP_port.substr(index+1,4);
    

    loadSeederFromFile();

    // for(auto i:seedermap){
    //     cout<<i.first<<":"<<endl;
    //     for(auto j:i.second){
    //         cout<<j.first<<" "<<j.second<<endl;
    //     }
    //     cout<<endl<<endl;
    // }
    createSocket();
    log("socket created successfully");
    while(1){
        int new_socket;
        // cout<<"listening"<<endl;
        // log("listening");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            // perror("accept"); 
            log("error in acceting request");
            exit(EXIT_FAILURE); 
        }
        log("request accepted "); 
        thread t(serveRequest, std::ref(new_socket));
        t.join();
    }
}
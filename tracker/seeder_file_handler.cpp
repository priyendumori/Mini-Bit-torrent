#include "header.h"
#include "trackerglobal.h"

fstream getFileStream(int mode){
    fstream seeders;
    mtx.lock();
    if(mode==0) seeders.open(seeder_list.c_str(), ios::app);
    else if(mode==1) seeders.open(seeder_list.c_str(), ios::out);
    else if(mode==2) seeders.open(seeder_list.c_str(), ios::in);
    return seeders;
}

void loadSeederFromFile(){

    // ifstream seeders;
    seeders = getFileStream(2);
    
    string temp;
    while(getline(seeders, temp)){
        //insert((char *)temp.c_str(), true);
        char *token = strtok((char *)temp.c_str(), "*|?"); 
        // Keep printing tokens while one of the 
        // delimiters present in str[]. 
        vector<string> s;
        while (token != NULL){ 
            s.push_back(token);
            token = strtok(NULL, "*|?"); 
        } 
        
        insert(s, true);

    }
    seeders.close();
    mtx.unlock();
    log("seeders loaded from file "+seeder_list);
}

void writeSeederToFile(){
    // ofstream seeders;
    seeders = getFileStream(1);

    for(auto i:seedermap){
        for(auto j:i.second){
            seeders<<i.first<<"*|?"<<j.first<<"*|?"<<j.second<<endl;
        }
    }
    seeders.close();
    mtx.unlock();

    log("seeders loaded to the file "+seeder_list);
}

void insert(vector<string> s, bool callfromfile){
  
    string entry= s[0]+"*|?"+s[1]+"*|?"+s[2] ;
    cout<<"making entry for "<<entry<<endl;
    if(seedermap.find(s[0]) == seedermap.end() ){
        log("entry added to map: "+entry);
        seedermap[s[0]][s[1]]=s[2];
        if(!callfromfile){
            log("entry added to file: "+entry);
            seeders = getFileStream(0);
            seeders<< entry <<endl;
            seeders.close();
            mtx.unlock();
        }
    }
    else{
        if(seedermap[s[0]].find(s[1]) == seedermap[s[0]].end() ){
            log("entry added to map: "+entry);
            seedermap[s[0]][s[1]]=s[2];
            if(!callfromfile){
                log("entry added to file: "+entry);
                seeders = getFileStream(0);
                seeders<< entry <<endl;
                seeders.close();
                mtx.unlock();
            }
        }
    }
}

void remove(vector<string> s){
    if(seedermap.find(s[0]) != seedermap.end()){
        seedermap[s[0]].erase(s[1]);
        log("removed from map: "+s[1]);
        if(seedermap[s[0]].size() == 0){
            seedermap.erase(s[0]);
        }
    }

    writeSeederToFile();

    // cout<<"After remove"<<endl;
    // for(auto i:seedermap){
    //     cout<<i.first<<":"<<endl;
    //     for(auto j:i.second){
    //         cout<<j.first<<" "<<j.second<<endl;
    //     }
    //     cout<<endl<<endl;
    // }
}

void clientOffLine(vector<string> s){
    for(auto l:seedermap){
        cout<<"going for hash "<<l.first<<endl;
        for(auto sock:l.second){
            cout<<"s "<<sock.first<<endl;
            cout<<"sk "<<s[0]<<endl;
            if(sock.first == s[0]){
                log("removing from tracker: "+s[0]);
                seedermap[l.first].erase(s[0]);
                
                if(seedermap[l.first].size() == 0){
                    seedermap.erase(l.first);
                }
            }
        }
    }

    writeSeederToFile();

    // cout<<"After remove"<<endl;
    // for(auto i:seedermap){
    //     cout<<i.first<<":"<<endl;
    //     for(auto j:i.second){
    //         cout<<j.first<<" "<<j.second<<endl;
    //     }
    //     cout<<endl<<endl;
    // }
}
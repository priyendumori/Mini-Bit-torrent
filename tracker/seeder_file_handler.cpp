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

void insert(vector<string> s, bool callfromfile){
  
    string entry= s[0]+"|"+s[1]+"|"+s[2] ;
  
    if(seedermap.find(s[0]) == seedermap.end() ){
        seedermap[s[0]][s[1]]=s[2];
        if(!callfromfile){
            seeders = getFileStream(0);
            seeders<< entry <<endl;
            seeders.close();
            mtx.unlock();
        }
    }
    else{
        if(seedermap[s[0]].find(s[1]) == seedermap[s[0]].end() ){
            seedermap[s[0]][s[1]]=s[2];
            if(!callfromfile){
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
        if(seedermap[s[0]].size() == 0){
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
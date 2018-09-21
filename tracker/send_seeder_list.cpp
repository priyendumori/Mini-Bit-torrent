#include "header.h"
#include "trackerglobal.h"

string getList(string hash){
    string list;
    for(auto i:seedermap[hash]){
        // for(auto j:i.second){
            list+=i.first+"|"+i.second+"|";
        // }
    }
    return list;
}

void sendSeederList(vector<string> s, int new_socket){
    string list = getList(s[0]);
    send(new_socket , list.c_str() , list.length() , 0 );
} 

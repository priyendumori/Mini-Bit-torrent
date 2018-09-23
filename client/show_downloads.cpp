#include "header.h"
#include "clientglobal.h"

void show_down(){
    for(auto i:downloads){
        char status;
        if(i.second==2) status='S';
        if(i.second==1) status='D';
        cout<<status<<" "<<i.first<<endl;
    }
}
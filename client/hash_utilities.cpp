#include "header.h"
#include "clientglobal.h"

string stringhash(string s){
    unsigned char hashbuf[20]; // == 20
    unsigned char hash[40];

    SHA1((unsigned char *)s.c_str(), s.length() , hashbuf);

    //cout<<buffer<<endl;

    for(int i=0;i<20;i++){
        sprintf((char *)&(hash[i*2]), "%02x",hashbuf[i]);            
    }

    string hashstring((char *)hash);
    return hashstring;
}

string computeHash(string filePath){
    ifstream sharedfile;
    sharedfile.open(filePath.c_str(), ios::binary);
    size_t chunksize= 524288;
    char buffer[chunksize]; //reads only the first 1024 bytes
    string filehash="";
    long long size = getFileSize(filePath);
    size_t sizeLeftToHash=size;

    if(sizeLeftToHash < chunksize) chunksize=sizeLeftToHash;
    while(sharedfile.read(buffer, chunksize)) {
        ///do with buffer
        if(chunksize==0) break;
        sizeLeftToHash-=chunksize;
        unsigned char hashbuf[20]; // == 20
        unsigned char hash[40];

        SHA1((unsigned char *)buffer, chunksize , hashbuf);
        
        //cout<<buffer<<endl;

        for(int i=0;i<20;i++){
            sprintf((char *)&(hash[i*2]), "%02x",hashbuf[i]);            
        }
        
        string hashstring((char *)hash);
        //cout<<hashstring<<endl;
        hashstring=hashstring.substr(0,20);
        filehash+=hashstring;
        if(sizeLeftToHash<chunksize) chunksize=sizeLeftToHash;
        // break;
    }
    sharedfile.close();
    return filehash;
}
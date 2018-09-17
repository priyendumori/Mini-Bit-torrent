#include "header.h"
#include "clientglobal.h"

long long getFileSize(string file){
    struct stat sb;
    stat(file.c_str(), &sb);
    return sb.st_size;
}

string computeHash(string filePath){

    ifstream sharedfile;
    sharedfile.open(filePath.c_str(), ios::binary);
    size_t chunksize= 524288;
    char buffer[chunksize]; //reads only the first 1024 bytes
    string filehash="";
    long long size = getFileSize(filePath);
    long long sizeLeftToHash=size;

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

void createTorrentFile(string torrentFileName, string filePath){
    // string tracker1="127.0.0.1:9999";
    // string tracker2="127.0.0.2:9999";

    ofstream mtfile;
    
    //cout<<endl<<endl<<filehash<<endl;
    string filehash=computeHash(filePath);
    cout<<"name "<<torrentFileName<<endl;
    torrentFileName="mTorrent/"+torrentFileName;
    cout<<"name "<<torrentFileName<<endl;
    mtfile.open(torrentFileName.c_str());
    mtfile<<tracker1IP<<":"<<tracker1Port<<endl;
    mtfile<<tracker2IP<<":"<<tracker2Port<<endl;
    mtfile<<filePath<<endl;
    mtfile<<getFileSize(filePath)<<endl;
    mtfile<<filehash;

    mtfile.close();

}

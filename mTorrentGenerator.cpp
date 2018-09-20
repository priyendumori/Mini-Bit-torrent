#include "header.h"
#include "clientglobal.h"

long long getFileSize(string file){
    struct stat sb;
    stat(file.c_str(), &sb);
    return sb.st_size;
}

void createTorrentFile(string torrentFileName, string filePath){
    // string tracker1="127.0.0.1:9999";
    // string tracker2="127.0.0.2:9999";

    ofstream mtfile;
    
    //cout<<endl<<endl<<filehash<<endl;
    string filehash=computeHash(filePath);
    torrentFileName="mTorrent/"+torrentFileName;
    mtfile.open(torrentFileName.c_str());
    mtfile<<tracker1IP<<":"<<tracker1Port<<endl;
    mtfile<<tracker2IP<<":"<<tracker2Port<<endl;
    mtfile<<filePath<<endl;
    mtfile<<getFileSize(filePath)<<endl;
    mtfile<<filehash;

    mtfile.close();

}

/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "clientglobal.h"

/*
    returns size of the file
*/
long long getFileSize(string file)
{
    struct stat sb;
    stat(file.c_str(), &sb);
    return sb.st_size;
}

/*
    creates .mtorrent file as mentioned in specification for input file 
*/
void createTorrentFile(string torrentFileName, string filePath)
{
    ofstream mtfile;

    log("creating mtorrent file for " + filePath);
    string filehash = computeHash(filePath);
    torrentFileName = "mTorrent/" + torrentFileName;
    mtfile.open(torrentFileName.c_str());
    mtfile << tracker1IP << ":" << tracker1Port << endl;
    mtfile << tracker2IP << ":" << tracker2Port << endl;

    if (filePath[0] != '/' && filePath[0] != '~')
    {
        char buffer[1000];
        getcwd(buffer, 1000);
        string pwd(buffer);
        filePath = pwd + "/" + filePath;
    }
    mtfile << filePath << endl;
    mtfile << getFileSize(filePath) << endl;
    mtfile << filehash;

    mtfile.close();
    log("mtorrent file created for " + filePath);
}

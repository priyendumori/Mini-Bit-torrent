/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/
#include "header.h"
#include "clientglobal.h"

/*
    called at startup
    
    iterates through mTorrent folder and for every mtorrent file found,
    an entry is made in tracker's seeder list by sending request to tracker
*/
void shareDetailsOfExistingTorrent()
{
    string foldername = "./mTorrent";
    DIR *dirp = opendir(foldername.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL)
    {
        if (dp->d_name == "." || dp->d_name == "..")
            continue;
        string n = dp->d_name;
        int in = n.find_last_of(".");
        string ext = n.substr(in + 1);
        if (ext != "mtorrent")
            continue;

        notifyTracker(dp->d_name);
    }
    closedir(dirp);
    log("details from mTorrent folder shared");
}

/*
    generates a request to notify tracker about this client being seeder for some file
    then sends the request to tracker
*/
void notifyTracker(string mtorrentName)
{

    string sendstring = getStringToSend(mtorrentName, 0);

    int sock = create_socket("", "", false);
    log("sending request to notify tracker about " + mtorrentName);
    send(sock, sendstring.c_str(), sendstring.length(), 0);
    log("tracker notified about " + mtorrentName);
    cout << "SUCCESS: " + mtorrentName << endl;
    close(sock);
}

/*
    creates mtorrent file
    notifies tracker about the client being a seeder of that file
*/
void share(string filePath, string mtorrentName)
{
    if (!file_exists(filePath))
    {
        cout << "FAILURE: FILE_NOT_FOUND" << endl;
        return;
    }
    createTorrentFile(mtorrentName, filePath);
    notifyTracker(mtorrentName);
}
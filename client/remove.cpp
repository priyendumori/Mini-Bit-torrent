/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "clientglobal.h"

/*
    removes entry of this IP and port from tracker's seeder list
    and deletes mtorrent file from the machine
*/
void removeTorrent(string mtorrentName)
{

    if (!file_exists("./mTorrent/" + mtorrentName))
    {
        cout << "FAILURE: FILE_NOT_FOUND" << endl;
        return;
    }

    string sendstring = getStringToSend(mtorrentName, 1);

    int sock = create_socket("", "", false);
    log("remove request sent for " + mtorrentName);
    send(sock, sendstring.c_str(), sendstring.length(), 0);
    log("entry corresponding to " + mtorrentName + " removed ");
    mtorrentName = "./mTorrent/" + mtorrentName;
    remove(mtorrentName.c_str());
    log(mtorrentName + " removed from file system ");
    cout << "SUCCESS: FILE_REMOVED" << endl;
    close(sock);
}
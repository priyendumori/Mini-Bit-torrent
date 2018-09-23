/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "clientglobal.h"

/*
    On entering exit user goes offline
    and this function removes all entries of this IP and port 
    from tracker's seeder_list 
*/
void closeClient()
{
    int sock = create_socket("", "", false);
    string sendstring = clientIP + ":" + clientPort + "*|?" + to_string(3);
    log("sending request to remove client info from tracker");
    send(sock, sendstring.c_str(), sendstring.length(), 0);
    log("request sent for removing client info from tracker");
    close(sock);
    log("client closed");
    exit(0);
}
/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "trackerglobal.h"

/*
    takes a hash of hash of a file as input
    and returns all the seeders for it
*/
string getList(string hash)
{
    string list;
    for (auto i : seedermap[hash])
    {
        list += i.first + "*|?" + i.second + "*|?";
    }
    return list;
}

/*
    send the seeder list to the client requesting for it
*/
void sendSeederList(vector<string> s, int new_socket)
{
    string list = getList(s[0]);
    log("sending seederlist for " + s[0]);
    send(new_socket, list.c_str(), list.length(), 0);
    log("seeder list sent");
    close(new_socket);
    return;
}

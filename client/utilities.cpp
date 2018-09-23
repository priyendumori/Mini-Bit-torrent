/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "clientglobal.h"

/*
    method that logs messages in log file
*/
void log(string s)
{
    logmtx.lock();
    logger.open(logfile.c_str(), ios::app);

    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
    string datetime = asctime(ti);
    datetime.pop_back();
    logger << datetime << " -> ";
    logger << s << endl;

    logger.close();
    logmtx.unlock();
}

/*
    checks if file exists or not
*/
bool file_exists(string name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

/*
    generates request to be sent using information from 
    mtorrent file and type passed by user
    type    meaning
     0      share
     1      remove
     2      get
     3      exit
*/
string getStringToSend(string mtorrentName, int type)
{
    mtorrentName = "./mTorrent/" + mtorrentName;
    string send;
    ifstream mt;
    mt.open(mtorrentName);
    string path, hashOfHash;
    for (int i = 0; i < 5; i++)
    {
        string temp;
        getline(mt, temp);
        if (i == 2)
        {
            path = temp;
        }
        if (i == 4)
        {
            hashOfHash = stringhash(temp);
        }
    }
    mt.close();

    send = hashOfHash + "*|?";
    send += clientIP + ":" + clientPort + "*|?";
    send += path + "*|?" + to_string(type);
    return send;
}

/*
    initializes ip and ports of client and trackers
*/
void initializeGlobalVariables(string client_IP_port, string t1_IP_port, string t2_IP_port)
{

    vector<string> s=tokenize(client_IP_port,":");
    clientIP=s[0];
    clientPort=s[1];
    s.clear();

    s=tokenize(t1_IP_port,":");
    tracker1IP=s[0];
    tracker1Port=s[1];
    s.clear();

    s=tokenize(t1_IP_port,":");
    tracker2IP=s[0];
    tracker2Port=s[1];
    s.clear();
}

/*
    helper function that tokenizes string 
    "str" with delimter "d"
*/
vector<string> tokenize(string str, string d)
{
    char *token = strtok((char *)str.c_str(), d.c_str());

    vector<string> s;
    while (token != NULL)
    {
        s.push_back(token);
        token = strtok(NULL, d.c_str());
    }

    return s;
}
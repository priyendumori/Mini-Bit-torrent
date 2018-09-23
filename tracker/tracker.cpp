/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "trackerglobal.h"

int server_fd;
struct sockaddr_in address;
int addrlen = sizeof(address);

/*
    writes log message to log file
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

/*
    initializes global variable
    and calls driver function in a thread
*/
int main(int argc, char **argv)
{
    if (argc < 4)
    {
        cout << "too few arguments" << endl;
        return 1;
    }
    string mytracker_IP_port = argv[1];
    string othertracker_IP_port = argv[2];
    seeder_list = argv[3];
    logfile = argv[4];

    vector<string> s=tokenize(mytracker_IP_port,":");
    mytrackerIP=s[0];
    mytrackerport=s[1];
    s.clear();

    s=tokenize(othertracker_IP_port,":");
    othertrackerIP=s[0];
    othertrackerport=s[1];
    s.clear();

    loadSeederFromFile();
    createSocket();
    log("socket created successfully");
    while (1)
    {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0)
        {
            log("error in acceting request");
            exit(EXIT_FAILURE);
        }
        log("request accepted ");
        thread t(serveRequest, new_socket);
        t.detach();
    }
}
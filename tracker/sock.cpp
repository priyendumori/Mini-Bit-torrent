/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "trackerglobal.h"

extern int server_fd;
extern struct sockaddr_in address;
extern int addrlen;

/*
    creates socket
    and start listening for client
*/
void createSocket()
{
    int opt = 1;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log("socket failed");
        exit(EXIT_FAILURE);
    }
    log("socket created");
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        log("setsockopt error");
        exit(EXIT_FAILURE);
    }
    log("socket options set");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(mytrackerIP.c_str());
    address.sin_port = htons(atoi(mytrackerport.c_str()));

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        log("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        log("listen error");
        exit(EXIT_FAILURE);
    }
    log("listening at " + mytrackerIP + ":" + mytrackerport);
}

/*
    driver function that reads requests,
    interpret it and call apropriate function
*/
void serveRequest(int new_socket)
{
    char buffer[1024] = {0};

    read(new_socket, buffer, 1024);

    char *token = strtok(buffer, "*|?");
    vector<string> s;
    while (token != NULL)
    {
        s.push_back(token);
        token = strtok(NULL, "*|?");
    }

    if (s[s.size() - 1] == "0")
    {
        insert(s, false);
    }
    else if (s[s.size() - 1] == "1")
    {
        remove(s);
    }
    else if (s[s.size() - 1] == "2")
    {
        sendSeederList(s, new_socket);
    }
    else if (s[s.size() - 1] == "3")
    {
        clientOffLine(s);
    }
    else
    {
        cout << "couldn't identify request" << endl;
    }
}

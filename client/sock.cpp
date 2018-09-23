/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "clientglobal.h"


/*
    creates a socket
    and returns socket descriptor for it
*/
int create_socket(string ip, string port, bool connectToIP)
{

    int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        log("Socket creation error");
        return -1;
    }
    log("socket created");
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    if (connectToIP)
        serv_addr.sin_port = htons(atoi(port.c_str()));
    else
        serv_addr.sin_port = htons(atoi(tracker1Port.c_str()));

    string sendIP;

    if (connectToIP)
        sendIP = ip;
    else
        sendIP = tracker1IP;
    if (inet_pton(AF_INET, sendIP.c_str(), &serv_addr.sin_addr) <= 0)
    {
        log("Invalid address/ Address not supported");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        log("Connection Failed");
        return -1;
    }
    log("connected");
    return sock;
}

/*
    makes client listen at port given during running
    to handle download requests from other clients
*/
void startListening()
{
    int server_fd;
    struct sockaddr_in address;
    int addrlen;

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
    log("sock options set");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(clientIP.c_str());
    address.sin_port = htons(atoi(clientPort.c_str()));

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        log("bind failed");
        exit(EXIT_FAILURE);
    }
    log("socket binded");
    if (listen(server_fd, 3) < 0)
    {
        log("listen error");
        exit(EXIT_FAILURE);
    }
    log("listening at " + clientIP + ":" + clientPort);

    while (1)
    {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0)
        {
            log("error in accepting request");
            exit(EXIT_FAILURE);
        }
        log("request accepted ");
        char buffer1[1024] = {0};
        read(new_socket, buffer1, 1024);
        string filePath(buffer1);
        log("request to download " + filePath + " received ");

        ifstream sharedfile;
        sharedfile.open(buffer1, ios::binary);
        size_t chunksize = 524288;
        char buffer[chunksize];

        long long size = getFileSize(filePath);
        size_t sizeLeftToSend = size;

        log("sending data in chunks for " + filePath);
        if (sizeLeftToSend < chunksize)
            chunksize = sizeLeftToSend;
        while (sharedfile.read(buffer, chunksize))
        {
            sizeLeftToSend -= chunksize;

            send(new_socket, buffer, chunksize, 0);

            if (chunksize == 0)
                break;
            if (sizeLeftToSend < chunksize)
                chunksize = sizeLeftToSend;
        }
        sharedfile.close();
        log(filePath + " sent");
        close(new_socket);
    }
}
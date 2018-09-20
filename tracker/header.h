#include <fstream>
#include <sys/stat.h>
#include <openssl/sha.h>
#include <iostream>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

fstream getFileStream(int );
void insert(vector<string> , bool );
void remove(vector<string> );
string getList(string );
void sendSeederList(vector<string> , int );
void createSocket();
void serveRequest(int );
void writeSeederToFile();
void loadSeederFromFile();
void log(string );
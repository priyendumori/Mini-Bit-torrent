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
#include <math.h>

using namespace std;

void createTorrentFile(string, string);
void shareDetailsOfExistingTorrent();
void share(string, string);
void removeTorrent(string);
string getStringToSend(string, int);
void get(string, string);
void initializeGlobalVariables(string , string ,string);
vector<string> tokenize(string ,string);
string computeHash(string );
long long getFileSize(string );
string stringhash(string );
string getStringToSend(string , int);
int create_socket(string, string, bool);
void log(string);
void startListening();
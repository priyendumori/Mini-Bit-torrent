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

using namespace std;

void createTorrentFile(string, string);
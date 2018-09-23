#include "header.h"

string clientIP;
string clientPort;
string tracker1IP;
string tracker1Port;
string tracker2IP;
string tracker2Port;
string logfile;
mutex logmtx;
fstream logger;
map<string, int> downloads;
#include "header.h"

string mytrackerIP;
string mytrackerport;
string othertrackerIP;
string othertrackerport;
string seeder_list;
string logfile;

map<string, map<string, string> > seedermap; // map< hash, map<socket, file>>
mutex mtx;
mutex logmtx;
fstream seeders;
fstream logger;

#include "header.h"

extern string mytrackerIP;
extern string mytrackerport;
extern string othertrackerIP;
extern string othertrackerport;
extern string seeder_list;
extern string logfile;

extern map<string, map<string, string> > seedermap; // map< hash, map<socket, file>>
extern mutex mtx;
extern fstream seeders;
extern mutex logmtx;
extern fstream logger;
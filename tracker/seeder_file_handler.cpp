/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "trackerglobal.h"

/*
    get fstream object of the shared file that contains seeders list
*/
fstream getFileStream(int mode)
{
    fstream seeders;
    mtx.lock();
    if (mode == 0)
        seeders.open(seeder_list.c_str(), ios::app);
    else if (mode == 1)
        seeders.open(seeder_list.c_str(), ios::out);
    else if (mode == 2)
        seeders.open(seeder_list.c_str(), ios::in);
    return seeders;
}

/*
    at tracker startup loads seeders from file to data structure
*/
void loadSeederFromFile()
{

    seeders = getFileStream(2);

    string temp;
    while (getline(seeders, temp))
    {
        char *token = strtok((char *)temp.c_str(), "*|?");
        vector<string> s;
        while (token != NULL)
        {
            s.push_back(token);
            token = strtok(NULL, "*|?");
        }

        insert(s, true);
    }
    seeders.close();
    mtx.unlock();
    log("seeders loaded from file " + seeder_list);
}

/*
    write seeder information from data structure to seeder file
*/
void writeSeederToFile()
{
    seeders = getFileStream(1);

    for (auto i : seedermap)
    {
        for (auto j : i.second)
        {
            seeders << i.first << "*|?" << j.first << "*|?" << j.second << endl;
        }
    }
    seeders.close();
    mtx.unlock();

    log("seeders loaded to the file " + seeder_list);
}

/*
    inserts ip and port of client to seeder list
    inserts to file and data structure both if callfromfile is false
    inserts to data strcuture only if callfromfile is true
*/
void insert(vector<string> s, bool callfromfile)
{

    string entry = s[0] + "*|?" + s[1] + "*|?" + s[2];
    if (seedermap.find(s[0]) == seedermap.end())
    {
        log("entry added to map: " + entry);
        seedermap[s[0]][s[1]] = s[2];
        if (!callfromfile)
        {
            log("entry added to file: " + entry);
            seeders = getFileStream(0);
            seeders << entry << endl;
            seeders.close();
            mtx.unlock();
        }
    }
    else
    {
        if (seedermap[s[0]].find(s[1]) == seedermap[s[0]].end())
        {
            log("entry added to map: " + entry);
            seedermap[s[0]][s[1]] = s[2];
            if (!callfromfile)
            {
                log("entry added to file: " + entry);
                seeders = getFileStream(0);
                seeders << entry << endl;
                seeders.close();
                mtx.unlock();
            }
        }
    }
}

/*
    removes ip and port of a client from a particular hash's seeder list 
*/
void remove(vector<string> s)
{
    if (seedermap.find(s[0]) != seedermap.end())
    {
        seedermap[s[0]].erase(s[1]);
        log("removed from map: " + s[1]);
        if (seedermap[s[0]].size() == 0)
        {
            seedermap.erase(s[0]);
        }
    }

    writeSeederToFile();
}

/*
    remove ip and port of client going offline from all hash's seeder list
*/
void clientOffLine(vector<string> s)
{
    for (auto l : seedermap)
    {
        for (auto sock : l.second)
        {
            if (sock.first == s[0])
            {
                log("removing from tracker: " + s[0]);
                seedermap[l.first].erase(s[0]);

                if (seedermap[l.first].size() == 0)
                {
                    seedermap.erase(l.first);
                }
            }
        }
    }

    writeSeederToFile();
}
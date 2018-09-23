/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "clientglobal.h"

/*
    takes a string as input
    returns SHA1 hash of that string
*/
string stringhash(string s)
{
    unsigned char hashbuf[20];
    unsigned char hash[40];

    SHA1((unsigned char *)s.c_str(), s.length(), hashbuf);

    for (int i = 0; i < 20; i++)
    {
        sprintf((char *)&(hash[i * 2]), "%02x", hashbuf[i]);
    }

    string hashstring((char *)hash);
    return hashstring;
}

/*
    takes file (filePath) as input
    returns concatenation of 20 characters of 
    SHA1 hash of each 512KB chunk of the file
*/
string computeHash(string filePath)
{
    log("calculating SHA1 of " + filePath);
    ifstream sharedfile;
    sharedfile.open(filePath.c_str(), ios::binary);
    size_t chunksize = 524288;
    char buffer[chunksize];
    string filehash = "";
    long long size = getFileSize(filePath);
    size_t sizeLeftToHash = size;

    if (sizeLeftToHash < chunksize)
        chunksize = sizeLeftToHash;
    while (sharedfile.read(buffer, chunksize))
    {
        if (chunksize == 0)
            break;
        sizeLeftToHash -= chunksize;
        unsigned char hashbuf[20];
        unsigned char hash[40];

        SHA1((unsigned char *)buffer, chunksize, hashbuf);

        for (int i = 0; i < 20; i++)
        {
            sprintf((char *)&(hash[i * 2]), "%02x", hashbuf[i]);
        }

        string hashstring((char *)hash);
        hashstring = hashstring.substr(0, 20);
        filehash += hashstring;
        if (sizeLeftToHash < chunksize)
            chunksize = sizeLeftToHash;
    }
    sharedfile.close();
    log("SHA1 calculated");
    return filehash;
}
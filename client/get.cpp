/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "clientglobal.h"

/*
    reads mtorrentfile (mtorrentName)
    send path of the required file to the seeder
    read chunks sent by the seeder
    write to destination file (downpath)
*/
void download(vector<pair<string, string>> seederpair, string mtorrentName, string downpath)
{
    mtorrentName = "./mTorrent/" + mtorrentName;
    ifstream mt;
    mt.open(mtorrentName);
    string path;
    int size;
    for (int i = 0; i < 5; i++)
    {
        string temp;
        getline(mt, temp);

        if (i == 2)
        {
            path = temp;
        }
        if (i == 3)
        {
            size = stoi(temp);
        }
    }
    mt.close();

    char *token = strtok((char *)seederpair[0].first.c_str(), ":");
    string ip = token;
    token = strtok(NULL, ":");
    string port = token;
    int cl_sock = create_socket(ip, port, true);
    log("path of file to be downloaded sent: " + path);
    send(cl_sock, path.c_str(), path.length(), 0);

    char buffer[524288] = {0};
    ofstream file;
    file.open(downpath);

    log("download " + downpath + " starting");
    int rec_l;
    do
    {
        rec_l = read(cl_sock, buffer, 524288);
        file.write(buffer, rec_l);
    } while (rec_l > 0);
    file.close();
    log("downloaded " + downpath);
    cout << "SUCCESS: " + downpath << endl;
    downloads[downpath]++;

    close(cl_sock);
}

/*
    sends get request to tracker
    receives seeder list from tracker for that particular file
    takes first seeder
    connects with that seeder
    and download file from that seeder
*/
void get(string mtorrentName, string downpath)
{

    wordexp_t exp_result;
    wordexp(downpath.c_str(), &exp_result, 0);
    downpath=exp_result.we_wordv[0];
    wordfree(&exp_result);

    if (file_exists(downpath))
    {
        cout << "FAILURE: ALREADY_EXISTS" << endl;
        return;
    }
    if (!file_exists("./mTorrent/" + mtorrentName))
    {
        cout << "FAILURE: MTORRENT_FILE_NOT_FOUND" << endl;
        return;
    }
    string sendstring = getStringToSend(mtorrentName, 2);
    string hash(sendstring);
    hash = hash.substr(0, hash.find_first_of("*|?"));
    char buffer[1024] = {0};

    int sock = create_socket("", "", false);

    log("sending request to get seeder list for " + mtorrentName);
    send(sock, sendstring.c_str(), sendstring.length(), 0);
    log("seeder list received");
    read(sock, buffer, 1024);
    close(sock);
    vector<string> seeder;
    seeder = tokenize(buffer, "*|?");
    vector<pair<string, string>> seederpair;
    for (int i = 0; i < seeder.size(); i += 2)
    {
        seederpair.push_back({seeder[i], seeder[i + 1]});
    }

    if (downpath[0] != '/' && downpath[0] != '~')
    {
        char buffer[1000];
        getcwd(buffer, 1000);
        string pwd(buffer);
        downpath = pwd + "/" + downpath;
    }

    string shareinfo = hash + "*|?" + clientIP + ":" + clientPort + "*|?" + downpath + "*|?" + "0";
    sock = create_socket("", "", false);
    log("request sent to add " + clientIP + ":" + clientPort + " as a seeder for " + downpath);
    send(sock, shareinfo.c_str(), shareinfo.length(), 0);
    log(clientIP + ":" + clientPort + " seeds " + downpath + " now");
    downloads[downpath] = 1;

    thread t(download, seederpair, mtorrentName, downpath);
    t.detach();
    close(sock);
}
/**
------------------------
 * Created by Maroš Orsák
 * Date - 02/10/2019
 * Time - 22:46
 * File - Server.h
-------------------------
**/

#ifndef ISA_SERVER_H
#define ISA_SERVER_H

#include <string>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <map>
#include <vector>
#include "Controller.h"

class Server {
private:
    int port;
    std::string url;
    int serverListeningFileDescriptor;
    int connectedFileDescriptor;
    struct sockaddr_in address;
    struct sockaddr_in clientAddress;
    int addressLength;
    char message[1024];
    pid_t processId;
    std::map<std::string, std::string> header;
public:
    void setPort(int port);
    const std::string &getUrl() const;

    void preRun();
    void run();

    void createSocket();
    void bindSocket();
    void prepareQueueForClients();
    void acceptClient();

    Server();
    Server(std::string url, int port, int serverListeningFileDescriptor, struct sockaddr_in address);
    ~Server();
};


#endif //ISA_SERVER_H

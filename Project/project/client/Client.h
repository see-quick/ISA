/**
------------------------
 * Created by Maroš Orsák
 * Date - 03/10/2019
 * Time - 22:02
 * File - Client.h
-------------------------
**/

#ifndef ISA_CLIENT_H
#define ISA_CLIENT_H

#include <string>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>


class Client {
private:
    std::string url;
    int port;
    int clientFileDescriptor;
    struct sockaddr_in address;
    char message[1024];
public:
    void setUrl(const std::string &url);
    void setPort(int port);
    void preRun();
    void run(int argc, char** argv);

    Client();
    ~Client();
};


#endif //ISA_CLIENT_H

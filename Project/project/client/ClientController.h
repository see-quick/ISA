/**
------------------------
 * Created by Maroš Orsák
 * Date - 13/10/2019
 * Time - 20:39
 * File - ClientController.h
-------------------------
**/

#ifndef ISA_CLIENTCONTROLLER_H
#define ISA_CLIENTCONTROLLER_H


#include <string>
#include <map>

class ClientController {
private:
    std::string url;
    int port;
    std::string nameOfTheBoard;
    std::string content;
    std::string id;
    std::string method;
public:

    std::string buildGet();
    std::string buildPost();
    std::string buildPut();
    std::string buildDelete();

    std::string buildRequest(std::string method);
    std::string buildRequest(std::string method, std::string nameOfTheBoard);
    std::string buildRequest(std::string method, std::string nameOfTheBoard, std::string content);
    std::string buildRequest(std::string method, std::string nameOfTheBoard, std::string id, std::string content);

    ClientController(std::string url, int port);
    ~ClientController();
};


#endif //ISA_CLIENTCONTROLLER_H

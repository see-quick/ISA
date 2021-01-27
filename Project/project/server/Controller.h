/**
------------------------
 * Created by Maroš Orsák
 * Date - 09/10/2019
 * Time - 21:11
 * File - Controller.h
-------------------------
**/

#ifndef ISA_CONTROLLER_H
#define ISA_CONTROLLER_H

#include <string>
#include <map>
#include <regex>
#include <iostream>
#include "Boards.h"

class Controller {
private:
    std::string endpoint;
    std::string method;
    std::string httpVersion;
    std::map<std::string, std::string> headers;
    std::string body;
    Boards boards;

    std::string nameOfTheBoard;
    std::string orderOfCommend;
public:
    std::string getNameBoardFromEndpoint();
    std::string getOrderOfCommend();
    std::string getNameOfTheBoard();

    std::string handleGet();
    std::string handlePost();
    std::string handlePut();
    std::string handleDelete();

    std::string executeMethod();
    void setMethodHeadersEndpoint(std::map<std::string, std::string> httpHeaders, std::string body);
    Controller(Boards boards);
    ~Controller();
};


#endif //ISA_CONTROLLER_H

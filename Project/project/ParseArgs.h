/**
------------------------
 * Created by Maroš Orsák
 * Date - 15/10/2019
 * Time - 20:09
 * File - ParseArgs.h
-------------------------
**/

#ifndef ISA_PARSEARGS_H
#define ISA_PARSEARGS_H

#include <iostream>
#include <cstring>
#include <regex>

class ParseArgs {
private:
    int serverPort;
    std::string serverHost;

    void serverHelp();
    void clientHelp();

    void verifyParameterH(char** argv);
    void verifyParameterP(char** argv);
    void verifyParameterCommand(int argc, char** argv);
public:
    int getServerPort() const;
    const std::string &getServerHost() const;

    void parseServerArgs(int argc, char** argv);
    void parseClientArgs(int argc, char** argv);

    ParseArgs();
    ~ParseArgs();
};


#endif //ISA_PARSEARGS_H

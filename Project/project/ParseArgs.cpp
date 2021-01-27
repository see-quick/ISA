/**
------------------------
 * Created by Maroš Orsák
 * Date - 15/10/2019
 * Time - 20:09
 * File - ParseArgs.cpp
-------------------------
**/

#include <netdb.h>
#include <arpa/inet.h>
#include "ParseArgs.h"

/***
 * Contructor for the ParseArgs
 */
ParseArgs::ParseArgs() {}

/***
 * Destructor for the ParseArgs
 */
ParseArgs::~ParseArgs() {}

/***
 * Method, which parse and checks server arguments
 * @param argc count of arguments
 * @param argv values of arguments
 */
void ParseArgs::parseServerArgs(int argc, char **argv) {
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0) {
            serverHelp();
            exit(EXIT_SUCCESS);
        } else {
            std::cout << "ERROR: Wrong input parameter should be '-h'" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 3) {
        if (((strcmp(argv[1], "-p")) == 0)) {
            int port = 0;

            try {
                port = std::stoi(argv[2]);
                if (port <= 1024 || port > 65535) {
                    std::cout << "ERROR: You type invalid port number need be in range <1025-65535>" << std::endl;
                    serverHelp();
                    exit(EXIT_FAILURE);
                }
            } catch (std::invalid_argument) {
                std::cout << "You didn't type a number" << std::endl;
                serverHelp();
                exit(EXIT_FAILURE);
            }

            if (std::isdigit(port) == 0) {
                this->serverPort = port;
                return;
            }
        }
        std::cout << "Wrong input of parameters" << std::endl;
        serverHelp();
        exit(EXIT_FAILURE);
    } else {
        std::cout << "Wrong number of arguments" << std::endl;
        serverHelp();
        exit(EXIT_FAILURE);
    }
}

void ParseArgs::serverHelp() {
    std::cout <<
              "================ ISA SERVER HELP ================" << std::endl <<
              "Usage:" << std::endl <<
              "\t ./isaserver -p <port-number>" << std::endl <<
              "\t ./isaserver -h" << std::endl <<
              "Example:" << std::endl <<
              "\t ./isaserver -p 12000" << std::endl <<
              "\t ./isaserver -h" << std::endl;
}

/***
 * Method, which parse and checks client arguments
 * @param argc count of arguments
 * @param argv values of arguments
 */
void ParseArgs::parseClientArgs(int argc, char **argv) {
    if (argc == 2) {
        if(strcmp(argv[1], "-h") == 0) {
            ParseArgs::clientHelp();
            exit(EXIT_SUCCESS);
        }
        else {
            std::cout << "ERROR: Wrong input parameter should be '-h'" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 6 || argc == 8 || argc == 9 || argc == 10) {
        ParseArgs::verifyParameterH(argv);
        ParseArgs::verifyParameterP(argv);
        ParseArgs::verifyParameterCommand(argc, argv);
    }
    else {
        std::cout << "ERROR: Wrong number of parameters" << std::endl;
        ParseArgs::clientHelp();
        exit(EXIT_FAILURE);
    }
}

/***
 * Method, which parse and checks client option -H <address>
 * @param argv values of arguments
 */
void ParseArgs::verifyParameterH(char** argv) {
    if (strcmp(argv[1], "-H") == 0) {
        if (std::regex_match(argv[2], std::regex ("\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b"))) {

        } else {
            hostent *record = gethostbyname(argv[2]);
            if (record == NULL) {
                std::cout << "ERROR: You typed wrong hostname" << std::endl;
                ParseArgs::clientHelp();
                exit(EXIT_FAILURE);
            }
            argv[2] = inet_ntoa(*((struct in_addr*) record->h_addr_list[0]));
        }
        this->serverHost = argv[2];
    }
    else {
        std::cout << "ERROR: Wrong -H input" << std::endl;
        ParseArgs::clientHelp();
        exit(EXIT_FAILURE);
    }
}

/***
 * Method, which parse and checks client option -p <port-number>
 * @param argv values of arguments
 */
void ParseArgs::verifyParameterP(char** argv) {
    if (strcmp(argv[3], "-p") == 0) {

        try {
            serverPort = std::stoi(argv[4]);
            if (serverPort <= 1024 || serverPort > 65535) {
                std::cout << "ERROR: You type invalid port number need be in range <1025-65535>" << std::endl;
                serverHelp();
                exit(EXIT_FAILURE);
            }
        } catch (std::invalid_argument) {
            std::cout << "You didn't type a number" << std::endl;
            ParseArgs::serverHelp();
            exit(EXIT_FAILURE);
        }
    } else {
        std::cout << "ERROR: Wrong -p input" << std::endl;
        ParseArgs::clientHelp();
        exit(EXIT_FAILURE);
    }
}

/***
 * Method, which parse and checks client option <command>
 * @param argc count of arguments
 * @param argv values of arguments
 */
void ParseArgs::verifyParameterCommand(int argc, char** argv) {
    if (argc == 6) {
        if (strcmp(argv[5], "boards") == 0) {
            return;
        } else {
            std::cout << "ERROR: Wrong used parameter" << std::endl;
            ParseArgs::clientHelp();
            exit(EXIT_FAILURE);
        }
    } else if (argc == 8) {
        if (strcmp(argv[5], "board") == 0) {
            if ((strcmp(argv[6], "add") == 0) || (strcmp(argv[6], "delete") == 0) || (strcmp(argv[6], "list") == 0)) {
                std::regex boardName( "\\b^[a-zA-Z0-9]*$\\b");
                if (std::regex_match(argv[7], boardName)) {
                    return;
                }
                else {
                    std::cout << "ERROR: Wrong name of board should contains only [a-zA-Z0-9]" << std::endl;
                    ParseArgs::clientHelp();
                    exit(EXIT_FAILURE);
                }
            }
            else {
                std::cout << "ERROR: Wrong used method supported only: add | delete | list" << std::endl;
                ParseArgs::clientHelp();
                exit(EXIT_FAILURE);
            }
        } else {
            std::cout << "ERROR: Wrong used parameter supported only: board" << std::endl;
            ParseArgs::clientHelp();
            exit(EXIT_FAILURE);
        }
    } else if (argc == 9) {
        if (strcmp(argv[5], "item") == 0) {
            if ((strcmp(argv[6], "add") == 0) || (strcmp(argv[6], "delete") == 0)) {
                std::regex boardName( "\\b^[a-zA-Z0-9]*$\\b");
                if (std::regex_match(argv[7], boardName)) {
                    return;
                }
                else {
                    std::cout << "ERROR: Wrong name of board should contains only [a-zA-Z0-9]" << std::endl;
                    ParseArgs::clientHelp();
                    exit(EXIT_FAILURE);
                }
            }
            else {
                std::cout << "ERROR: Wrong used method supported only: add | delete " << std::endl;
                ParseArgs::clientHelp();
                exit(EXIT_FAILURE);
            }
        } else {
            std::cout << "ERROR: Wrong used parameter supported only: item" << std::endl;
            ParseArgs::clientHelp();
            exit(EXIT_FAILURE);
        }
    } else if (argc == 10) {
        if (strcmp(argv[5], "item") == 0) {
            if ((strcmp(argv[6], "update") == 0)) {
                std::regex boardName( "\\b^[a-zA-Z0-9]*$\\b");
                if (std::regex_match(argv[7], boardName)) {
                    try {
                        std::stoi(argv[8]);
                    } catch (std::invalid_argument) {
                        std::cout << "You didn't type a number for id parameter" << std::endl;
                        ParseArgs::clientHelp();
                        exit(EXIT_FAILURE);
                    }
                    return;
                }
                else {
                    std::cout << "ERROR: Wrong name of board should contains only [a-zA-Z0-9]" << std::endl;
                    ParseArgs::clientHelp();
                    exit(EXIT_FAILURE);
                }
            }
            else {
                std::cout << "ERROR: Wrong used method supported only: add | delete " << std::endl;
                ParseArgs::clientHelp();
                exit(EXIT_FAILURE);
            }
        } else {
            std::cout << "ERROR: Wrong used parameter supported only: item" << std::endl;
            ParseArgs::clientHelp();
            exit(EXIT_FAILURE);
        }
    }
}

void ParseArgs::clientHelp() {
    std::cout <<
            "================ ISA CLIENT HELP ================" << std::endl <<
            "Usage:" << std::endl <<
            " ./isaclient -H <host> -p <port-number> <command>" << std::endl <<
            "    where <command> could be as follows:" << std::endl <<
            "\t 1) boards                                 ----- LIST ALL BOARDS" << std::endl <<
            "\t 2) board add boardName                    ----- ADD NEW BOARD" << std::endl <<
            "\t 3) board delete boardName                 ----- DELETE BOARD" << std::endl <<
            "\t 4) board list boardName                   ----- LIST COMMENDS OF BOARD" << std::endl <<
            "\t 5) item add boardName content             ----- ADD COMMEND TO BOARD" << std::endl <<
            "\t 6) item delete boardName id               ----- DELETE COMMEND OF BOARD" << std::endl <<
            "\t 7) item update boardName id/order content ----- UPDATE COMMEND OF BOARD" << std::endl <<
            "\t ./isaclient -h" << std::endl <<
            "Example:" << std::endl <<
            "\t ./isaserver -H localhost -p 12000 boards" << std::endl <<
            "---------------------------------------------" << std::endl <<
            "\t ./isaserver -H localhost -p 12000 board add myNewBoard" << std::endl <<
            "\t ./isaserver -H localhost -p 12000 board delete myNewBoard" << std::endl <<
            "\t ./isaserver -H localhost -p 12000 board list myNewBoard" << std::endl <<
            "---------------------------------------------" << std::endl <<
            "\t ./isaserver -H localhost -p 12000 item add myNewBoard newCommendMessage" << std::endl <<
            "\t ./isaserver -H localhost -p 12000 item delete myNewBoard 1" << std::endl <<
            "---------------------------------------------" << std::endl <<
            "\t ./isaserver -H localhost -p 12000 item update myNewBoard 1 newCommendMessage" << std::endl <<
            "\t ./isaserver -h" << std::endl;
}

int ParseArgs::getServerPort() const {
    return serverPort;
}

const std::string &ParseArgs::getServerHost() const {
    return serverHost;
}
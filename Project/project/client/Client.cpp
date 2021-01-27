/**
------------------------
 * Created by Maroš Orsák
 * Date - 03/10/2019
 * Time - 22:02
 * File - Client.cpp
-------------------------
**/

#include <sstream>
#include "Client.h"
#include "ClientController.h"

Client::Client() {}

Client::~Client() {}

/**
 * Method which initialize basic fields
 */
void Client::preRun() {
    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr( url.data() );
}

/**
 * Method which is root of the project. Taking care of creating communication and trying to connect to server.
 * @param argc number of arguments
 * @param argv values of arguments
 */
void Client::run(int argc, char** argv) {
    if ((clientFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Creation socket failed...\n";
        exit(EXIT_FAILURE);
    }

    if (connect(clientFileDescriptor, (struct sockaddr *) &address, sizeof(address)) < 0) {
        std::cout << "Connection failed...\n";
        exit(EXIT_FAILURE);
    }

    ClientController clientController(url, port);


    std::memset(message, '\0', 1024);

    if (argc == 6) {
        std::strcpy(message, clientController.buildRequest("").c_str());
    } else if (argc == 8) {
        std::strcpy(message, clientController.buildRequest(argv[6], argv[7]).c_str());
    } else if (argc == 9) {
        std::strcpy(message, clientController.buildRequest(argv[6], argv[7], argv[8]).c_str());
    } else if (argc == 10) {
        std::strcpy(message, clientController.buildRequest(argv[6], argv[7], argv[8], argv[9]).c_str());
    }

    int i = 0;

    i = write(clientFileDescriptor, message, 1024);
    if (i == -1) {
        std::cout << "Writing failed...";
    }

    i = read(clientFileDescriptor, message, 1024);
    if (i == -1) {
        std::cout << "Reading failed...\n";
    }

    std::istringstream responseStream(message);
    std::string line;

    std::cerr << "===HEADERS===" << std::endl;

    while (std::getline(responseStream, line)) {
        if (line.empty()){
            break;
        }
        std::cerr << line << std::endl;
    }

    std::cout << "===BODY===" << std::endl;

    while (std::getline(responseStream, line)) {
        if (line.empty()) {
            continue;
        }
        std::cout << line << std::endl;
    }

    close(clientFileDescriptor);
}

void Client::setPort(int port) {
    Client::port = port;
}
void Client::setUrl(const std::string &url) {
    Client::url = url;
}

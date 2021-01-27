/**
------------------------
 * Created by Maroš Orsák
 * Date - 02/10/2019
 * Time - 22:46
 * File - Server.cpp
-------------------------
**/

#include "Server.h"

/**
 * Constructor for the server
 * @param url hostname of the server
 * @param port port of the server
 * @param serverListeningFileDescriptor file descriptor
 * @param address concrete address of the server
 */
Server::Server(std::string url, int port, int serverListeningFileDescriptor, struct sockaddr_in address) {
    this->url = url;
    this->port = port;
    this->serverListeningFileDescriptor = serverListeningFileDescriptor;
    this->address = address;
}

/**
 * Empty Constructor for the server
 */
Server::Server() {
   std::cout << " ______   ______    ______          ______   ________  _______   __     __  ________  _______          ______  ________   ______   _______  ________  ________  _______  \n"
                "|      \\ /      \\  /      \\        /      \\ |        \\|       \\ |  \\   |  \\|        \\|       \\        /      \\|        \\ /      \\ |       \\|        \\|        \\|       \\ \n"
                " \\$$$$$$|  $$$$$$\\|  $$$$$$\\      |  $$$$$$\\| $$$$$$$$| $$$$$$$\\| $$   | $$| $$$$$$$$| $$$$$$$\\      |  $$$$$$\\\\$$$$$$$$|  $$$$$$\\| $$$$$$$\\\\$$$$$$$$| $$$$$$$$| $$$$$$$\\\n"
                "  | $$  | $$___\\$$| $$__| $$      | $$___\\$$| $$__    | $$__| $$| $$   | $$| $$__    | $$__| $$      | $$___\\$$  | $$   | $$__| $$| $$__| $$  | $$   | $$__    | $$  | $$\n"
                "  | $$   \\$$    \\ | $$    $$       \\$$    \\ | $$  \\   | $$    $$ \\$$\\ /  $$| $$  \\   | $$    $$       \\$$    \\   | $$   | $$    $$| $$    $$  | $$   | $$  \\   | $$  | $$\n"
                "  | $$   _\\$$$$$$\\| $$$$$$$$       _\\$$$$$$\\| $$$$$   | $$$$$$$\\  \\$$\\  $$ | $$$$$   | $$$$$$$\\       _\\$$$$$$\\  | $$   | $$$$$$$$| $$$$$$$\\  | $$   | $$$$$   | $$  | $$\n"
                " _| $$_ |  \\__| $$| $$  | $$      |  \\__| $$| $$_____ | $$  | $$   \\$$ $$  | $$_____ | $$  | $$      |  \\__| $$  | $$   | $$  | $$| $$  | $$  | $$   | $$_____ | $$__/ $$\n"
                "|   $$ \\ \\$$    $$| $$  | $$       \\$$    $$| $$     \\| $$  | $$    \\$$$   | $$     \\| $$  | $$       \\$$    $$  | $$   | $$  | $$| $$  | $$  | $$   | $$     \\| $$    $$\n"
                " \\$$$$$$  \\$$$$$$  \\$$   \\$$        \\$$$$$$  \\$$$$$$$$ \\$$   \\$$     \\$     \\$$$$$$$$ \\$$   \\$$        \\$$$$$$    \\$$    \\$$   \\$$ \\$$   \\$$   \\$$    \\$$$$$$$$ \\$$$$$$$ \n";
}

/**
 * Destructor for the server
 */
Server::~Server() {}

/**
 * Method which initialize basic fields
 */
void Server::preRun() {
    memset(&address, '\0', sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
}

/**
 * Method which is root of the project. Taking care of creating communication and waiting for the clients.
 */
void Server::run() {
    createSocket();
    bindSocket();
    prepareQueueForClients();

    addressLength = sizeof(clientAddress);

    Boards boards((std::vector<Board>()));
    Controller controller(boards);
    while (true) {

        acceptClient();

        int messageLength = 0;

        if ((messageLength = read(connectedFileDescriptor, message, 1024)) > 0) {}

        std::string requestMessage(message);

        std::istringstream messageStream(requestMessage);
        std::string line;

        do {
            std::getline(messageStream, line);
            if(strstr(line.data(), "HTTP/1.1")){
                header.insert(std::pair<std::string, std::string>("endpoint", line.data()));
                continue;
            }

            std::size_t indexOfFirstDelimiter = line.find(':');

            if (indexOfFirstDelimiter > 1000) {
                break;
            }

            std::string firstItem = line.substr(0, indexOfFirstDelimiter);
            std::string secondItem = line.substr(indexOfFirstDelimiter + 2, line.length());

            header.insert(std::pair<std::string, std::string>(firstItem, secondItem));
        } while (!line.empty());

        std::string body;
        std::getline(messageStream, body);

        int recvBytes = 0;

        controller.setMethodHeadersEndpoint(header, body);

        memset(message, '\0', 1024);

        strcpy(message, controller.executeMethod().data());

        std::cout << "Returning to client:\n" << message << std::endl;

        recvBytes = write(connectedFileDescriptor, message, 1024);
        if (recvBytes != 1024) {
            std::cout << "Initial writing failed..." << std::endl;
        }

        memset(message, '\0', 1024);
        header.clear();

        close(connectedFileDescriptor);
    }
}

void Server::createSocket() {
    serverListeningFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (serverListeningFileDescriptor == 0) {
        std::cout << "Creation socket failed...\n";
        exit(EXIT_FAILURE);
    }
}

/**
 * Method, which taking care of binding socket
 */
void Server::bindSocket() {
    if (bind(serverListeningFileDescriptor, (struct sockaddr*) &address, sizeof(address)) < 0){
        std::cout << "Binding socket failed...\n";
        exit(EXIT_FAILURE);

    }
}

/**
 * Method, which taking care of creating queue for the clients
 */
void Server::prepareQueueForClients() {
    if (listen(serverListeningFileDescriptor, 1) < 0) {
        std::cout << "Listening socket failed...\n";
        exit(EXIT_FAILURE);
    };
}

/**
 * Method, which taking care of accepting connection of clients
 */
void Server::acceptClient() {
    connectedFileDescriptor = accept(serverListeningFileDescriptor, (struct sockaddr *) &clientAddress, (socklen_t*) &addressLength);

    if (connectedFileDescriptor == -1) {
        std::cout << "Accepting new connection failed...\n";
        exit(EXIT_FAILURE);
    }
}

void Server::setPort(int port) {
    Server::port = port;
}
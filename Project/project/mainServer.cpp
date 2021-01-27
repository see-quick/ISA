/**
------------------------
 * Created by Maroš Orsák
 * Date - 02/10/2019
 * Time - 22:54
 * File - mainServer.cpp
-------------------------
**/

#include "server/Server.h"
#include "ParseArgs.h"
/**
 * Main method for executing server side application
 */
int main(int argc, char** argv) {
    ParseArgs parseArgs = ParseArgs();

    parseArgs.parseServerArgs(argc, argv);

    Server server = Server();

    server.setPort(parseArgs.getServerPort());
    server.preRun();
    server.run();

    return 0;
}
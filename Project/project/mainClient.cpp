#include "client/Client.h"

/**
------------------------
 * Created by Maroš Orsák
 * Date - 03/10/2019
 * Time - 23:05
 * File - mainClient.cpp
-------------------------
**/

#include "client/Client.h"
#include "ParseArgs.h"

/**
 * Main method for executing client side application
 */
int main(int argc, char** argv) {
    ParseArgs parseArgs = ParseArgs();

    parseArgs.parseClientArgs(argc, argv);

    Client client = Client();

    client.setUrl(parseArgs.getServerHost());
    client.setPort(parseArgs.getServerPort());

    client.preRun();
    client.run(argc, argv);
}
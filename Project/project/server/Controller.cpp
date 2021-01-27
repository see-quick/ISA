/**
------------------------
 * Created by Maroš Orsák
 * Date - 09/10/2019
 * Time - 21:11
 * File - Controller.cpp
-------------------------
**/

#include "Controller.h"

/***
 * Contructor for the controller
 * @param boards all boards
 */
Controller::Controller(Boards boards) {
    this->boards = boards;
}

/***
 * Destructor for the controller
 */
Controller::~Controller() {}

/**
 * Method, which sets http headers to the map, parse first line and sets
 *  method
 *  endpoint
 *  httpVersion
 * @param httpHeaders http headers
 * @param body http body
 */
void Controller::setMethodHeadersEndpoint(std::map<std::string, std::string> httpHeaders, std::string body) {
    this->headers = httpHeaders;
    std::string firstLine = this->headers.find("endpoint")->second;

    this->method = firstLine.substr(0, firstLine.find(' '));
    firstLine = firstLine.substr(firstLine.find(' ') + 1, firstLine.length());
    this->endpoint = firstLine.substr(0, firstLine.find(' '));
    firstLine = firstLine.substr(firstLine.find(' ') + 1, firstLine.length());
    this->httpVersion = firstLine.substr(0, firstLine.find(' '));
    this->body = body;
}

std::string Controller::getNameBoardFromEndpoint() {
    if (endpoint.find("/board/") == 0) {
        nameOfTheBoard = endpoint.substr(endpoint.find("/") + 7, endpoint.length() - 1);    // because of /board/ (need move offset +7 to get name)
    } else {
        nameOfTheBoard = endpoint.substr(endpoint.find("/") + 8, endpoint.length() - 1);   // because of /boards/ (need move offset +8 to get name)
    }
    return nameOfTheBoard;
}

/***
 * Get concrete order from the endpoints
 * for DELETE and PUT methods /board/name/id...
 * @return order/id number
 */
std::string Controller::getOrderOfCommend() {
    if (endpoint.find("/board/") == 0) {
        orderOfCommend = endpoint.substr(1, endpoint.length());
        orderOfCommend = orderOfCommend.substr(orderOfCommend.find("/") + 1, endpoint.length());
        orderOfCommend = orderOfCommend.substr(orderOfCommend.find("/") + 1, endpoint.length());
        return orderOfCommend;
    }
}

/***
 * Get concrete name of the board from the endpoints
 * @return name of the board
 */
std::string Controller::getNameOfTheBoard() {
    if (endpoint.find("/board/") == 0) {
        nameOfTheBoard = endpoint.substr(1, endpoint.length());
        nameOfTheBoard = nameOfTheBoard.substr(nameOfTheBoard.find("/") + 1, endpoint.length());
        nameOfTheBoard = nameOfTheBoard.substr(0, nameOfTheBoard.find("/"));
        return nameOfTheBoard;
    }
}

/**
 * Method, which handling and deciding which response will be building
 * @return response for the client
 */
std::string Controller::executeMethod() {
std::cout << "This is endpoint:" << endpoint << std::endl;
    if (method == "GET") {
        return Controller::handleGet();
    } else if (method == "POST") {
        return Controller::handlePost();
    } else if (method == "DELETE") {
        return Controller::handleDelete();
    } else if (method == "PUT") {
        return Controller::handlePut();
    } else {
        std::cout << "ERROR: Not known method:" << method << std::endl;
    }
}

/**
 * Method, which will take care of endpoints
 *  GET /boards         - Vráti zoznam dostupných nástenok, jedna na riadok.
 *  GET /board/name    - Zobrazí obsah nástenky name.
 * @return
 *  200 - OK
 *  404 - DOESN'T EXIST
 */
std::string Controller::handleGet() {
    if(endpoint == "/boards") {
        std::cout << "Boards size is--->:" << boards.getBoards().size() << std::endl;

        std::string responseBody;
        int contentLength = 0;

        responseBody = "[--Boards--]\n";

        contentLength = responseBody.length();

        for (auto const& board : boards.getBoards()) {
            std::cout << "Adding to the response -> " << board.getName() << std::endl;
            responseBody += board.getName() + "\n";
            contentLength += responseBody.length();
        }

        std::string response = "HTTP/1.1 200 OK\r\n"
                      "Server: C++ HTTP server |XORSAK02|\r\n"
                      "Content-type: text/plain\r\n"
                      "Content-length: " + std::to_string(contentLength) + "\r\n"
                      "\n"
                      "";

        response.append(responseBody);

        std::cout << "Returning body:\n" << response  << std::endl;
        return response;

   } else if (endpoint.find("/board/") == 0){
        std::string response;

        if (!boards.hasBoard(getNameBoardFromEndpoint())) {
            std::cout << "INFO: " << getNameBoardFromEndpoint() << " NOT FOUND ==================" << std::endl;
            response =
                    "HTTP/1.1 404 Not found\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        std::string responseBody;

        responseBody.append("[" + boards.getBoard(getNameBoardFromEndpoint()).getName() + "]\n");

        Board board = boards.getBoard(getNameBoardFromEndpoint());

        for (auto const& commend : board.getCommends()) {
            std::cout << std::to_string(commend.getOrder()) << "." << commend.getMessage() << std::endl;
            responseBody.append(std::to_string(commend.getOrder()) + ".");

            std::string::size_type i;

            for(i = 0; i < commend.getMessage().size() - 1; ++i) {
                if (commend.getMessage()[i] == '\\' && commend.getMessage()[i + 1] == 'n') {
                    responseBody.append("\n");
                    continue;
                }
                responseBody += commend.getMessage()[i];
            }

            responseBody += commend.getMessage()[i];
            responseBody += "\n";

        }

        int contentLength = responseBody.length();

        response =
                "HTTP/1.1 200 OK\r\n"
                "Server: C++ HTTP server |XORSAK02|\r\n"
                "Content-type: text/plain\r\n"
                "Content-length: " + std::to_string(contentLength) + "\r\n"
                "\n"
                "";

        response.append(responseBody);

        return response;
    } else {
        // in term of endpoints like /boards/qweqeqqw, /boards/ww etc.
        return
            "HTTP/1.1 404 Not found\r\n"
            "Server: C++ HTTP server |XORSAK02|\r\n"
            "Content-type: text/plain\r\n"
            "Content-length: 0\r\n"
            "\n"
            "";
    }
}

/**
 * Method, which will take care of endpoints
 *  POST /boards/name - Vytvorí novú prázdnu nástenku s názvom name.
 *  POST /board/name  - Vloží nový príspevok do nástenky name. Príspevok je vložený na koniec
 * @return
 *  201 - CREATED
 *  400 - if content-length = 0
 *  409 - ALREADY EXISTS
 *  else
 *  404
 */
std::string Controller::handlePost() {
    std::cout << "POST METHOD" << std::endl;

    if(endpoint.find("/boards/") == 0) {
        std::string response;

        // POST /boards/
        if (getNameBoardFromEndpoint().empty()) {
            response =
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        std::regex boardName( "\\b^[a-zA-Z0-9]*$\\b");
        if (!(std::regex_match(getNameBoardFromEndpoint(), boardName))) {
            std::cout << "ERROR: Wrong name of board should contains only [a-zA-Z0-9]" << std::endl;
            response =
                    "HTTP/1.1 404 Not found\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;

        }

        if (boards.hasBoard(getNameBoardFromEndpoint())) {
            std::cout << "INFO: " << getNameBoardFromEndpoint() << " EXISTS ==================" << std::endl;
            response =
                    "HTTP/1.1 409 Conflict\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        std::cout << "Boards count..." << boards.getCountBoards() << std::endl;

        boards.createBoardWithEmptyCommend(getNameBoardFromEndpoint());     // here is input name of the board

        return "HTTP/1.1 201 Created\r\n"
               "Location: http://127.0.0.1:12000/boards/name"
               "Server: C++ HTTP server |XORSAK02|\r\n"
               "Content-type: text/plain;charset=UTF-8\r\n"
               "Content-length: 0\r\n"
               "Cache-Control: no-cache\r\n"
               "\n"
               "";
    } else if (endpoint.find("/board/") == 0) {
        std::string response;

        // POST /board/
        if (getNameBoardFromEndpoint().empty() || body.empty()) {
            response =
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        if (!boards.hasBoard(getNameBoardFromEndpoint())) {
            std::cout << "INFO: " << getNameBoardFromEndpoint() << "  NOT FOUND ==================" << std::endl;
            response =
                    "HTTP/1.1 404 Not found\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        std::string responseBody;

        Board board = boards.getBoard(getNameBoardFromEndpoint());

        board.addCommend(body, board.getCommends().size() + 1);

        boards.getBoard(getNameBoardFromEndpoint()).setCommends(board.getCommends());

        for (auto const& commend :  board.getCommends()) {
            std::cout << std::to_string(commend.getOrder()) << "." << commend.getMessage() << std::endl;
            responseBody.append(std::to_string(commend.getOrder()) + ".");

            std::string::size_type i;

            for(i = 0; i < commend.getMessage().size() - 1; ++i) {
                if (commend.getMessage()[i] == '\\' && commend.getMessage()[i + 1] == 'n') {
                    responseBody.append("\n");
                    continue;
                }
                 responseBody += commend.getMessage()[i];
              }

            responseBody += commend.getMessage()[i];
            responseBody += "\n";
        }

        int contentLength = responseBody.length();

        response =  "HTTP/1.1 201 Created\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: " + std::to_string(contentLength) + "\r\n"
                    "\n"
                    "";

        response.append(responseBody);

        return response;
    } else {
        // in term of endpoints like /boards/qweqeqqw, /boards/ww etc.
        return
            "HTTP/1.1 404 Not found\r\n"
            "Server: C++ HTTP server |XORSAK02|\r\n"
            "Content-type: text/plain\r\n"
            "Content-length: 0\r\n"
            "\n"
            "";
    }
}

/**
 * Method, which will take care of endpoints
 *  DELETE /boards/name     - Zmaže nástenku name a všetok jej obsah.
 *  DELETE /board/name/id   - Zmaže príspevok číslo id z nástenky name.
 * @return
 *  200 - OK
 *  404 - DOESN'T EXIST
 */
std::string Controller::handleDelete() {
    std::string response;

    if(endpoint.find("/boards/") == 0) {

        if (!boards.hasBoard(getNameBoardFromEndpoint())) {
            std::cout << "INFO: " << getNameBoardFromEndpoint() << "  NOT FOUND ==================" << std::endl;
            response =
                    "HTTP/1.1 404 Not found\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        boards.deleteBoard(getNameBoardFromEndpoint());

        return "HTTP/1.1 200 OK\r\n"
               "Server: C++ HTTP server |XORSAK02|\r\n"
               "Content-type: text/plain\r\n"
               "Content-length: 0\r\n"
               "\n"
               "";

    } else if (endpoint.find("/board/") == 0) {
        if (!boards.hasBoard(getNameOfTheBoard())) {
            std::cout << "INFO: " << getNameBoardFromEndpoint() << " Border NOT FOUND ==================" << std::endl;
            response =
                    "HTTP/1.1 404 Not found\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        // if orderOfTheCommend is greater then we have commends that means it doesn't exists
        if (std::stoi(getOrderOfCommend()) > boards.getBoard(getNameOfTheBoard()).getCommends().size()) {
            std::cout << "INFO: " << getNameBoardFromEndpoint() << " COMMEND ID/Order NOT FOUND ==================" << std::endl;
            response =
                    "HTTP/1.1 404 Not found\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        boards.getBoard(getNameOfTheBoard()).deleteCommend(std::stoi(getOrderOfCommend()));

        std::vector<Commend> unorderedCommends = boards.getBoard(getNameOfTheBoard()).getCommends();

        boards.getBoard(getNameOfTheBoard()).setCommends(boards.getBoard(getNameOfTheBoard()).reorderCommends(unorderedCommends));

        return "HTTP/1.1 200 OK\r\n"
               "Server: C++ HTTP server |XORSAK02|\r\n"
               "Content-type: text/plain\r\n"
               "Content-length: 0\r\n"
               "\n"
               "";
    } else {
        // in term of endpoints like /boards/qweqeqqw, /boards/ww etc.
        return
                "HTTP/1.1 404 Not found\r\n"
                "Server: C++ HTTP server |XORSAK02|\r\n"
                "Content-type: text/plain\r\n"
                "Content-length: 0\r\n"
                "\n"
                "";
    }
}

/**
 * Method, which will take care of endpoints
 *  PUT /board/name/id      -    Zmení obsah príspevku číslo id v nástenke name.
 * @return
 *  200 - OK
 *  404 - DOESN'T EXIST
 */
std::string Controller::handlePut() {
    std::string response;

    if(endpoint.find("/board/") == 0) {

        // PUT /board/
        if (getNameBoardFromEndpoint().empty() || body.empty()) {
            response =
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        if (!boards.hasBoard(getNameOfTheBoard())) {
            std::cout << "INFO: " << getNameBoardFromEndpoint() << " Border NOT FOUND ==================" << std::endl;
            response =
                    "HTTP/1.1 404 Not found\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        // if orderOfTheCommend is greater then we have commends that means it doesn't exists
        if (std::stoi(getOrderOfCommend()) > boards.getBoard(getNameOfTheBoard()).getCommends().size()) {
            response =
                    "HTTP/1.1 404 Not found\r\n"
                    "Server: C++ HTTP server |XORSAK02|\r\n"
                    "Content-type: text/plain\r\n"
                    "Content-length: 0\r\n"
                    "\n"
                    "";
            return response;
        }

        std::vector<Commend> updatedCommends = boards.getBoard(getNameOfTheBoard()).editCommend(std::stoi(getOrderOfCommend()), body);
        boards.getBoard(getNameOfTheBoard()).setCommends(updatedCommends);

        return "HTTP/1.1 200 OK\r\n"
               "Server: C++ HTTP server |XORSAK02|\r\n"
               "Content-type: text/plain\r\n"
               "Content-length: 0\r\n"
               "\n"
               "";
    } else {
        // in term of endpoints like /boards/qweqeqqw, /boards/ww etc.
        return
                "HTTP/1.1 404 Not found\r\n"
                "Server: C++ HTTP server |XORSAK02|\r\n"
                "Content-type: text/plain\r\n"
                "Content-length: 0\r\n"
                "\n"
                "";
    }
}

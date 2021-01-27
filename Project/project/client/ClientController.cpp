/**
------------------------
 * Created by Maroš Orsák
 * Date - 13/10/2019
 * Time - 20:39
 * File - ClientController.cpp
-------------------------
**/

#include "ClientController.h"

/**
 * Contructor of the Client Controller
 * @param url or hostname where client will be connecting
 * @param port port where client will be connecting
 */
ClientController::ClientController(std::string url, int port) {
    this->url = url;
    this->port = port;
}

/**
 * Destructor of the ClientController
 */
ClientController::~ClientController() {}

/**
 * Method which building request for the server
 * @details using overload principle of OOP
 * @param method this method can be GET, PUT, POST, DELETE
 */
std::string ClientController::buildRequest(std::string method) {
    return buildRequest(method, "", "");
}

/**
 * Method which building request for the server
 * @details using overload principle of OOP
 * @param method this method can be GET, PUT, POST, DELETE
 */
std::string ClientController::buildRequest(std::string method, std::string nameOfTheBoard) {
    return buildRequest(method, nameOfTheBoard, "");
}

/**
 * Method which building request for the server
 * @details using overload principle of OOP
 * @param method this method can be GET, PUT, POST, DELETE
 */
std::string ClientController::buildRequest(std::string method, std::string nameOfTheBoard, std::string content) {
    return buildRequest(method, nameOfTheBoard, "", content);
}

/**
 * Method which building request for the server
 * @details using overload principle of OOP
 * @param method this method can be GET, PUT, POST, DELETE
 */
std::string ClientController::buildRequest(std::string method, std::string nameOfTheBoard, std::string id, std::string content) {
    this->method = method;
    this->nameOfTheBoard = nameOfTheBoard;
    this->id = id;
    this->content = content;

    if (method == "add") {
        return buildPost();
    } else if (method == "delete") {
        return buildDelete();
    } else if (method == "update") {
        return buildPut();
    } else if (method == "list" || method.empty()) {
        return buildGet();
    }
}

/**
 * Method which building request for the server GET
 */
std::string ClientController::buildGet() {
    if (method.empty()) {
        return
                "GET /boards HTTP/1.1\r\n"
                "Host: " + url + ":" + std::to_string(port) + "\r\n"
                "User-Agent: ISA client\r\n"
                "Accept: */*\r\n"
                "\n"
                "";

    } else if (method == "list") {
        return
                "GET /board/" + nameOfTheBoard + " HTTP/1.1\r\n"
                "Host: " + url + ":" + std::to_string(port) + "\r\n"
                "User-Agent: ISA client\r\n"
                "Accept: */*\r\n"
                "\n"
                 "";
    }

}

/**
 * Method which building request for the server POST
 */
std::string ClientController::buildPost() {
    if (content.empty()) {
        return
            "POST /boards/" + nameOfTheBoard + " HTTP/1.1\r\n"
            "Host: " + url + ":" + std::to_string(port) + "\r\n"
            "User-Agent: ISA client\r\n"
            "Accept: */*\r\n"
            "\n"
            "";
    }

    return
        "POST /board/" + nameOfTheBoard + " HTTP/1.1\r\n"
        "Host: " + url + ":" + std::to_string(port) + "\r\n"
        "User-Agent: ISA client\r\n"
        "Accept: */*\r\n"
        "Content-Length:" + std::to_string(content.length()) + "\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "\n"
        "" + content;
}

/**
 * Method which building request for the server PUT
 */
std::string ClientController::buildPut() {
    if (method == "update") {
        return
            "PUT /board/" + nameOfTheBoard + "/" + id + " HTTP/1.1\r\n"
            "Host: " + url + ":" + std::to_string(port) + "\r\n"
            "User-Agent: ISA client\r\n"
            "Accept: */*\r\n"
            "Content-Length:" + std::to_string(content.length()) + "\r\n"
            "Content-Type: application/x-www-form-urlencoded\r\n"
            "\n"
            "" + content;
    }
}

/**
 * Method which building request for the server DELETE
 */
std::string ClientController::buildDelete() {
    if (content.empty()) {
        return
            "DELETE /boards/" + nameOfTheBoard + " HTTP/1.1\r\n"
            "Host: " + url + ":" + std::to_string(port) + "\r\n"
            "User-Agent: ISA client\r\n"
            "Accept: */*\r\n"
            "\n"
            "";
    }

    return
            "DELETE /board/" + nameOfTheBoard + "/" + content + " HTTP/1.1\r\n"
            "Host: " + url + ":" + std::to_string(port) + "\r\n"
            "User-Agent: ISA client\r\n"
            "Accept: */*\r\n"
            "\n"
            "";
}
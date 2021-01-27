/**
------------------------
 * Created by Maroš Orsák
 * Date - 10/10/2019
 * Time - 22:43
 * File - Commend.cpp
-------------------------
**/

#include "Commend.h"

/***
 * Contructor for the commend
 * @param message concrete message
 * @param order order count/id
 */
Commend::Commend(const std::string message, const int order) {
    this->order = order;
    this->message = message;
}

/***
 * Destructor for the commend
 */
Commend::~Commend() {}


int Commend::getOrder() const {
    return order;
}

void Commend::setOrder(int order) {
    Commend::order = order;
}

std::string Commend::getMessage() const {
    return message;
}

void Commend::setMessage(std::string message) {
    Commend::message = message;
}



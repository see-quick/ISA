/**
------------------------
 * Created by Maroš Orsák
 * Date - 10/10/2019
 * Time - 22:42
 * File - Board.cpp
-------------------------
**/

#include "Board.h"

/***
 * Contructor for the Board
 * @param name name of the board
 */
Board::Board(const std::string &name) {
    this->name = name;
    this->commends = commends;
}

/***
 * Destructor for the Board
 */
Board::~Board() {}

/***
 * Adding commend to the instance of the board
 * @param message concrete message
 * @param orderCount id/orderCount of commend
 */
void Board::addCommend(std::string message, int orderCount) {
    Commend commend(message, orderCount);
    commends.push_back(commend);
}

/***
 * Deletes specific commend
 * @param orderCount id/orderCount of commend
 */
void Board::deleteCommend(int orderCount) {
    commends.erase(commends.begin() + orderCount - 1);       // delete xTh element returned by getIndexOfBoard...
}

/***
 * Reorder commends from 1 to commend.size()
 * @param commends vector of all commends
 * @return reordered vector of commends
 */
std::vector<Commend> Board::reorderCommends(std::vector<Commend> commends) {
    int order = 1;
    for(auto& commend: commends) {
        commend.setOrder(order);
        order++;
    }
    return commends;
}

/***
 * Edit concrete commend inside board
 * @param orderCount id/orderCount of commend
 * @param updateMessage new message to update previous one
 * @return new vector of commends
 */
std::vector<Commend> Board::editCommend(int orderCount, std::string updateMessage) {
    if (orderCount > 0) {
        int index = 1;
        for(auto& commend: commends) {
            if (index == orderCount) {
                commend.setMessage(updateMessage);
            }
            index++;
        }
        return commends;
    }
}

const std::string &Board::getName() const {
    return name;
}


const std::vector<Commend> &Board::getCommends() const {
    return commends;
}

void Board::setCommends(const std::vector<Commend> &commends) {
    Board::commends = commends;
}
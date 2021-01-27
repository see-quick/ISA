/**
------------------------
 * Created by Maroš Orsák
 * Date - 10/10/2019
 * Time - 22:41
 * File - Boards.cpp
-------------------------
**/

#include "Boards.h"

/***
 * Contructor of the Boards
 * @param boards vector of boards
 */
Boards::Boards(std::vector<Board> boards) {
    this->vectorBoards = boards;
}

/***
 * Empty constructor for Boards
 */
Boards::Boards() {}

/***
 * Desctructor of the Boards
 */
Boards::~Boards() {}

/***
 * Method, which creates empty commend inside board and push it to vector of boards
 * @param name name of the board
 */
void Boards::createBoardWithEmptyCommend(std::string name)  {
    Board newBoard(name);
    vectorBoards.push_back(newBoard);
}

/***
 * Method, which get concrete board from vector of boards
 * @param name name of the board
 */
Board &Boards::getBoard(std::string name) {
    for (auto& board : vectorBoards) {
        if (board.getName() == name) {
            return board;
        }
    }
}

/***
 * Method, which get verifies that board is actually present inside vector of boards
 * @param name name of the board
 */
bool Boards::hasBoard(std::string name) {
    for (auto const& board : vectorBoards) {
        if (board.getName() == name) {
            return true;
        }
    }
    return false;
}

/***
 * Gets index of the concrete board
 * @param name name of the board
 * @return index of the board
 */
int Boards::getIndexOfBoard(std::string name) {
    int index = 0;
    for (auto i = vectorBoards.begin(); i < vectorBoards.end() ; ++i) {
        if (i.base()->getName() == name) {
            return index;
        }
        index++;
    }
}

/***
 * Delete concrete board from vector of the boards
 * @param name name of the board
 */
void Boards::deleteBoard(std::string name) {
    vectorBoards.erase(vectorBoards.begin() + getIndexOfBoard(name));       // delete xTh element returned by getIndexOfBoard...
}

/***
 * Method, which returning size of boards
 * @return count of boards
 */
int Boards::getCountBoards() {
    return vectorBoards.size();
}

/***
 * Method, which returns vector of boards
 * @return vector of boards
 */
std::vector<Board> Boards::getBoards() {
    return vectorBoards;
}


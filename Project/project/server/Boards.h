/**
------------------------
 * Created by Maroš Orsák
 * Date - 10/10/2019
 * Time - 22:41
 * File - Boards.h
-------------------------
**/

#ifndef ISA_BOARDS_H
#define ISA_BOARDS_H


#include <string>
#include <vector>
#include "Board.h"

class Boards {
private:
    std::vector<Board> vectorBoards;
public:
    std::vector<Board> getBoards();

    int getCountBoards();
    void deleteBoard(std::string name);
    int getIndexOfBoard(std::string name);
    void createBoardWithEmptyCommend(std::string name);
    Board &getBoard(std::string name);
    bool hasBoard(std::string name);

    Boards(std::vector<Board> boards);
    Boards();
    ~Boards();
};



#endif //ISA_BOARDS_H

/**
------------------------
 * Created by Maroš Orsák
 * Date - 10/10/2019
 * Time - 22:42
 * File - Board.h
-------------------------
**/

#ifndef ISA_BOARD_H
#define ISA_BOARD_H


#include <string>
#include <vector>
#include "Commend.h"

class Board {
private:
    std::string name;
    std::vector<Commend> commends;
public:
    const std::string &getName() const;
    const std::vector<Commend> &getCommends() const;
    void setCommends(const std::vector<Commend> &commends);

    void addCommend(std::string message, int orderCount);
    void deleteCommend(int orderCount);
    std::vector<Commend> editCommend(int orderCount, std::string updateMessage);
    std::vector<Commend> reorderCommends(std::vector<Commend> commends);


    Board(const std::string &name);
    Board();

    ~Board();
};


#endif //ISA_BOARD_H

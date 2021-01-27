/**
------------------------
 * Created by Maroš Orsák
 * Date - 10/10/2019
 * Time - 22:43
 * File - Commend.h
-------------------------
**/

#ifndef ISA_COMMEND_H
#define ISA_COMMEND_H


#include <string>

class Commend {
private:
    int order;
    std::string message;
public:
    int getOrder() const;
    std::string getMessage() const;
    void setMessage(std::string message);
    void setOrder(int order);

    Commend(const std::string message, const int order);
    ~Commend();
};


#endif //ISA_COMMEND_H

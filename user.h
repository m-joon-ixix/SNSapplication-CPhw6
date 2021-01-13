#ifndef PROBLEM2_USER_H
#define PROBLEM2_USER_H

#include <string>

class User{
    std::string password;
public:
    std::string id;
    User(std::string id, std::string password);
};

#endif //PROBLEM2_USER_H

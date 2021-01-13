#ifndef PROBLEM2_FRONTEND_H
#define PROBLEM2_FRONTEND_H

#include "backend.h"
#include "user.h"

class FrontEnd{
    BackEnd* backEnd;
    User* user;
public:
    FrontEnd(BackEnd* backEnd);
    bool auth(std::string authInfo);
    void post(std::pair<std::string, std::string> titleContentPair);
    std::vector<Post*> recommend();
    std::vector<Post*> search(std::string command);
    User* getUser();
};

#endif //PROBLEM2_FRONTEND_H

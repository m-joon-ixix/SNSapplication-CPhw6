#ifndef PROBLEM2_USER_INTERFACE_H
#define PROBLEM2_USER_INTERFACE_H

#include "frontend.h"
#include "view.h"

class UserInterface{
    FrontEnd* frontEnd;
    bool query(std::string command);
    static std::string parseInstruction(std::string command);
    void post();
    void search(std::string command);
    void recommend();
public:
    UserInterface(std::istream& is, std::ostream& os);
    std::istream& is;
    std::ostream& os;
    PostView* postView;
    AuthView* authView;
    View* mainView;
    void createUI(FrontEnd* frontEnd);
    void run(std::istream& is, std::ostream& os);
};


#endif //PROBLEM2_USER_INTERFACE_H

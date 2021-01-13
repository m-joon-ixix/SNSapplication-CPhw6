#ifndef PROBLEM2_VIEW_H
#define PROBLEM2_VIEW_H

#include <iostream>
#include <fstream>

class View{
public:
    std::istream& is;
    std::ostream& os;
    bool isTest;
    View(std::istream& is, std::ostream& os);
    // View(std::string input, std::ostream& os);
    virtual std::string getUserInput(std::string prompt);
    // std::string getOutput(); -> no need to implement
};

class AuthView : public View{
public:
    AuthView(std::istream& is, std::ostream& os);
    // AuthView(std::string input, std::ostream& os);
    std::string getUserInput(std::string prompt) override;
};

class PostView : public View{
public:
    PostView(std::istream& is, std::ostream& os);
    // PostView(std::string input, std::ostream& os);
    std::pair<std::string, std::string> getPost(std::string prompt);
};

#endif //PROBLEM2_VIEW_H

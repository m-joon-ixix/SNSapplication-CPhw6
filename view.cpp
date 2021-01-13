#include "view.h"

View::View(std::istream &is, std::ostream &os): is(is), os(os), isTest(false) { }

AuthView::AuthView(std::istream &is, std::ostream &os): View(is, os) { }

PostView::PostView(std::istream &is, std::ostream &os): View(is, os) { }

std::string View::getUserInput(std::string prompt){
    os << prompt;
    std::string nextLine;
    std::getline(is, nextLine);
    return nextLine;
}

std::string AuthView::getUserInput(std::string prompt){
    std::string id, passwd;
    os << prompt;
    os << "id=";
    std::getline(is, id);
    os << "passwd=";
    std::getline(is, passwd);
    return id + "\n" + passwd;
}

std::pair<std::string, std::string> PostView::getPost(std::string prompt){
    std::string title, content, entireContent = "";
    os << "-----------------------------------\n";
    os << prompt << "\n";
    os << "* Title=";
    std::getline(is, title);
    os << "* Content\n";
    os << ">";
    std::getline(is, content);
    entireContent += (content + "\n");
    while(!content.empty()){
        os << ">";
        std::getline(is, content);
        entireContent += (content + "\n");
    }
    // os << "-----------------------------------\n";
    return std::pair<std::string, std::string>(title, entireContent);
}

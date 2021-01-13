#include "user_interface.h"
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> str_split_UI(std::string s, char delimiter){
    std::vector<std::string> words;
    std::string word;
    std::stringstream ss(s);
    while(std::getline(ss, word, delimiter)){
        words.push_back(word);
    }
    return words;
}

UserInterface::UserInterface(std::istream &is, std::ostream &os): is(is), os(os) { }

std::string UserInterface::parseInstruction(std::string command){
    std::vector<std::string> words = str_split_UI(command, ' ');
    if(!words.empty()) return words[0];
    else return "";
}

bool UserInterface::query(std::string command){
    std::string instruction = parseInstruction(command);
    if(instruction == "exit") return false;
    else if(instruction == "post") post();
    else if(instruction == "search") search(command);
    else if(instruction == "recommend") recommend();
    else os << "Illegal Command Format : " << command << std::endl;

    return true;
}

void UserInterface::post(){
    frontEnd->post(postView->getPost("New Post"));
}

void UserInterface::search(std::string command){
    std::vector<Post*> posts = frontEnd->search(command);
    os << "-----------------------------------\n";
    for(Post* post : posts){
        os << post->getSummary() << std::endl;
    }
}

void UserInterface::recommend(){
    std::vector<Post*> posts = frontEnd->recommend();
    for(Post* post : posts){
        os << post->toString() << std::endl;
    }
}

void UserInterface::createUI(FrontEnd *frontEnd){
    this->frontEnd = frontEnd;
    authView = new AuthView(is, os);
    postView = new PostView(is, os);
    mainView = authView;
}

void UserInterface::run(std::istream &is, std::ostream &os){
    std::string command;
    std::string authInfo = authView->getUserInput("------ Authentication ------\n");
    if(frontEnd->auth(authInfo)){
        mainView = postView;
        do{
            command = postView->getUserInput(
                    "-----------------------------------\n" +
                    frontEnd->getUser()->id + "@sns.com\n" +
                    "post : Post contents\n" +
                    "recommend : recommend interesting posts\n" +
                    "search <keyword> : List post entries whose contents contain <keyword>\n" +
                    "exit : Terminate this program\n" +
                    "-----------------------------------\n" +
                    "Command=");

        } while(query(command));
    } else {
        os << "Failed Authentication.\n";
    }
}
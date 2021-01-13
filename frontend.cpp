#include "frontend.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>

std::vector<std::string> str_split_FE(std::string s, char delimiter){
    std::vector<std::string> words;
    std::string word;
    std::stringstream ss(s);
    while(std::getline(ss, word, delimiter)){
        words.push_back(word);
    }
    return words;
}

FrontEnd::FrontEnd(BackEnd *backEnd): backEnd(backEnd) { }

bool FrontEnd::auth(std::string authInfo){
    std::vector<std::string> id_pw = str_split_FE(authInfo, '\n');
    if(id_pw.size() < 2) return false;
    std::string id = id_pw[0], password = id_pw[1];
    if(password == backEnd->getPassword(id)) user = new User(id, password);
    return password == backEnd->getPassword(id);
}

void FrontEnd::post(std::pair<std::string, std::string> titleContentPair){
    backEnd->writePost(user->id, titleContentPair.first, titleContentPair.second);
}

std::vector<Post*> FrontEnd::recommend(){
    return backEnd->recommendPosts(user->id);
}

std::vector<Post*> FrontEnd::search(std::string command){
    std::vector<std::string> keywords = str_split_FE(command, ' ');
    keywords.erase(keywords.begin());
    std::unordered_set<std::string> keywordSet;
    for(std::string word : keywords) keywordSet.insert(word);
    keywords.clear();
    for(std::string word : keywordSet) keywords.push_back(word);
    // unique keywords put in 'keywords'
    return backEnd->searchPosts(keywords);
}

User* FrontEnd::getUser(){
    return user;
}
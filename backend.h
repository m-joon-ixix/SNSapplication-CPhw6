#ifndef PROBLEM2_BACKEND_H
#define PROBLEM2_BACKEND_H

#include "config.h"
#include "post.h"
#include <iostream>
#include <string>
#include <vector>

class BackEnd{
public:
    static int maxPostNumber;
    BackEnd();
    std::string getPassword(std::string id);
    void writePost(std::string userId, std::string title, std::string content);
    std::vector<Post*> recommendPosts(std::string userId);
    std::vector<Post*> searchPosts(std::vector<std::string> keywords);
};

#endif //PROBLEM2_BACKEND_H

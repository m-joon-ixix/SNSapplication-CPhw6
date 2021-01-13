#include "backend.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <queue>

int BackEnd::maxPostNumber = -1;

std::vector<std::string> str_split_BE(std::string s, char delimiter){
    std::vector<std::string> words;
    std::string word;
    std::stringstream ss(s);
    while(std::getline(ss, word, delimiter)){
        words.push_back(word);
    }
    return words;
}

std::vector<std::string> str_split_whitespace(std::string s){
    std::vector<std::string> words;
    std::istringstream iss(s);
    do {
        std::string subs;
        iss >> subs;
        if(!subs.empty()) words.push_back(subs);
    } while (iss);
    return words;
}

bool comparePosts_dateTime(Post* p1, Post* p2){
    return p1->getDateTime().more_new_than(p2->getDateTime());
}

bool comparePosts_keywordCount(Post* p1, Post* p2){
    if(p1->getKeywordCount() != p2->getKeywordCount()){
        return p1->getKeywordCount() > p2->getKeywordCount();
    } else {
        return p1->getDateTime().more_new_than(p2->getDateTime());
    }
}

BackEnd::BackEnd() {
    // retrieve the maxPostNumber
    std::vector<std::string> people;
    std::string path = SERVER_STORAGE_DIR;
    for(auto& file : std::filesystem::directory_iterator(path)){
        std::vector<std::string> v1 = str_split_BE(file.path().string(), '/');
        people.push_back(v1[v1.size() - 1]);
    }

    for(std::string name : people){
        path = SERVER_STORAGE_DIR + name + "/post";
        std::string str; // temporary space for reading in strings
        for(auto& file : std::filesystem::directory_iterator(path)){
            std::vector<std::string> words = str_split_BE(file.path().string(), '\\');
            try{
                int postNum = std::stoi(str_split_BE(words[words.size() - 1], '.')[0]);
                if(maxPostNumber < postNum) maxPostNumber = postNum;
            } catch(std::exception& exception){
                exception.what();
            }
        }
    }
}

bool userExists(std::string userId){
    std::vector<std::string> people;
    std::string path = SERVER_STORAGE_DIR;
    for(auto& file : std::filesystem::directory_iterator(path)){
        std::vector<std::string> v1 = str_split_BE(file.path().string(), '/');
        people.push_back(v1[v1.size() - 1]);
    }
    bool exists = false;
    for(std::string name : people){
        if(name == userId){
            exists = true;
            break;
        }
    }
    return exists;
}

std::string BackEnd::getPassword(std::string id){
    if(!userExists(id)) return "";
    std::string password;
    std::ifstream pw_txt(SERVER_STORAGE_DIR + id + "/password.txt");
    std::getline(pw_txt, password);
    pw_txt.close();
    return password;
}

void BackEnd::writePost(std::string userId, std::string title, std::string content){
    maxPostNumber++;
    std::string path = SERVER_STORAGE_DIR + userId + "/post/" + std::to_string(maxPostNumber) + ".txt";
    DateTime dateTime;
    std::ofstream my_file(path);
    my_file << dateTime.toString() + "\n" + title + "\n\n" + content;
    my_file.close();
}

class Compare{
public:
    bool operator()(Post* lhs, Post* rhs){
        return lhs->getDateTime().more_new_than(rhs->getDateTime());
    }
};

class CompareForSearch{
public:
    bool operator()(Post* lhs, Post* rhs){
        if(lhs->getKeywordCount() != rhs->getKeywordCount()){
            return lhs->getKeywordCount() > rhs->getKeywordCount();
        } else {
            return lhs->getDateTime().more_new_than(rhs->getDateTime());
        }
    }
};

typedef std::priority_queue<Post*, std::vector<Post*>, Compare> PPqueue;
typedef std::priority_queue<Post*, std::vector<Post*>, CompareForSearch> PPqueueSearch;

std::vector<Post*> BackEnd::recommendPosts(std::string userId){
    PPqueue postQueue;
    std::vector<std::string> friends;
    try {
        std::string path = SERVER_STORAGE_DIR + userId + "/friend.txt";
        std::ifstream friendsIFS(path);
        std::string friend_name;
        while (std::getline(friendsIFS, friend_name)) {
            friends.push_back(friend_name);
        }
        friendsIFS.close();

        for (std::string name : friends) {
            path = SERVER_STORAGE_DIR + name + "/post";
            std::string str; // temporary space for reading in strings
            for (auto &file : std::filesystem::directory_iterator(path)) {
                std::ifstream postStream(file.path());
                std::vector<std::string> words = str_split_BE(file.path().string(), '\\');
                int postId = std::stoi(str_split_BE(words[words.size() - 1], '.')[0]);
                std::getline(postStream, str);
                DateTime dateTime(str);
                if(postQueue.size() == 10 && postQueue.top()->getDateTime().more_new_than(dateTime)){
                    continue;
                }
                std::string title;
                std::getline(postStream, title);
                std::getline(postStream, str);
                std::string content = "";
                while (std::getline(postStream, str)) {
                    content += (str + "\n");
                }
                postStream.close();
                Post* goingIn = new Post(postId, dateTime, title, content);
                if(postQueue.size() == 10) postQueue.pop();
                postQueue.push(goingIn);
            }
        }
    } catch(std::exception& exception){
        exception.what();
    }
    std::vector<Post*> postList;
    while(!postQueue.empty()){
        postList.push_back(postQueue.top());
        postQueue.pop();
    }
    std::reverse(postList.begin(), postList.end());
    return postList;
}

std::vector<Post*> BackEnd::searchPosts(std::vector<std::string> keywords){
    PPqueueSearch postQueue;
    std::vector<std::string> people;
    try {
        std::string path = SERVER_STORAGE_DIR;
        for (auto &file : std::filesystem::directory_iterator(path)) {
            std::vector<std::string> v1 = str_split_BE(file.path().string(), '/');
            people.push_back(v1[v1.size() - 1]);
        }
        for (std::string name : people) {
            path = SERVER_STORAGE_DIR + name + "/post";
            std::string str; // temporary space for reading in strings
            for (auto &file : std::filesystem::directory_iterator(path)) {
                std::ifstream postStream(file.path());
                std::vector<std::string> words = str_split_BE(file.path().string(), '\\');
                int postId = std::stoi(str_split_BE(words[words.size() - 1], '.')[0]);
                std::getline(postStream, str);
                DateTime dateTime(str);
                std::string title;
                std::getline(postStream, title);
                std::getline(postStream, str);
                std::string content = "";
                while (std::getline(postStream, str)) {
                    content += (str + "\n");
                }
                postStream.close();
                int keyword_count = 0;
                std::vector<std::string> words_in_post;
                for (std::string word : str_split_whitespace(title)) words_in_post.push_back(word);
                for (std::string word : str_split_whitespace(content)) words_in_post.push_back(word);
                for (std::string word : words_in_post) {
                    for (std::string keyword : keywords) {
                        if (word == keyword) keyword_count++;
                    }
                }

                if(keyword_count == 0) continue;
                if(postQueue.size() == 10){
                    if(postQueue.top()->getKeywordCount() > keyword_count) continue;
                    else if(postQueue.top()->getKeywordCount() == keyword_count &&
                            postQueue.top()->getDateTime().more_new_than(dateTime)) continue;
                }

                Post *new_post = new Post(postId, dateTime, title, content);
                new_post->setKeywordCount(keyword_count);
                if(postQueue.size() == 10) postQueue.pop();
                postQueue.push(new_post);
            }
        }
    } catch(std::exception& exception){
        exception.what();
    }

    std::vector<Post*> postList;
    while(!postQueue.empty()){
        postList.push_back(postQueue.top());
        postQueue.pop();
    }
    std::reverse(postList.begin(), postList.end());
    return postList;
}

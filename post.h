#ifndef PROBLEM2_POST_H
#define PROBLEM2_POST_H

#include <string>
#include "my_time.h"

class Post{
    int id;
    DateTime dateTime;
    std::string title;
    std::string content;
    int keyWordCount = 0; // maybe possible in another way. pair<index, keywordCount>
public:
    Post();
    Post(int id, DateTime dateTime, std::string title, std::string content);
    // Post(std::string title, std::string content);
    std::string getSummary();
    std::string toString();
    int getId();
    void setId(int id);
    std::string getDate();
    void setDateTime(DateTime dateTime);
    std::string getTitle();
    std::string getContent();
    DateTime getDateTime();
    void setKeywordCount(int count);
    int getKeywordCount();
};

#endif //PROBLEM2_POST_H

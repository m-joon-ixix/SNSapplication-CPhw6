#include "post.h"

Post::Post() {}

Post::Post(int id, DateTime dateTime, std::string title, std::string content): id(id), dateTime(dateTime), title(title){
    this->content = content.substr(0, content.length() - 2); // removing \n\n at the end of content
}

// Post::Post(std::string title, std::string content): Post(-1, DateTime(), title, content) { }

std::string Post::getDate(){
    return dateTime.toString();
}

std::string Post::getSummary(){
    std::string str = "";
    return str + "id: " + std::to_string(id) + ", created at: " + getDate() + ", title: " + title;
}

std::string Post::toString(){
    std::string str = "";
    return str + "-----------------------------------\n" +
           "id: " + std::to_string(id) + "\n" +
           "created at: " + getDate() + "\n" +
           "title: " + title + "\n" +
           "content: " + content;
}

int Post::getId() { return id; }

void Post::setId(int id) { this->id = id; }

void Post::setDateTime(DateTime dateTime) { this->dateTime = dateTime; }

std::string Post::getTitle() { return title; }

std::string Post::getContent() { return content; }

DateTime Post::getDateTime() { return dateTime; }

void Post::setKeywordCount(int count) { this->keyWordCount = count; }

int Post::getKeywordCount() { return keyWordCount; }

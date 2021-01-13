//
// For DateTime Tasks - Created by Minjoon Choi
//

#ifndef PROBLEM2_MY_TIME_H
#define PROBLEM2_MY_TIME_H

#include <iostream>
#include <string>

class DateTime{
    short int year;
    short int month;
    short int day;
    short int hour;
    short int minute;
    short int second;
    std::string intToStr(int number);
public:
    DateTime(); // set to current time
    DateTime(std::string dateTimeString);
    std::string toString();
    bool more_new_than(DateTime dt);
};

#endif //PROBLEM2_MY_TIME_H

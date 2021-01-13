//
// For DateTime Tasks - Created by Minjoon Choi
//

#include "my_time.h"
#include <chrono>
#include <ctime>

using namespace std::chrono;

DateTime::DateTime(){
    auto t = system_clock::to_time_t(system_clock::now());
    std::tm* now = std::localtime(&t);
    year = 1900 + now->tm_year;
    month = 1 + now->tm_mon;
    day = now->tm_mday;
    hour = now->tm_hour;
    minute = now->tm_min;
    second = now->tm_sec;
}

DateTime::DateTime(std::string dateTimeString){
    // example of dateTimeString: "2020/12/19 21:49:32"
    try {
        year = std::stoi(dateTimeString.substr(0, 4));
        month = std::stoi(dateTimeString.substr(5, 7));
        day = std::stoi(dateTimeString.substr(8, 10));
        hour = std::stoi(dateTimeString.substr(11, 13));
        minute = std::stoi(dateTimeString.substr(14, 16));
        second = std::stoi(dateTimeString.substr(17, 19));
    } catch(std::exception exception){
        exception.what();
    }
}

std::string DateTime::intToStr(int number){
    if(number < 10) return "0" + std::to_string(number);
    else return std::to_string(number);
}

std::string DateTime::toString(){
    return intToStr(year) + "/" + intToStr(month) + "/" + intToStr(day) + " "
                         + intToStr(hour) + ":" + intToStr(minute) + ":" + intToStr(second);
}

bool DateTime::more_new_than(DateTime dt){
    if(this->year != dt.year){
        return this->year > dt.year;
    } else {
        if(this->month != dt.month){
            return this->month > dt.month;
        } else {
            if(this->day != dt.day){
                return this->day > dt.day;
            } else {
                if(this->hour != dt.hour){
                    return this->hour > dt.hour;
                } else {
                    if(this->minute != dt.minute){
                        return this->minute > dt.minute;
                    } else {
                        return this->second > dt.second;
                    }
                }
            }
        }
    }
}
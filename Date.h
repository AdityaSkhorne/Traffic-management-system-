#ifndef DATE_H
#define DATE_H

#include "Serializable.h"
#include <ctime>
#include <string>

struct Date : Serializable {
    struct tm date {};
    bool empty;
    
    explicit Date(std::string dateStr);
    Date();
    
    Date operator+(int days);
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    
    bool isEmpty() const;
    std::string toString() const override;
};

#endif
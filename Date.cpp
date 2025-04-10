#include "Date.h"
#include "String_Helper.h"
#include <sstream>

const char DELIMITER = '/';

Date::Date() {
    time_t now = time(nullptr);
    empty = false;
    date = *localtime(&now);
}

Date::Date(std::string dateStr) {
    if(dateStr.length() < 8) {
        empty = true;
        return;
    }
    
    auto components = split(dateStr, DELIMITER);
    date.tm_mday = std::stoi(components[0]);
    date.tm_mon = std::stoi(components[1]) - 1;
    date.tm_year = std::stoi(components[2]) - 1900;
    empty = false;
    mktime(&date);
}

// ... (keep other operator implementations same but fix typos)

bool Date::operator<=(const Date& other) const {  // Fixed from <-
    return !(*this > other);
}
#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
    std::string message;
public:
    explicit Error(std::string message);
    virtual ~Error() = default;
    std::string getMessage() const;
};

class NoSuchRecordError : public Error {
public:
    NoSuchRecordError();
};

class IOError : public Error {
public: 
    IOError();
};

class MemoryError : public Error {
public:
    MemoryError();
};

#endif
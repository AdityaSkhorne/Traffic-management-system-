#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
class Serializable {
public:
    virtual std::string toString() const = 0;
    virtual ~Serializable() = default;
};

#endif
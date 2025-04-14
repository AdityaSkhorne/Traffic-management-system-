#ifndef STORABLE_H
#define STORABLE_H

#include "Serializable.h"

template<class T> class Table;
class Database;

class Storable : public Serializable {
protected:
    long recordId;
    
public:
    explicit Storable(long recordId);
    long getRecordId() const;  // Remove "override"
    virtual void setDataFrom(Storable* s) = 0;

    // Add missing toString() override
    std::string toString() const override = 0;

    friend class Database;
    template<class T> friend class Table;
};

#endif
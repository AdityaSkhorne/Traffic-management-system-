#ifndef table_h
#define table_h

#include "storable.cpp"
#include "error.cpp"

#include <vector>
#include <string>
#include <fstream>

using namespace std;

template <class T> class Table {
private:
    string fileName;
    fstream fileStream;

    vector<Storable *> * records = NULL;

    T * getReferenceOfRecordForId (long recordId) const;

    void writeTofile();

    const T* const addNewRecord (T data);

    void updateRecord (T updateRecord);

public:
    Table (string fileName);
    ~Table();

    long getNextRecordId() const;

    const T* const getRecordForId (long recordId) const;

    friend class Database;
};

#endif

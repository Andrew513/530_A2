#ifndef TABLE_Rec_Iter_H
#define TABLE_Rec_Iter_H

#include "MyDB_RecordIterator.h"

class MyDB_TableRecordIterator : MyDB_RecordIterator
{
private:
    /* data */
public:
    MyDB_TableRecordIterator(/* args */);
    ~MyDB_TableRecordIterator();
    void getNext() override {};
    bool hasNext() override {};
};



#endif
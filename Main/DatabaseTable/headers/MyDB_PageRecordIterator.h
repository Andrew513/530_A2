#ifndef PAGE_Rec_Iter_H
#define PAGE_Rec_Iter_H

#include "MyDB_PageType.h"
#include "MyDB_TableReaderWriter.h"

typedef shared_ptr <MyDB_PageRecordIterator> MyDB_PageRecordIteratorPtr;

class MyDB_PageRecordIterator : MyDB_RecordIterator
{
private:
    
public:
    MyDB_PageRecordIterator();
    ~MyDB_PageRecordIterator();

    void getNext() override {};

    bool hasNext() override {};
};

#endif

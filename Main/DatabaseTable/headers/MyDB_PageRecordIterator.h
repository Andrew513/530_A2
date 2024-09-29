#ifndef PAGE_Rec_Iter_H
#define PAGE_Rec_Iter_H

#include <MyDB_PageReaderWriter.h>
#include "MyDB_PageType.h"
#include "MyDB_TableReaderWriter.h"

typedef shared_ptr <MyDB_PageRecordIterator> MyDB_PageRecordIteratorPtr;

class MyDB_PageRecordIterator : public MyDB_RecordIterator
{
private:
    MyDB_PageType type;
    MyDB_PagePtr page;
    MyDB_RecordPtr record;
    MyDB_BufferManagerPtr buffer;

    size_t currentSize;
    
public:
    MyDB_PageRecordIterator::MyDB_PageRecordIterator(MyDB_PagePtr page, MyDB_BufferManagerPtr buffer);
    ~MyDB_PageRecordIterator();

    void getNext() {};

    bool hasNext() {};

    PageHeader* getPageHeader() {};

    char* getCurrentRecordLocation() {};

    void advanceToNextRecord() {};
    
};

#endif

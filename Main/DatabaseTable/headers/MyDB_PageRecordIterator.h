#ifndef MYDB_PAGERECORDITERATOR_H
#define MYDB_PAGERECORDITERATOR_H

#include "MyDB_PageReaderWriter.h"
#include "MyDB_PageType.h"
#include "MyDB_TableReaderWriter.h"

class MyDB_PageRecordIterator;
typedef shared_ptr <MyDB_PageRecordIterator> MyDB_PageRecordIteratorPtr;


struct PageHeader;

class MyDB_PageRecordIterator : public MyDB_RecordIterator
{
private:
    // MyDB_PageType type;
    MyDB_PagePtr page;
    MyDB_RecordPtr record;
    MyDB_BufferManagerPtr buffer;
    MyDB_PageHandle pageHandler;

    size_t currentSize;
    
public:
    MyDB_PageRecordIterator(MyDB_PageHandle pageHandler, MyDB_RecordPtr iterateIntoMe);
    ~MyDB_PageRecordIterator();

    void getNext();

    bool hasNext();

    PageHeader* getPageHeader();

    char* getCurrentRecordLocation();

    void advanceToNextRecord();

};

#endif

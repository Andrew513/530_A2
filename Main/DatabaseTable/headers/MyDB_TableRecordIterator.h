#ifndef TABLE_Rec_Iter_H
#define TABLE_Rec_Iter_H

#include "MyDB_RecordIterator.h"
#include "MyDB_Record.h"
#include "MyDB_Table.h"
#include "MyDB_PageReaderWriter.h"

typedef shared_ptr <MyDB_TableRecordIterator> MyDB_TableRecordIteratorPtr;

class MyDB_TableRecordIterator : public MyDB_RecordIterator
{
public:
    MyDB_TableRecordIterator(MyDB_RecordPtr recordIn, MyDB_TablePtr tableIn, MyDB_BufferManagerPtr bufferIn);
    ~MyDB_TableRecordIterator();

    void getNext();
    
    bool hasNext();

private:
    int curPageId;
    MyDB_RecordPtr record;
    MyDB_TablePtr table;
    MyDB_PageReaderWriter *curPageWR;
    MyDB_BufferManagerPtr buffer;
    MyDB_RecordIteratorPtr curPageRecIter;
};

#endif
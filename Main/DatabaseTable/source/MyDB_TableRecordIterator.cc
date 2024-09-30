#include "MyDB_TableRecordIterator.h"
#include "MyDB_Table.h"
#include "MyDB_PageReaderWriter.h"
#include <iostream>

using namespace std;

MyDB_TableRecordIterator::MyDB_TableRecordIterator(MyDB_RecordPtr recordIn, MyDB_TablePtr tableIn, MyDB_BufferManagerPtr bufferIn): 
        record(recordIn), table(tableIn), buffer(bufferIn) {
    curPageId = 0;
    curPageWR = new MyDB_PageReaderWriter(curPageId, buffer, table);
    curPageRecIter = curPageWR->getIterator(record);
}

MyDB_TableRecordIterator::~MyDB_TableRecordIterator() {

}

void MyDB_TableRecordIterator::getNext() {
    if (!hasNext()) return;
    if (!curPageRecIter->hasNext()) {
        curPageId++;
        curPageWR = new MyDB_PageReaderWriter(curPageId, buffer, table);
        curPageRecIter = curPageWR->getIterator(record);
    }
    curPageRecIter->getNext();
}

bool MyDB_TableRecordIterator::hasNext() {
    //return true if there is another record in the file
    // in the last page and does not has enough space for storing record
    if (curPageId == table->lastPage() && !curPageRecIter->hasNext()) 
        return false;

    // TODO:need to check page by page, if all pages before last page are full, return false
    // if there is a page that is not full, call pagerecorditerator to check if there is a record
    // than return true

    return true;
}

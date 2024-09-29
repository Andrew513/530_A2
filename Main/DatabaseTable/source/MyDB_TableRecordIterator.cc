#include "MyDB_TableRecordIterator.h"
#include "MyDB_Table.h"
#include "MyDB_PageReaderWriter.h"

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
    // in the last page and does not has enough space for storing record
    if (curPageId == table->lastPage() && !curPageRecIter->hasNext()) 
        return false;

    return true;
}

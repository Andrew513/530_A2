#include "MyDB_PageRecordIterator.h"

void MyDB_PageRecordIterator::getNext() {
    if (!hasNext()) return;
    
    PageHeader *header = getPageHeader();

    record->fromBinary(getCurrentRecordLocation());
    
    advanceToNextRecord();
}
bool MyDB_PageRecordIterator::hasNext() {
    PageHeader *header = getPageHeader();
    return currentSize < header->nextAvailablePlace;
}

PageHeader* MyDB_PageRecordIterator::getPageHeader() {
    return (PageHeader*) page->getBytes(page);
}

char* MyDB_PageRecordIterator::getCurrentRecordLocation() {
    PageHeader *header = getPageHeader();
    return (char*) (header->bytes + currentSize);
}

void MyDB_PageRecordIterator::advanceToNextRecord() {
    currentSize += record->getBinarySize();
}

MyDB_PageRecordIterator::MyDB_PageRecordIterator(MyDB_PagePtr page, MyDB_BufferManagerPtr buffer) 
    : page(page), buffer(buffer), currentSize(0) {}

MyDB_PageRecordIterator :: ~MyDB_PageRecordIterator() {

}
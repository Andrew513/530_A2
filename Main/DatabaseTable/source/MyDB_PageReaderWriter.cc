
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"
#include "MyDB_PageRecordIterator.h"

void MyDB_PageReaderWriter :: clear () {
	PageHeader *header = getPageHeader();
	header->nextAvailablePlace = 0;
	header->numBytesUsed = 0;
	header->type = MyDB_PageType :: RegularPage;
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return getPageHeader()->type;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	// return a new iterator
	return make_shared<MyDB_PageRecordIterator>(page, iterateIntoMe);
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
	getPageHeader()->type = toMe;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr appendMe) {
	PageHeader *header = getPageHeader();
	size_t recordSize = appendMe->getBinarySize();
	size_t pageSize = page->getParent().getPageSize();
	if(header->nextAvailablePlace + recordSize > pageSize) {
		return false;
	}
	appendMe->toBinary((char*)header->bytes[header->nextAvailablePlace]);
	header->nextAvailablePlace += recordSize;
	header->numBytesUsed += recordSize;
	page->wroteBytes();
	return true;
}

PageHeader* MyDB_PageReaderWriter::getPageHeader() {
    return (PageHeader*) page->getBytes(page);
}

MyDB_PageReaderWriter :: MyDB_PageReaderWriter (MyDB_PagePtr page, MyDB_BufferManagerPtr buffer):page(page), buffer(buffer) {}

#endif

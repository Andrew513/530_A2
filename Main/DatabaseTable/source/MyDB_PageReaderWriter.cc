
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"

void MyDB_PageReaderWriter :: clear () {
	PageHeader *header = (PageHeader *) page->getBytes(page);
	header->nextAvailablePlace = 0;
	header->numBytesUsed = 0;
	header->type = MyDB_PageType :: RegularPage;
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	PageHeader *header = (PageHeader *) page->getBytes(page);
	return header->type; // MyDB_PageType :: RegularPage;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	// return a new iterator
	
	return nullptr;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
	PageHeader *header = (PageHeader *) page->getBytes(page);
	header->type = toMe;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr appendMe) {
	PageHeader *header = (PageHeader *) page->getBytes(page);
	size_t recordSize = appendMe->getBinarySize();
	size_t pageSize = page->getParent().getPageSize();
	// Check if there is enough space to append the record
	if(header->nextAvailablePlace + recordSize > pageSize) {
		return false;
	}
	// if there is enough space, append the record
	appendMe->toBinary((char *)header + header->nextAvailablePlace);
	header->nextAvailablePlace += recordSize;
	// update the number of bytes used
	header->numBytesUsed += recordSize;
	//update the starting byte of the next record
	page->wroteBytes();
	return true;
}

#endif

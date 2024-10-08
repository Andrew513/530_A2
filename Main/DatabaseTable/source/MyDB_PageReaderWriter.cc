
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"
#include "MyDB_PageRecordIterator.h"
#include <iostream>

using namespace std;

void MyDB_PageReaderWriter :: clear () {
	PageHeader *header = getPageHeader();
	header->nextAvailablePlace = 0;
	header->numBytesUsed = 0;
	header->type = MyDB_PageType :: RegularPage;
	pageHandler->wroteBytes();
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return getPageHeader()->type;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	// return a new iterator
	return make_shared<MyDB_PageRecordIterator>(pageHandler, iterateIntoMe);
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
	getPageHeader()->type = toMe;
	pageHandler->wroteBytes();
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr appendMe) {
	if(index == -1) return false;

	PageHeader *header = getPageHeader();
	if(!header) return false;

	size_t recordSize = appendMe->getBinarySize();
	size_t pageSize = buffer->getPageSize();

	if(sizeof(*header) + header->nextAvailablePlace + recordSize > pageSize) {
		return false;
	}

	appendMe->toBinary((char*)(header->bytes + header->nextAvailablePlace));
	header->nextAvailablePlace = (char*)(header->bytes + header->nextAvailablePlace + recordSize) - (char*)header->bytes;
	header->numBytesUsed += recordSize;
	pageHandler->wroteBytes();
	// table->setLastPage(index);
	
	// cout << "after append: " << header->nextAvailablePlace << endl;
	return true;
}

PageHeader* MyDB_PageReaderWriter::getPageHeader() {
	PageHeader *header = (PageHeader*)pageHandler->getBytes();
    return header;
}

MyDB_PageReaderWriter :: MyDB_PageReaderWriter (long i, MyDB_BufferManagerPtr buffer, MyDB_TablePtr table):index(i), buffer(buffer), table(table) {
	pageHandler = buffer->getPage(table, index);
	
	// PageHeader *header = (PageHeader*)pageHandler->getBytes();
	// header->nextAvailablePlace = 0;
	// header->numBytesUsed = 0;
	// header->type = MyDB_PageType :: RegularPage;
}

#endif

// void MyDB_PageReaderWriter::overWrite(char* overwriteMe, int pageSize) {
// 	PageHeader *header = getPageHeader();
// 	header->nextAvailablePlace = 0;
// 	header->numBytesUsed = pageSize;
// 	header->type = MyDB_PageType :: RegularPage;
// 	memcpy(header->bytes, overwriteMe, pageSize);
// }



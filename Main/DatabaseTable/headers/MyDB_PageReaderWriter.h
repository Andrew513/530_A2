
#ifndef PAGE_RW_H
#define PAGE_RW_H

#include "MyDB_PageType.h"
#include "MyDB_TableReaderWriter.h"

struct PageHeader {
	// the next available place to write a record
	unsigned nextAvailablePlace;
	// the number of bytes used on the page
	size_t numBytesUsed;
	// the type of the page
	MyDB_PageType type;
	// record starting point
	char bytes[0];
};

class MyDB_PageReaderWriter {

public:

	// ANY OTHER METHODS YOU WANT HERE

	// empties out the contents of this page, so that it has no records in it
	// the type of the page is set to MyDB_PageType :: RegularPage
	void clear ();	

	// return an itrator over this page... each time returnVal->next () is
	// called, the resulting record will be placed into the record pointed to
	// by iterateIntoMe
	MyDB_RecordIteratorPtr getIterator (MyDB_RecordPtr iterateIntoMe);

	// appends a record to this page... return false is the append fails because
	// there is not enough space on the page; otherwise, return true
	bool append (MyDB_RecordPtr appendMe);

	// gets the type of this page... this is just a value from an ennumeration
	// that is stored within the page
	MyDB_PageType getType ();

	// sets the type of the page
	void setType (MyDB_PageType toMe);

	MyDB_PageReaderWriter (long i, MyDB_BufferManagerPtr buffer, MyDB_TablePtr table);

	PageHeader* getPageHeader();

	void overWrite(char* overwriteMe, int pageSize);
	
private:

	// ANYTHING ELSE YOU WANT HERE
	long index;
	MyDB_BufferManagerPtr buffer;
	MyDB_TablePtr table;
	MyDB_PageHandle pageHandler;
};

#endif

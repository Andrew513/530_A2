
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_TableRecordIterator.h"
#include "MyDB_Record.h"

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr t, MyDB_BufferManagerPtr bm) : table(t), buffer(bm) {
	curPageId = 0;
	pageSize = buffer->getPageSize();
	curPageRW = new MyDB_PageReaderWriter(curPageId, buffer, table);
}

MyDB_PageReaderWriter MyDB_TableReaderWriter :: operator [] (size_t i) {
	if (i > table->lastPage()) {
		// set up all of the pages after the old last page to be empty

		return last();
	}
	
	MyDB_PageReaderWriter temp(i, buffer, table); // use i as parameter to determine pageReaderWriter points to which page
	return temp;
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	MyDB_RecordPtr emptyRec = make_shared<MyDB_Record>(nullptr);
	return emptyRec;
}

MyDB_PageReaderWriter MyDB_TableReaderWriter :: last () {
	long lastPageId = table->lastPage();
	MyDB_PageReaderWriter lastPage(lastPageId, buffer, table); // use lastPageId as parameter
	return lastPage;	
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr appendMe) {
	if (!last().append(appendMe)) {
		cout << "Failed to append record\n";
	}
}

void MyDB_TableReaderWriter :: loadFromTextFile (string fromMe) {
	int fd = open(fromMe.c_str(), O_RDONLY);
	if (fd == -1) {
		cerr << "Failed to open the file: " << fromMe << endl;
		return;
	}

	char readBuffer[pageSize];
	ssize_t bytesRead;
	long curPageId = 0, lastPageId = table->lastPage();
	while ((bytesRead == read(fd, readBuffer, pageSize)) > 0 || curPageId <= lastPageId) {
		MyDB_PageReaderWriter pageRW(curPageId, buffer, table); // use curPageId to determine which page is pointed to
		
		// overwrite page content
		// pageRW->overwrite(buffer);
		
		curPageId++;
	}
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	return make_shared<MyDB_TableRecordIterator>(iterateIntoMe, table, buffer);
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string toMe) {
	
}

#endif


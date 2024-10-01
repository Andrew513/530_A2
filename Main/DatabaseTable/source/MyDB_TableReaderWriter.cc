
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_TableRecordIterator.h"
#include "MyDB_Record.h";

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr t, MyDB_BufferManagerPtr bm) : table(t), buffer(bm) {
	curPageId = 0;
	pageSize = buffer->getPageSize();
	shared_ptr<MyDB_PageReaderWriter> curPageRW = make_shared<MyDB_PageReaderWriter>(curPageId, buffer, table);
}

// access the i^th page in this file
MyDB_PageReaderWriter MyDB_TableReaderWriter::operator[](size_t i) {

	while (i > table->lastPage()) {
		table->setLastPage(table->lastPage() + 1);
		shared_ptr<MyDB_PageReaderWriter> newPage = make_shared<MyDB_PageReaderWriter>(table->lastPage(), buffer, table);
		newPage->clear();
	}

	return MyDB_PageReaderWriter(i, buffer, table);
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	//NOTE: can't be nullptr becuase it requires the schema of the table !!!!
	MyDB_RecordPtr emptyRec = make_shared<MyDB_Record>(table->getSchema());
	return emptyRec;
}

MyDB_PageReaderWriter MyDB_TableReaderWriter :: last () {
	long lastPageId = table->lastPage();
	shared_ptr<MyDB_PageReaderWriter> lastPage = make_shared<MyDB_PageReaderWriter>(lastPageId, buffer, table);
	// cout<<"last page id: "<<lastPageId<<endl;
	return *lastPage;	
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr appendMe) {
	shared_ptr<MyDB_PageReaderWriter> lastPageRW = make_shared<MyDB_PageReaderWriter>(table->lastPage(), buffer, table);

	// cout<<"debugging point 1-0" << endl;
	while(lastPageRW->append(appendMe) == false) {
		// cout<<"debugging point 1-1" << endl;
		// create a new page
		table->setLastPage(table->lastPage() + 1);
		// cout<<"debugging point 1-2" << endl;
		lastPageRW = make_shared<MyDB_PageReaderWriter>(table->lastPage(), buffer, table);
		// cout<<"debugging point 1-3" << endl;
		lastPageRW->clear();
		
	}
	// if (!last().append(appendMe)) {
	// 	cout << "Failed to append record\n";
	// }
}

void MyDB_TableReaderWriter :: loadFromTextFile (string fromMe) {
	ifstream fileStream(fromMe);
	if (!fileStream.is_open()) {
		cerr << "Unable to open the file: " << fromMe << endl;
		return;
	}
	long currentPageId = 0;
	long lastPageId = table->lastPage();
	shared_ptr<MyDB_PageReaderWriter> currentPageRW = make_shared<MyDB_PageReaderWriter>(currentPageId, buffer, table);
	currentPageRW->clear();
	string line; 
	while (getline(fileStream, line)) {
		// cout<<"debugging point 1" << endl;
		MyDB_RecordPtr record = getEmptyRecord();
		// cout<<"debugging point 2" << endl;
		record->fromString(line);
		// cout<<"debugging point 3" << endl;
		append(record);
		// cout<<"debugging point 4" << endl;
		if (currentPageId < lastPageId) {
			currentPageId++;
			currentPageRW = make_shared<MyDB_PageReaderWriter>(currentPageId, buffer, table);
			currentPageRW->clear();
		}
		// cout << "debugging point 5" << endl;
	}
	fileStream.close();
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	return make_shared<MyDB_TableRecordIterator>(iterateIntoMe, table, buffer);
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string toMe) {
	ofstream file(toMe);
	if (!file.is_open()) {
		cerr << "Failed to open the file: " << toMe << endl;
		return;
	}
	MyDB_RecordPtr record = getEmptyRecord();
	MyDB_RecordIteratorPtr recordItr = getIterator(record);
	while(recordItr->hasNext()) {
		recordItr->getNext();
		ostringstream recordStream;
		recordStream << record;
		file << recordStream.str() << endl;
	}
	file.close();
}

#endif


#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
using namespace std;

class librarian
{
public:
	librarian();
	librarian(string libID, string libName, int ligAge, int libContNo);
	//librarian(sql::ResultSet* Data);
	~librarian();
	void LibrarianCount();
	void GenLibID();
	void AddLibrarian();
	bool LibrarianLogin();
	void LibrarianRecord();
	void ViewLibrarian();
	//vector<librarian> SearchLibrarian(string keyword,string sortColumn, int minAge, int maxAge, bool asc);
	void LibUpdate();
	void getLibData(string libID);
	void DeleteLibrarian(string libID);
	string libID, libName;
	int libAge, libContNo, libNo;

private:

};
#endif

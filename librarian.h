#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include <mysql/jdbc.h>
#include <string>
#include <vector> 
#include <utility>  
using namespace std;
using namespace sql;

class librarian
{
public:
	string libID, libName;
	int libAge, libContNo, libNo;

	librarian();
	librarian(ResultSet* data);
	~librarian();
	void LibrarianCount();
	void GenLibID();
	void AddLibrarian();
	bool LibrarianLogin();
	static vector<librarian> SearchLibrarian();
	void LibUpdate();
	void getLibData(string libID);
	void DeleteLibrarian(string libID);

private:

};
#endif

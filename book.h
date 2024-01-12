#ifndef BOOK_H
#define BOOK_H
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
#include <vector> 
#include <utility>  
using namespace std;
using namespace sql;
class book
{
public:
	book();
	book(ResultSet* data);
	~book();
	void ViewBook();
	void AddBook();
	void BookCount();
	void GenBID();
	bool isValidBook(string bTitle);
	void SearchBook();
	void GetBookData(string bID);
	void UpdateBook();
	void DeleteBook(string bID);
	static vector<book> NewStock();
	static vector <book> SearchBook(string keyword);
	string bID, bTitle, Author, bStatus, category, language;
	int bQuantity, ISBN;
	double bPrice;

private:
	static int bookCount, bookNo;
};
#endif


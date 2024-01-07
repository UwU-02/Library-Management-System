#ifndef BOOK_H
#define BOOK_H
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
using namespace std;

class book
{
public:
	book();
	book(string bID, string bTitle, string Author, string bStatus, string category, string language, int bQuantity, double bPrice, long ISBN);
	~book();
	void ViewBook();
	void AddBook();
	void BookCount();
	void GenBID();
	bool isValidBook(string & bTitle);
	//string returnTitle(string& bTitle);
	void SearchBook();
	void GetBookData(string bID);
	void UpdateBook();
	void DeleteBook(string bID);
	string bID, bTitle, Author, bStatus, category, language, UID;
	int bQuantity, ISBN;
	double bPrice;
	int bookCount, bookNo;

private:

};
#endif


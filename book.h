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
	void AddBook();
	void BookCount();
	void GenBID();
	void defineLastRow();
	void updateLastRow();
	bool isValidBook(string bTitle);
	void GetBookData(string bID);
	void UpdateBook();
	void DeleteBook(string bID);
	static vector<book> NewStock(string keyword);
	static vector <book> SearchBook(string keyword, int choice);
	string bID, bTitle, Author, bStatus, category, language, insertDate;
	int bQuantity, ISBN;
	double bPrice;

private:
	static int bookCount, bookNo;
	static string temp;
};
#endif


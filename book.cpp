#include "book.h"
#include "DbConnection.h"
#include "page.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <sstream>
using namespace std;

book::book()
{
	bID = "";
	bTitle = "";
	Author = "";
	bQuantity = 0;
	bPrice = 0;
	ISBN = 0;
	bStatus = "";
	category = "";
	language = "";
}

book::book(string bID, string bTitle, string Author, string bStatus, string category, string language, int bQuantity, double bPrice, long ISBN)
{
	this->bID = bID;
	this->bTitle = bTitle;
	this->Author = Author;
	this->bQuantity = bQuantity;
	this->bPrice = bPrice;
	this->ISBN = ISBN;
	this->bStatus = bStatus;
	this->category = category;
	this->language = language;
}

void book::ViewBook()
{

}

void book::AddBook()
{
	DBConnection db;
	db.prepareStatement("INSERT INTO book(BookID, Title, Author, Quantity, Price, ISBN, Status, Category, Language) VALUES (?,?,?,?,?,?,?,?,?)");
	db.stmt->setString(1, bID);
	db.stmt->setString(2, bTitle);
	db.stmt->setString(3, Author);
	db.stmt->setInt(4, bQuantity);
	db.stmt->setDouble(5, bPrice);
	db.stmt->setInt(6, ISBN);
	db.stmt->setString(7, bStatus);
	db.stmt->setString(8, category);
	db.stmt->setString(9, language);
	db.QueryStatement();
	db.~DBConnection();
}

void book::BookCount()
{
	DBConnection db;
	db.prepareStatement("SELECT COUNT(Title) AS BOOKCOUNT FROM book");
	db.QueryResult();

	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			bookNo = db.res->getInt("BOOKCOUNT");
	}
	else
		cout << "Error retrieving book count." << endl;
}

void book::GenBID()
{
	BookCount();
	bookNo++;
	stringstream b;
	b << "B" << setfill('0') << setw(5) << bookNo;
	bID = b.str();
}
bool book::isValidBook(string bTitle)
{
	DBConnection db;
	db.prepareStatement("SELECT Title FROM book WHERE BookID=? ");
	db.stmt->setString(1, bID);

	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			bTitle = db.res->getString("Title");
			cout << "Book Title: " << bTitle << endl;
			_getch();
		}
		db.~DBConnection();
		return true;
	}
	else {
		cout << "This book does not exist. Please try again." << endl;
		_getch();
		db.~DBConnection();
		return false;
	}
}

void book::SearchBook()
{

}
void book::GetBookData(string bID)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM book WHERE BookID=?");
	db.stmt->setString(1, bID);
	db.QueryResult();
	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			bID = db.res->getString("BookID");
			bTitle = db.res->getString("Title");
			Author = db.res->getString("Author");
			bQuantity = db.res->getInt("Quantity");
			bPrice = db.res->getDouble("Price");
			ISBN = db.res->getInt("ISBN");
			bStatus = db.res->getString("Status");
			category = db.res->getString("Category");
			language = db.res->getString("Language");
		}
	}
	else
	{
		cout << "Error retrieving book details." << endl;
		_getch();
	}
	db.~DBConnection();
}
void book::UpdateBook()
{
	DBConnection db;
	db.prepareStatement("UPDATE book SET Title = ?, Author = ?, Quantity = ?, Price = ?, ISBN = ?, Status = ?, Category = ?, Language = ? WHERE BookID = ? ");
	db.stmt->setString(1, bTitle);
	db.stmt->setString(2, Author);
	db.stmt->setInt(3, bQuantity);
	db.stmt->setDouble(4, bPrice);
	db.stmt->setInt(5, ISBN);
	db.stmt->setString(6, bStatus);
	db.stmt->setString(7, category);
	db.stmt->setString(8, language);
	db.stmt->setString(9, bID);
	db.QueryStatement();
	db.~DBConnection();
}
void book::DeleteBook(string bID)
{
	DBConnection db;
	db.prepareStatement("DELETE FROM book WHERE BookID = ?");
	db.stmt->setString(1, bID);
	db.QueryStatement();
	db.~DBConnection();
}
book::~book()
{

}
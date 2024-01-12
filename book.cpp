#include "book.h"
#include "DbConnection.h"
#include "page.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;
using namespace sql;

int book::bookCount = 0, book::bookNo = 0;

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

book::book(ResultSet* data)
{
	bID = data->getString("BookID");
	bTitle = data->getString("Title");
	Author = data->getString("Author");
	bQuantity = data->getInt("Quantity");
	bPrice = data->getDouble("Price");
	ISBN = data->getInt("ISBN");
	bStatus = data->getString("Status");
	category = data->getString("Category");
	language = data->getString("Language");
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

vector<book> book::NewStock()
{
	vector <book> Book;
	DBConnection db;
	db.prepareStatement("SELECT * FROM book ORDER BY BookID DESC LIMIT 20 ");
	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			book tmpReport(db.res);
			Book.push_back(tmpReport);
		}
	}
	db.~DBConnection();
	return Book;
}

vector <book> book::SearchBook(string keyword)
{
	DBConnection db;
	vector <book> books;

	string query = "SELECT * FROM book WHERE (Title like ? OR Author like ? OR Status like ? OR Category like ? OR Language like ?)";
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + keyword + "%");
	db.stmt->setString(2, "%" + keyword + "%");
	db.stmt->setString(3, "%" + keyword + "%");
	db.stmt->setString(4, "%" + keyword + "%");
	db.stmt->setString(5, "%" + keyword + "%");

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next()) {
			book tmpUser(db.res);
			books.push_back(tmpUser);
		}
	}

	db.~DBConnection();
	return books;
}

book::~book()
{

}
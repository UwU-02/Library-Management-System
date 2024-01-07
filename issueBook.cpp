#include "issueBook.h"
#include "book.h"
#include "user.h"
#include "librarian.h"
#include "DbConnection.h"
#include "page.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
using namespace std;
issueBook::issueBook()
{
	caseID = "";
	brwDate = "";
	rtnDate = "";
	bID = "";
	libID = "";
	UID = "";
}
issueBook::issueBook(string caseID, string brwDate, string rtnDate, string libID, string UID, string bID)
{
	this->caseID = caseID;
	this->brwDate = brwDate;
	this->rtnDate = rtnDate;
	this->bID = bID;
	this->libID = libID;
	this->UID = UID;
}

void issueBook::borrowBook()
{
	DBConnection db;
	db.prepareStatement("INSERT INTO `issue book`(CaseID, bID, UID, libID, brwDate, rtnDate) VALUES (?,?,?,?,?,?)");
	db.stmt->setString(1, caseID);
	db.stmt->setString(2, bID);
	db.stmt->setString(3, UID);
	db.stmt->setString(4, libID);
	db.stmt->setString(5, brwDate);
	db.stmt->setString(6, rtnDate);
	db.QueryStatement();
	//db.~DBConnection();
}

void issueBook::returnBook()
{
	DBConnection db;
	db.prepareStatement("UPDATE book SET Status = 'Available' WHERE BookID = ?");
	db.stmt->setString(1, bID);
	db.QueryStatement();
	db.~DBConnection();
}

void issueBook::updateBookStatus(string bID)
{
	DBConnection db;
	db.prepareStatement("UPDATE book SET Status = 'Borrowing' WHERE BookID = ?");
	db.stmt->setString(1, bID);
	db.QueryStatement();
	//db.~DBConnection();
}
void issueBook::GenCaseID()
{
	CaseCount();
	caseNo++;
	stringstream c;
	c << "C" << setfill('0') << setw(5) << caseNo;
	caseID = c.str();
}
bool issueBook::isBookAvailable()
{
	DBConnection db;
	book b;
	db.prepareStatement("SELECT * FROM book WHERE BookID= ? and status = 'Available' ");
	db.stmt->setString(1, bID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			bID = db.res->getString("BookID");
		}
		db.~DBConnection();
		return true;
	}
	else 
	{
		_getch();
		db.~DBConnection();
		return false;
	}
}
void issueBook::CaseCount()
{
	DBConnection db;
	db.prepareStatement("SELECT COUNT(caseID) AS ISSUEBOOKCOUNT FROM `issue book`");
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			caseNo = db.res->getInt("ISSUEBOOKCOUNT");
	}
	else
		cout << "Error retrieving issue book count." << endl;
}

void issueBook::checkLateRtn()
{
	DBConnection db;
	db.prepareStatement("SELECT rtnDate FROM book WHERE BookID= ?");
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			rtnDate = db.res->getString("rtnDate");
	}
	else
		cout << "Error retrieving the return date." << endl;
}

issueBook::~issueBook()
{

}
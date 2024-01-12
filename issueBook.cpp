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
#include <vector>
#include <utility>
#include <mysql/jdbc.h>

using namespace std;
using namespace sql;

int issueBook::caseNo=0;

issueBook::issueBook()
{
	caseID = "";
	brwDate = "";
	rtnDate = "";
	bID = "";
	libID = "";
	UID = "";
	rtn = "";
	daysCount = 0;
}

issueBook::issueBook(ResultSet* data)
{
	caseID = data->getString("CaseID");
	brwDate = data->getString("brwDate");
	expDate = data->getString("expDate");
	rtnDate = data->getString("rtnDate");
	bID = data->getString("bID");
	libID = data->getString("libID");
	UID = data->getString("UID");
	rtn = data->getString("Return?");
}

void issueBook::borrowBook()
{
	DBConnection db;
	db.prepareStatement("INSERT INTO `issue book`(CaseID, bID, UID, libID, brwDate, expDate, `Return?`) VALUES (?,?,?,?,?,?,?)");
	db.stmt->setString(1, caseID);
	db.stmt->setString(2, bID);
	db.stmt->setString(3, UID);
	db.stmt->setString(4, libID);
	db.stmt->setString(5, brwDate);
	db.stmt->setString(6, expDate);
	db.stmt->setString(7, rtn);
	db.QueryStatement();
	db.prepareStatement("UPDATE book SET Status = 'Borrowing' WHERE BookID = (SELECT bID FROM `issue book` WHERE CaseID = ?) ");
	db.stmt->setString(1, caseID);
	db.QueryStatement();
	db.~DBConnection();
}

void issueBook::updateExpDate(string caseID)
{
	DBConnection db;
	db.prepareStatement("UPDATE `issue book` SET expDate = DATE_ADD(brwDate, INTERVAL 14 DAY), `Return?` = 'No' WHERE CaseID = ? ");
	db.stmt->setString(1, caseID);
	db.QueryStatement();
	getExpDate(caseID);
}

void issueBook::getExpDate(string caseID)
{
	DBConnection db;
	db.prepareStatement("SELECT expDate FROM `issue book` WHERE CaseID = ? ");
	db.stmt->setString(1, caseID);
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			expDate = db.res->getString("expDate");
	}
	else
		cout << "Error retrieving the expiry date." << endl;
}

void issueBook::returnBook()
{
	DBConnection db;
	db.prepareStatement("UPDATE `issue book` SET rtnDate = ? WHERE CaseID = ?");
	db.stmt->setString(1, rtnDate);
	db.stmt->setString(2, caseID);
	db.QueryStatement();
	db.prepareStatement("UPDATE `issue book` SET `Return?` = 'YES' WHERE CaseID = ?");
	db.stmt->setString(1, caseID);
	db.QueryStatement();
	db.prepareStatement("UPDATE book SET Status = 'Available' WHERE BookID = (SELECT bID FROM `issue book` WHERE CaseID = ?) ");
	db.stmt->setString(1, caseID);
	db.QueryStatement();
	db.~DBConnection();
}

bool issueBook::checkCase()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM `issue book` WHERE CaseID = ? AND `Return?` = 'No'");
	db.stmt->setString(1, caseID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) 
	{
		db.~DBConnection();
		return true;
	}
	else
	{
		db.~DBConnection();
		return false;
	}
}

void issueBook::updateBookStatus(string bID)
{
	DBConnection db;
	db.prepareStatement("UPDATE book SET Status = 'Borrowing' WHERE BookID = ?");
	db.stmt->setString(1, bID);
	db.QueryStatement();

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
		db.~DBConnection();
		return false;
	}
}

void issueBook::GenCaseID()
{
	CaseCount();
	caseNo++;
	stringstream c;
	c << "C" << setfill('0') << setw(5) << caseNo;
	caseID = c.str();
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

bool issueBook::checkLateRtn()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM `issue book` WHERE expDate < CURRENT_TIMESTAMP AND CaseID = ?");
	db.stmt->setString(1, caseID);
	db.QueryResult();
	return db.res->rowsCount() == 1;
}

void issueBook::DaysCal()
{
	DBConnection db;
	db.prepareStatement("SELECT DATEDIFF(CURRENT_TIMESTAMP, expDate) AS DAYSCOUNT from `issue book` WHERE CaseID = ?");
	db.stmt->setString(1, caseID);
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			daysCount = db.res->getInt("DAYSCOUNT");
		cout << daysCount;
	}
	else
		cout << "Error retrieving days count." << endl;
}

/*vector<report> report::brwReceipt(string caseID)
{

}*/


issueBook::~issueBook()
{

}
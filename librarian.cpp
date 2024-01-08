#include "librarian.h"
#include "DbConnection.h"
#include "page.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <sstream>
using namespace std;

librarian::librarian()
{
	libID = "";
	libName = "";
	libAge = 0;
	libContNo = 0;
}
librarian::librarian(string libID, string libName, int ligAge, int libContNo)
{
	this->libID = libID;
	this->libName = libName;
	this->libAge = libAge;
	this->libContNo = libContNo;
}

/*librarian::librarian(sql::ResultSet* data)
{
	libID = data->getString("libID");
	libName = data->getString("libName");
	libAge = data->getInt("libAge");
	libContNo = data->getInt("libContNo");
}
*/

void librarian::AddLibrarian()
{
	DBConnection db;
	db.prepareStatement("Insert into librarian(LibrarianName,Age,LibrarianContactNo, LibrarianID) VALUES (?,?,?,?)");
	db.stmt->setString(1, libName);
	db.stmt->setInt(2, libAge);
	db.stmt->setInt(3, libContNo);
	db.stmt->setString(4, libID);
	db.QueryStatement();
	db.~DBConnection();
}

void librarian::LibrarianCount()
{
	DBConnection db;
	db.prepareStatement("SELECT COUNT(LibrarianName) AS LIBRARIANCOUNT FROM librarian");
	db.QueryResult();

	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			libNo = db.res->getInt("LIBRARIANCOUNT");
	}
	else
		cout << "Error retrieving librarian count." << endl;
}

void librarian::GenLibID()
{
	LibrarianCount();
	libNo++;
	stringstream l;
	l << "L" << setfill('0') << setw(2) << libNo;
	libID = l.str();
}

bool librarian::LibrarianLogin()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM librarian WHERE LibrarianID=? ");
	db.stmt->setString(1, libID);

	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			libID = db.res->getString("LibrarianID");
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
void librarian::LibrarianRecord()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM librarian");
}
void librarian::ViewLibrarian()
{

}
/*
vector<librarian> librarian::SearchLibrarian(string keyword, string sortColumn,int minAge, int maxAge, bool asc)
{
	string query = "SELECT * FROM 'librarian' WHERE (LibrarianName LIKE ? OR Address LIKE ?) AND Age >= ? AND Age <= ? ORDER BY " + sortColumn;
	if (asc)
		query += " ASC";
	else
		query += " DESC";
	vector<librarian> librarians;
	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + keyword + "%");
	db.stmt->setString(2, "%" + keyword + "%");
	db.stmt->setInt(3, minAge)
	db.stmt->setInt(4, maxAge);

	vector<librarian> librarians;
	db.QueryResult();
	if (db.res->rowsCount())
	{
		while (db.res->next() > 0)
		{
			librarian tempLib(db.res);
			librarians.push_back(tempLib);
		}
	}
	db.~DBConnection();
	return librarians;
}
*/
void librarian::LibUpdate()
{
	DBConnection db;
	db.prepareStatement("UPDATE librarian SET LibrarianName = ?, Age = ?, LibrarianContactNo = ? WHERE LibrarianID = ? ");
	db.stmt->setString(1, libName);
	db.stmt->setInt(2, libAge);
	db.stmt->setInt(3, libContNo);
	db.stmt->setString(4, libID);
	db.QueryStatement();
	db.~DBConnection();
}

void librarian::getLibData(string libID)
{
	DBConnection db;
	db.prepareStatement("SELECT* FROM librarian WHERE LibrarianID=?");
	db.stmt->setString(1, libID);
	db.QueryResult();
	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			libID = db.res->getString("libID");
			libName = db.res->getString("libName");
			libAge = db.res->getInt("adminAge");
			libContNo = db.res->getInt("libContNo");
		}
	}
	db.~DBConnection();

}

void librarian::DeleteLibrarian(string libID)
{
	DBConnection db;
	db.prepareStatement("DELETE FROM librarian WHERE LibrarianID = ?");
	db.stmt->setString(1, libID);
	db.QueryStatement();
	db.~DBConnection();
}
librarian::~librarian()
{

}


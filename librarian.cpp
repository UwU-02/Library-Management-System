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

string librarian::tmp = "";

librarian::librarian()
{
	libID = "";
	libName = "";
	libAge = 0;
	libContNo = 0;
}

librarian::librarian(ResultSet* data)
{
	libID = data->getString("LibrarianID");
	libName = data->getString("LibrarianName");
	libAge = data->getInt("Age");
	libContNo = data->getInt("LibrarianContactNo");
}

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

vector<librarian> librarian::SearchLibrarian()
{
	DBConnection db;
	vector<librarian> lib;
	db.prepareStatement("SELECT * FROM librarian");

	db.QueryResult();
	if (db.res->rowsCount())
	{
		while (db.res->next() > 0)
		{
			librarian tempLib(db.res);
			lib.push_back(tempLib);
		}
	}
	else
	{
		cout << "No librarian found! Please try again.";
		_getch();
	}
	db.~DBConnection();
	return lib;
}

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
	db.prepareStatement("SELECT * FROM librarian WHERE LibrarianID=?");
	db.stmt->setString(1, libID);
	db.QueryResult();
	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			libID = db.res->getString("LibrarianID");
			libName = db.res->getString("LibrarianName");
			libAge = db.res->getInt("Age");
			libContNo = db.res->getInt("LibrarianContactNo");
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

void librarian::defineLastRow()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM librarian ORDER BY LibrarianID DESC LIMIT 1");
	db.QueryResult();

	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			tmp = db.res->getString("LibrarianID");
		}
	}
	else {
		std::cout << "Error retrieving librarian count." << std::endl;
	}
}

void librarian::updateLastRow()
{
	defineLastRow();
	DBConnection db;
	db.prepareStatement("UPDATE book SET LibrarianID =? WHERE LibrarianID=?");
	db.stmt->setString(1, libID);
	db.stmt->setString(2, tmp);
	db.QueryStatement();
	db.~DBConnection();
}

librarian::~librarian()
{

}


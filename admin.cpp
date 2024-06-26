#include "admin.h"
#include "DbConnection.h"
#include "page.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

int admin::adminCount = 0;
string admin::tmp = "";

admin::admin()
{
	adminID = "";
	adminName = "";
	adminPwd = "";
	adminContNo = 0;
}

admin::admin(string adminID, string adminName, string adminPwd, int adminContNo)
{
	this->adminID = adminID;
	this->adminName = adminName;
	this->adminPwd = adminPwd;
	this->adminContNo = adminContNo;
}

void admin::AddAdmin()
{
	DBConnection db;
	db.prepareStatement("INSERT INTO admin(AdminName, AdminID, AdminPassword, AdminContactNo) VALUES (?,?,?,?)");
	db.stmt->setString(1, adminName);
	db.stmt->setString(2, adminID);
	db.stmt->setString(3, adminPwd);
	db.stmt->setInt(4, adminContNo);
	db.QueryStatement();
	db.~DBConnection();
}

void admin::AdminCount()
{
	DBConnection db;
	db.prepareStatement("SELECT COUNT(AdminID) AS ADMINCOUNT FROM admin");
	db.QueryResult();

	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			adminNo = db.res->getInt("ADMINCOUNT");
	}
	else
		cout << "Error retrieving admin count." << endl;
	
}

void admin::GenAdminID()
{
	AdminCount();
	adminNo++;
	stringstream a;
	a << "A" << setfill('0') << setw(2) << adminNo;
	adminID = a.str();
}

bool admin::AdminLogin()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM admin WHERE AdminID=? AND AdminPassword=?");
	db.stmt->setString(1, adminID);
	db.stmt->setString(2, adminPwd);
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			adminID = db.res->getString("AdminID");
			adminPwd = db.res->getString("AdminPassword");
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

void admin::ViewAdmin()
{
	DBConnection db;
	db.prepareStatement("SELECT AdminName, AdminContactNo FROM admin");
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			cout << setw(5) << adminName << setw(20) << adminContNo << endl;
		}
	}
	db.~DBConnection();
}

void admin::AdminUpdate()
{
	DBConnection db;
	db.prepareStatement("UPDATE admin SET AdminName = ?, AdminContactNo = ?, AdminPassword = ? WHERE AdminID = ? ");
	db.stmt->setString(1, adminName);
	db.stmt->setInt(2, adminContNo);
	db.stmt->setString(3, adminPwd);
	db.stmt->setString(4, adminID);
	db.QueryStatement();
	db.~DBConnection();
}

void admin::getAdminData(string adminID)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM admin WHERE AdminID=?");
	db.stmt->setString(1, adminID);
	db.QueryResult();
	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			adminID = db.res->getString("AdminID");
			adminName = db.res->getString("AdminName");
			adminPwd = db.res->getString("AdminPassword");
			adminContNo = db.res->getInt("AdminContactNo");
		}
	}
	db.~DBConnection();
}

void admin::DeleteAdmin(string adminID)
{
	DBConnection db;
	db.prepareStatement("DELETE FROM admin WHERE AdminID = ?");
	db.stmt->setString(1, adminID);
	db.QueryStatement();
	db.~DBConnection();
}

void admin::defineLastRow()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM admin ORDER BY AdminID DESC LIMIT 1");
	db.QueryResult();

	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			tmp = db.res->getString("AdminID");
		}
	}
	else {
		std::cout << "Error retrieving admin count." << std::endl;
	}
}

void admin::updateLastRow()
{
	defineLastRow();
	DBConnection db;
	db.prepareStatement("UPDATE admin SET AdminID =? WHERE AdminID=?");
	db.stmt->setString(1, adminID);
	db.stmt->setString(2, tmp);
	db.QueryStatement();
	db.~DBConnection();
}

admin::~admin()
{

}
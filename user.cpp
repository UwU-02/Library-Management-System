#include "user.h"
#include "DbConnection.h"
#include "page.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <conio.h>

user::user()
{
	UID = "";
	username = "";
	email = "";
	uContNo = 0;
	uAddress = "";
}

user::user(string UID, string username, string email, string uAddress, int uContNo)
{
	this->UID = UID;
	this->username = username;
	this->email = email;
	this->uAddress = uAddress;
	this->uContNo = uContNo;
}

void user::UserSearchBook()
{

}

void user::UserCount()
{
	DBConnection db;
	db.prepareStatement("SELECT COUNT(UserName) AS USERCOUNT FROM user");
	db.QueryResult();

	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			userNo = db.res->getInt("USERCOUNT");
	}
	else
		cout << "Error retrieving user count." << endl;
}
void user::AddUser()
{
	DBConnection db;
	db.prepareStatement("INSERT INTO user(UserID, UserName, email, ContactNo, Address) VALUES (?,?,?,?,?)");
	db.stmt->setString(1, UID);
	db.stmt->setString(2, username);
	db.stmt->setString(3, email);
	db.stmt->setInt(4, uContNo);
	db.stmt->setString(5, uAddress);
	db.QueryStatement();
	db.~DBConnection();
}
void user::GenUID()
{
	UserCount();
	userNo++;
	stringstream u;
	u << "U" << setfill('0') << setw(4) << userNo;
	UID = u.str();
}
/*
int DBConnection::getGenId() {
	DBConnection db;
	db.prepareStatement("SELECT LAST_INSERT_ID();");
	db.QueryResult();
	int lastInsertId = -1;
	if (db.res->rowsCount() > 0) {
		while (db.res->next()) {
			lastInsertId = db.res->getInt64("LAST_INSERT_ID()");
		}
	}
	return lastInsertId;
}
*/
bool user::isValidUser(string& username)
{
	DBConnection db;
	db.prepareStatement("SELECT UserName FROM user WHERE UserID=? ");
	db.stmt->setString(1, UID);

	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			username = db.res->getString("UserName");
			cout << "User Name: " << username << endl;
			_getch();
		}
		db.~DBConnection();
		return true;
	}
	else
	{
		cout << "This book does not exist. Please try again." << endl;
		_getch();
		db.~DBConnection();
		return false;
	}
}
bool user::UserBorrowRecord()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM `issue book` WHERE UID=? ");
	db.stmt->setString(1, UID);

	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			UID = db.res->getString("UID");
			_getch();
		}
		db.~DBConnection();
		return false;
	}
	else
	{
		db.~DBConnection();
		return true;
	}
}
void user::ViewUser()
{

}
void user::SearchUser()
{

}
void user::UpdateUser()
{
	DBConnection db;
	db.prepareStatement("UPDATE user SET UserName=?, email=?,ContactNo=?, address=? WHERE UID=?");
	db.stmt->setString(1, username);
	db.stmt->setInt(2, uContNo);
	db.stmt->setString(3, email);
	db.stmt->setString(4, uAddress);
	db.stmt->setString(5, UID);
	db.QueryStatement();
	db.~DBConnection();
}

void user::DeleteUser(string UID)
{
	DBConnection db;
	db.prepareStatement("DELETE FROM user WHERE UserID = ?");
	db.stmt->setString(1, UID);
	db.QueryStatement();
	db.~DBConnection();
}

user::~user()
{

}
#include "user.h"
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

int userCount=0, userNo=0;
string user::tmp = "";

user::user()
{
	UID = "";
	username = "";
	email = "";
	uContNo = 0;
	uAddress = "";
}

user::user(ResultSet* data)
{
	UID = data->getString("UserID");
	username = data->getString("UserName");
	email = data->getString("email");
	uAddress = data->getString("Address");
	uContNo = data->getInt("ContactNo");
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
	db.prepareStatement("SELECT * FROM `issue book` WHERE UID=? AND `Return?` = 'No'");
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

vector <user> user::SearchUser(string keyword)
{
	DBConnection db;
	vector <user> users;

	string query = "SELECT * FROM user WHERE (UserName like ?)";
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + keyword + "%");
	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next()) {
			user tmpUser(db.res);
			users.push_back(tmpUser);
		}
	}
	else
	{
		cout << "No user found! Please try again.";
		_getch();
	}
	db.~DBConnection();
	return users;
}

void user::getUserData(string UID)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM user WHERE UserID=?");
	db.stmt->setString(1, UID);
	db.QueryResult();
	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			username = db.res->getString("UserName");
			email = db.res->getString("email");
			uContNo = db.res->getInt("ContactNo");
			uAddress = db.res->getString("Address");
		}
	}
	else
	{
		cout << "Error retrieving user details. ";
		_getch();
	}
	db.~DBConnection();
}

void user::UpdateUser()
{
	DBConnection db;
	db.prepareStatement("UPDATE user SET UserName=?, email=?, ContactNo=?, Address=? WHERE UserID=?");
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

void user::defineLastRow()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM user ORDER BY UserID DESC LIMIT 1");
	db.QueryResult();

	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			tmp = db.res->getString("UserID");
		}
	}
	else {
		std::cout << "Error retrieving user count." << std::endl;
	}
}

void user::updateLastRow()
{
	defineLastRow();
	DBConnection db;
	db.prepareStatement("UPDATE user SET UserID =? WHERE UserID=?");
	db.stmt->setString(1, UID);
	db.stmt->setString(2, tmp);
	db.QueryStatement();
	db.~DBConnection();
}

user::~user()
{

}
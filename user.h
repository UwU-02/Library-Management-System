#ifndef USER_H
#define USER_H
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
using namespace std;

class user
{
public:
	string UID, username, email, uAddress;
	int uContNo, userCount, userNo;
	user();
	user(string UID,string username, string email, string uAddress, int uContNo);
	~user();
	void UserSearchBook();
	void UserCount();
	void AddUser();
	void GenUID();
	bool isValidUser(string& username);
	bool UserBorrowRecord();
	void ViewUser();
	void SearchUser();
	void UpdateUser();
	void DeleteUser(string UID);

private:

};
#endif


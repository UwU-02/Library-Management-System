#ifndef ADMIN_H
#define ADMIN_H
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
using namespace std;

class admin
{

private:


public:
	string adminID, adminPwd, adminName;
	int adminNo, adminContNo;
	admin();
	admin(string adminID, string adminPwd, string adminName, int adminContNo);
	~admin();
	void AdminCount();
	void GenAdminID();
	void AddAdmin();
	//void setPassword(string pass);
	//string getPassword();
	//bool MatcPasswordWith(string plainText);
	//bool isMatch(string encrypted, string testText);
	//string encrypt(string input);
	//char toChar(int asciDecimal);
	bool AdminLogin();
	void ViewAdmin();
	void AdminUpdate();
	void getAdminData(string adminID);
	void DeleteAdmin(string adminID);

};
#endif

#ifndef ADMIN_H
#define ADMIN_H
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
using namespace std;

class admin
{

private:
	static int adminCount;
	static string tmp;

public:
	string adminID, adminPwd, adminName;
	int adminNo, adminContNo;
	admin();
	admin(string adminID, string adminPwd, string adminName, int adminContNo);
	~admin();
	void AdminCount();
	void GenAdminID();
	void AddAdmin();
	bool AdminLogin();
	void ViewAdmin();
	void AdminUpdate();
	void getAdminData(string adminID);
	void DeleteAdmin(string adminID);
	void defineLastRow();
	void updateLastRow();

};
#endif

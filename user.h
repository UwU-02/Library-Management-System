#ifndef USER_H
#define USER_H
#include <mysql/jdbc.h>
#include <string>
#include <vector> 
#include <utility>  
using namespace std;
using namespace sql;

class user
{
public:
	string UID, username, email, uAddress;
	int uContNo;

	user();
	user(ResultSet* data);
	~user();
	void UserCount();
	void AddUser();
	void GenUID();
	bool isValidUser(string& username);
	bool UserBorrowRecord();
	static vector <user> SearchUser(string keyword);
	void getUserData(string UID);
	void UpdateUser();
	void DeleteUser(string UID);

private:

};
#endif


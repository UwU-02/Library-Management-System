#ifndef ISSUEBOOK_H
#define ISSUEBOOK_H
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
using namespace std;

class issueBook
{
public:
	issueBook();
	issueBook(string caseID, string brwDate, string expDate, string rtnDate, string libID, string UID, string bID, string rtn);
	~issueBook();
	void borrowBook();
	void updateExpDate(string caseID);
	void getExpDate(string caseID);
	void returnBook();
	bool checkCase();
	bool isBookAvailable();
	void updateBookStatus(string bID);
	void GenCaseID();
	void CaseCount();
	bool checkLateRtn();
	void DaysCal();
	string caseID, brwDate, expDate, rtnDate, bID, UID, libID, rtn;
	int caseNo, daysCount;

private:

};
#endif


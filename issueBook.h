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
	issueBook(string caseID, string brwDate, string rtnDate, string bID, string UID, string libID, string rtn);
	~issueBook();
	void borrowBook();
	void updateRtnDate(string caseID);
	void getRtnDate(string caseID);
	void returnBook();
	bool isBookAvailable();
	//void updateBookCount(string bID);
	void updateBookStatus(string bID);
	void GenCaseID();
	void CaseCount();
	bool checkLateRtn();
	void DaysCal();
	string caseID, brwDate, rtnDate, bID, UID, libID, rtn;
	int caseNo, daysCount;

private:

};
#endif


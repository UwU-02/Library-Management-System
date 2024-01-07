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
	issueBook(string caseID, string brwDate, string rtnDate, string bID, string UID, string libID);
	~issueBook();
	void borrowBook();
	void returnBook();
	bool isBookAvailable();
	//void updateBookCount(string bID);
	void updateBookStatus(string bID);
	void GenCaseID();
	void CaseCount();
	void checkLateRtn();
	string caseID, brwDate, rtnDate, bID, UID, libID;
	int caseNo;

private:

};
#endif


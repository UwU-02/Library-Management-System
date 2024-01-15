#ifndef ISSUEBOOK_H
#define ISSUEBOOK_H
#include <mysql/jdbc.h>
#include <string>
#include <vector> 
#include <utility>  
using namespace std;
using namespace sql;

class issueBook
{
public:
	string caseID, brwDate, expDate, rtnDate, bID, UID, libID, rtn;
	int daysCount;

	issueBook();
	issueBook(ResultSet* data);
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

private:
	static int caseNo;
};
#endif


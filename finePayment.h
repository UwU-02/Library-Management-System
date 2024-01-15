#ifndef FINEPAYMENT_H
#define FINEPAYMENT_H
#include <mysql/jdbc.h>
#include <string>
#include <vector> 
#include <utility>  
using namespace std;
using namespace sql;

class finePayment
{
public:
	string payID, expDate, rtnDate, caseID, libID, UID, payMethod, payDate;
	int paymentNo;
	double fine;
	finePayment();
	finePayment(ResultSet* data);
	void payCount();
	void genPayID();
	void insertPay();
	static vector<finePayment> LateReturnReport(string payDate);
	~finePayment();


private:

};
#endif

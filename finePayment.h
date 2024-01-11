#ifndef FINEPAYMENT_H
#define FINEPAYMENT_H
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
using namespace std;

class finePayment
{
public:
	finePayment();
	finePayment(string caseID, string rtnDate, string UID, string libID, string rtn, string payID, string payMethod, double fine);
	void payCount();
	void genPayID();
	void insertPay();
	~finePayment();
	string payID, expDate, rtnDate, caseID, libID, UID, payMethod;
	int paymentNo;
	double fine;

private:

};
#endif

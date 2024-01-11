#include "finePayment.h"
#include "issueBook.h"
#include "user.h"
#include "DbConnection.h"
#include "page.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

finePayment::finePayment()
{
	payID = "";
	caseID = "";
	UID = "";
	libID = "";
	fine = 0.00;
	payMethod = "";
}

finePayment::finePayment(string caseID, string rtnDate, string UID, string libID, string rtn, string payID, string payMethod, double fine)
{
	this->payID = payID;
	this->caseID = caseID;
	this->UID = UID;
	this->libID = libID;
	this->fine = fine;
	this->payMethod = payMethod;
}

void finePayment::insertPay()
{
	DBConnection db;
	db.prepareStatement("INSERT INTO finepayment (payID, caseID, UID, libID, fine, PayMethod) VALUES (?,?,?,?,?,?)");
	db.stmt->setString(1, payID);
	db.stmt->setString(2, caseID);
	db.stmt->setString(3, UID);
	db.stmt->setString(4, libID);
	db.stmt->setDouble(5, fine);
	db.stmt->setString(6, payMethod);
	db.QueryStatement();
	db.prepareStatement("UPDATE finepayment SET UID= (SELECT UID from `issue book` WHERE CaseID =?)");
	db.stmt->setString(1, caseID);
	db.QueryStatement();
}

void finePayment::payCount()
{
	DBConnection db;
	db.prepareStatement("SELECT COUNT(caseID) AS PAYMENTCOUNT FROM finepayment");
	db.QueryResult();

	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
			paymentNo = db.res->getInt("PAYMENTCOUNT");
	}
	else
		cout << "Error retrieving payment count." << endl;
}

void finePayment::genPayID()
{
	payCount();
	paymentNo++;
	stringstream p;
	p << "P" << setfill('0') << setw(5) << paymentNo;
	payID = p.str();
}

finePayment::~finePayment()
{

}
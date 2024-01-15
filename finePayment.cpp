#include "finePayment.h"
#include "issueBook.h"
#include "user.h"
#include "DbConnection.h"
#include "page.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;
using namespace sql;

finePayment::finePayment()
{
	payID = "";
	caseID = "";
	UID = "";
	libID = "";
	fine = 0.00;
	payMethod = "";
}

finePayment::finePayment(ResultSet* data)
{
	payID = data->getString("payID");
	caseID = data->getString("caseID");
	UID = data->getString("UID");
	libID = data->getString("libID");
	fine = data->getDouble("fine");
	payMethod = data->getString("payMethod");
	payDate = data->getString("payDate");
}

void finePayment::insertPay()
{
	DBConnection db;
	db.prepareStatement("INSERT INTO finepayment (payID, caseID, UID, libID, fine, PayMethod, payDate) VALUES (?,?,?,?,?,?,?)");
	db.stmt->setString(1, payID);
	db.stmt->setString(2, caseID);
	db.stmt->setString(3, UID);
	db.stmt->setString(4, libID);
	db.stmt->setDouble(5, fine);
	db.stmt->setString(6, payMethod);
	db.stmt->setString(7, payDate);
	db.QueryStatement();
	db.~DBConnection();
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

vector<finePayment> finePayment::LateReturnReport(string payDate)
{
	vector <finePayment> lrr;
	DBConnection db;
	db.prepareStatement("SELECT * FROM finepayment WHERE payDate = ? ORDER BY payID ASC");
	db.stmt->setString(1, payDate);
	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			finePayment tmpReport(db.res);
			lrr.push_back(tmpReport);
		}
	}
	else
	{
		cout << "No data found! Please try again.";
		_getch();
	}

	db.~DBConnection();
	return lrr;
}

finePayment::~finePayment()
{

}
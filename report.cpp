#include "report.h"
#include "DbConnection.h"
#include "page.h"
#include "book.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <utility>
#include <mysql/jdbc.h>

using namespace std;
using namespace sql;

report::report(ResultSet* data)
{
	issueCount = data->getInt("BorrowersCount");
	bTitle = data->getString("Title");
}

vector<report> report::TopPopularBook(string brwDate)
{
	vector <report> TopPopularBook;
	DBConnection db;
	db.prepareStatement("SELECT B.Title as Title,COUNT(I.bID) AS BorrowersCount FROM `issue book` I JOIN book B ON I.bID = B.BookID WHERE I.brwDate >= ? GROUP BY Title ORDER BY BorrowersCount DESC LIMIT 10 ");
	db.stmt->setString(1, brwDate);

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			report tmpReport(db.res);
			TopPopularBook.push_back(tmpReport);
		}
	}
	db.~DBConnection();
	return TopPopularBook;
}

vector<report> report::TopTenEngFic(string brwDate)
{
	vector <report> TopTenEngFic;
	DBConnection db;
	db.prepareStatement("SELECT B.Title AS Title, COUNT(I.bID) AS BorrowersCount FROM `issue book` I JOIN book B ON I.bID = B.BookID WHERE I.brwDate >= ? AND B.Category = 'Fiction' AND B.Language = 'English' GROUP BY Title ORDER BY BorrowersCount DESC LIMIT 10 ");
	db.stmt->setString(1, brwDate);

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			report tmpReport(db.res);
			TopTenEngFic.push_back(tmpReport);
		}
	}
	db.~DBConnection();
	return TopTenEngFic;
}

vector<report> report::TopTenMalayFic(string brwDate)
{
	vector <report> TopTenMalayFic;
	DBConnection db;
	db.prepareStatement("SELECT B.Title AS Title, COUNT(I.bID) AS BorrowersCount FROM `issue book` I JOIN book B ON I.bID = B.BookID WHERE I.brwDate >= ? AND B.Category = 'Fiction' AND B.Language = 'Malay' GROUP BY Title ORDER BY BorrowersCount DESC LIMIT 10 ");
	db.stmt->setString(1, brwDate);

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			report tmpReport(db.res);
			TopTenMalayFic.push_back(tmpReport);
		}
	}
	db.~DBConnection();
	return TopTenMalayFic;
}




report::~report()
{

}

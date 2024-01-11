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

using namespace std;
using namespace sql;

report::report()
{
    issueCount = 0;
}

void report::TopTenPopularBook()
{
	DBConnection db;
	db.prepareStatement("SELECT Title, COUNT(*) AS BorrowersCount FROM `issue book` JOIN book ON `issue book`.bID = book.BookID GROUP BY book.Title ORDER BY issue_count DESC LIMIT 10 ");
	db.QueryStatement();
	db.~DBConnection();
	return;
}

vector<pair<string, int>> getTopTenBooks() 
{
    DBConnection db;
    book books;
    try {
        db.prepareStatement("SELECT book.Title, COUNT(*) AS BorrowerCount FROM  `issue book` JOIN book ON `issue book`.bID = book.BookID GROUP BY book.Title ORDER BY BorrowerCount DESC LIMIT 10");

        db.QueryResult();

        vector<pair<string, int>> topTen;
        while (db.res->next()) {
            string title = db.res->getString("Title");
            int issueCount = db.res->getInt("BorrowerCount");
            topTen.push_back({ books.bTitle, issueCount });
        }

        cout << "Top 10 Popular Books:\n";
        for (const auto& book : topTen) {
            cout << book.first << " (Issued: " << book.second << " times)\n";
        }
    }
    catch (sql::SQLException& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return {};
}

report::~report()
{

}

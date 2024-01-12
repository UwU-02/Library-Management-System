#pragma once
#ifndef REPORT_H
#define REPORT_H

#include <mysql/jdbc.h>
#include <string>
#include <vector> 
#include <utility>  

using namespace std;
using namespace sql;

class report
{
public:
    string bTitle;
    int issueCount;

    report(ResultSet* data);
    static vector<report> TopPopularBook(string brwDate);
    static vector<report> TopTenEngFic(string brwDate);
    static vector<report> TopTenMalayFic(string brwDate);

    ~report();


};
#endif
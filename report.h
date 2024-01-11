#pragma once
#ifndef REPORT_H
#define REPORT_H

#include <mysql/jdbc.h>
#include <string>
#include <vector>    // Include header for vector
#include <utility>   // Include header for pair

class report
{
public:
    int issueCount;
    report();
    ~report();
    void TopTenPopularBook();
};
#endif
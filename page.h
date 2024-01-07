#pragma once
#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <vector>
#include <utility>
using namespace std;
class page
{
public:
	string header, footer, bullet;
    page();
	void addOption(string option);
	void setValue(int index, string value);
	int prompt();
	~page();
private:
	std::vector<pair<string, string>> options;
	// [ {"1","2"}  ,{"1","2"}  ]
};


#endif
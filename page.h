#pragma once
#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <vector>
#include <utility>

class page
{
public:
	std::string header, footer, bullet;
	page();
	void addOption(std::string option);
	void setValue(int index, std::string value);
	int prompt();
	~page();
private:
	std::vector<std::pair<std::string, std::string>> options;
	// [ {"1","2"}  ,{"1","2"}  ]
};


#endif
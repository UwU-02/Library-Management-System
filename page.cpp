#include "page.h"
#include <iostream>
#include <conio.h>
using namespace std;

page::page() {
	header = "";
	footer = "Select option";
	bullet = ". ";
}
/*
int page::prompt() {
	int selected = -1;
	do
	{
		system("cls"); // clear ur console
		cout << header << endl;
		for (int i = 0; i < options.size(); i++) {//loop through each option 
			cout << i + 1 << bullet << options[i].first;
			if (options[i].second != "") {
				cout << " : " << options[i].second;
			}
			cout << endl;
		}
		cout << footer << endl;
        
		selected = _getch() - '0';
	} while (selected < 1 || selected > options.size());
	return selected;
}
*/

int page::prompt() {
    int selected = -1;
    string inputString;
    do {
        system("cls"); // Clear console
        cout << header << endl;
        for (int i = 0; i < options.size(); i++) 
        {
            cout << i + 1 << bullet << options[i].first;
            if (options[i].second != "") 
            {
                cout << " : " << options[i].second;

            }
            cout << endl;
        }
        cout << footer << endl;
        getline(cin, inputString);

        try 
        {
            selected = stoi(inputString);  // Convert input to integer
            if (selected < 1 || selected > options.size()) 
            {
                throw invalid_argument("Invalid option");
            }
        }

        catch (const invalid_argument& e) 
        {
            cout << "Invalid option. Please enter a number between 1 and "
                << options.size() << "." << endl;
        }

    } while (selected < 1 || selected > options.size());
    return selected;
}

void page::addOption(string option) {
	options.push_back({ option,"" });
}
void page::setValue(int index, string value) {
	if (index >= 0 && index < options.size()) {
		options[index].second = value;
	}
}
page::~page() {
	options.clear();
}
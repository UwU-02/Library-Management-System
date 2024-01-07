#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <sstream>
//#include <time.h>

#include "DbConnection.h"
#include "page.h"
#include "admin.h"
#include "librarian.h"
#include "user.h"
#include "book.h"
#include "issueBook.h"

using namespace std;

void MainPage();
void AdminLogin();
void AdminRegister();
void AdminMenu();
//void LibrarianSearch(); no need
void UpdateAdmin();
void UpdateLibrarian();
void UpdateBook();
void UpdateUser();
void LibrarianLogin();
void LibrarianMenu(librarian lib);
void LibrarianRegister(string libID);

void UserMenu();
void UserRegister(string UID);

void InsertBook(string bID);
void Borrow(librarian lib);
void Return();
bool isNumeric(string input);
//string hiddenInput(string = "");
//string hideString(string);
//string hideString(int);


int main()
{
	MainPage();
	return 0;
}

void MainPage() //done
{
	page main;
	main.header = "=================================================================================\n                  Welcome to Acanthe Library Management System                   \n=================================================================================\n";
	main.addOption("Login as Admin");
	main.addOption("Login as Librarian");
	main.addOption("Browse as User");
	main.addOption("Exit");
	while (1)
	{
		switch (main.prompt())
		{
		case 1:
			AdminLogin();
			break;
		case 2:
			LibrarianLogin();
			break;
		case 3:
			UserMenu();
			break;
		case 4:
			exit(0);
			break;
		default:
			cout << endl << endl << "Please choose between 1 - 4. Press Enter To Continue...";
			_getch();
			MainPage();
			break;
		}
	}
}
void AdminLogin()//done
{
	page home;
	admin Admin;

	home.header = "==========================================\n               Admin Login                \n==========================================\n";
	home.addOption("AdminID");
	home.addOption("AdminPassword");
	home.addOption("Login");
	home.addOption("Admin Register");
	home.addOption("Back");
	while (1)
	{

		switch (home.prompt())
		{
		case 1:
			cout << "Insert your AdminID:";
			cin >> Admin.adminID;
			home.setValue(0, Admin.adminID);
			break;
		case 2:
			cout << "Insert Password:";
			cin >> Admin.adminPwd;
			home.setValue(1, Admin.adminPwd);
			break;
		case 3:
			if (Admin.AdminLogin())
			{
				cout << "Login successfully. ";
				AdminMenu();
			}
			else
			{
				cout << "Admin ID or password incorrect.	Please try again.";
				_getch();
			}
			break;
		case 4:
			AdminRegister();
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}
void AdminRegister() //done
{
	admin newAcc;
	page registerPage;
	bool valid = true;
	registerPage.header = "=========================================\n             Admin Register             \n=========================================\n";
	registerPage.addOption("Name");
	registerPage.addOption("Password");
	registerPage.addOption("Contact No");
	registerPage.addOption("Confirm");
	registerPage.addOption("Back");
	string tmpinput;
	bool valid;
	while (1)
	{
		switch (registerPage.prompt())
		{
		case 1:
			cout << "Name: ";
			getline(cin, newAcc.adminName);
			registerPage.setValue(0, newAcc.adminName);
			break;
		case 2:
			cout << "Password: ";
			cin >> newAcc.adminPwd;
			registerPage.setValue(1, newAcc.adminPwd);
			break;
		case 3:
			cout << "Contact No: ";
			cin >> tmpinput;
			if (isNumeric(tmpinput) && tmpinput.length() == 10) {
				newAcc.adminContNo = stoi(tmpinput);
				registerPage.setValue(2, to_string(newAcc.adminContNo));
			}
			else {
				cout << "Input for Contact No must be number with 10 digit";
				_getch();
			}
			break;
		case 4:
			valid = true;
			if (valid)
			{
				newAcc.GenAdminID();
				registerPage.setValue(3, newAcc.adminID);
				newAcc.AddAdmin();
				cout << "Your admin ID is " << newAcc.adminID << endl;
				cout << "Registered successfully. \nPress Enter to continue." << endl;
				_getch();
				main();
			}
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}
void AdminMenu() //done
{
	page AMenu;
	librarian lList;
	AMenu.header = "=========================================\n          Welcome to Admin Menu          \n=========================================\n";
	AMenu.addOption("Update Admin Info");
	AMenu.addOption("Add Librarian");
	AMenu.addOption("List of Librarian");
	AMenu.addOption("Search Librarian");
	AMenu.addOption("Back");
	while (1)
	{
		switch (AMenu.prompt())
		{
		case 1:
			UpdateAdmin();
			break;
		case 2:
			LibrarianRegister(lList.libID);
			break;
		case 3:
			lList.LibrarianRecord();
			break;
		case 4:
			//LibrarianSearch();
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}
/*
void LibrarianSearch()
{
	librarian lib;
	page searchlib;
	vector <librarian> librarians;
	string displayString = "", keyword = "", sortColumn = "libID";
	int minAge, maxAge;
	int lid = -1;
	bool asc = true;
	librarians = librarians::SearchLibrarian(keyword, sortColumn, minAge, maxAge, asc);
	searchlib.header = "====================================\n				Search Librarian\n====================================\n";
	searchlib.addOption("Keyword");
	searchlib.addOption("Sort by");
	searchlib.addOption("Order by");
	searchlib.addOption("Search");
	searchlib.addOption("Back");
	while (1)
	{
		searchlib.setValue(1, sortColumn);
		if (asc)
			searchlib.setValue(2,"Ascending");
		else
			searchlib.setValue(3, "Descending");

		if (displayString == "")
		{
			displayString = "\nSearch Result: \n\n";
			stringstream tmpString;
			tmpString << fixed << setprecision(2) << setw(5) << "Librarian ID" << setw(10)
				<< "|" << setw(10) << "Name" << setw(10) << "|" << setw(10) << "Age" << setw(10)
				<< "|" << setw(10) << "Contact No" << setw(10) << "|" << setw(10) << "Address";
			for (int i = 0; i < lib.size(); i++)
			{
				tmpString<<setw(8)<<lib[i].libID<<
			}
		}
	}
}
*/
void LibrarianLogin() //done
{
	page home;
	librarian lib;
	book books;
	user users;
	home.header = "============================================\n              Librarian Login               \n============================================\n";
	home.addOption("LibrarianID");
	home.addOption("Login");
	home.addOption("Back");

	while (1)
	{
		switch (home.prompt())
		{
		case 1:
			cout << "Insert your LibrarianID:";
			cin >> lib.libID;
			home.setValue(0, lib.libID);
			break;
		case 2:
			if (lib.LibrarianLogin())
			{
				LibrarianMenu(lib);
			}
			else
			{
				cout << "Librarian ID does not exists.	Please try again.";
				_getch();
			}
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}
}

void UpdateAdmin() //problem updating info
{
	admin Admin;
	Admin.getAdminData(Admin.adminID);
	admin temp = Admin;
	page update;
	string tmpinput;
	char confirm = '0';
	update.header = "====================================\n        Update Admin Details        \n====================================\n";
	update.addOption("Name");
	update.addOption("Password");
	update.addOption("Contact No");
	update.addOption("Confirm");
	update.addOption("Back");
	update.addOption("Delete Admin");
	while (1) {
		update.setValue(0, temp.adminName);
		update.setValue(1, temp.adminPwd);
		update.setValue(2, to_string(temp.adminContNo));
		switch (update.prompt())
		{
		case 1:
			cout << "New admin name: ";
			getline(cin, temp.adminName);
			update.setValue(0, temp.adminName);
			break;

		case 2:
			cout << "New password: ";
			cin >> temp.adminPwd;
			update.setValue(1, temp.adminPwd);
			break;

		case 3:
			cout << "New contact no: ";
			cin >> tmpinput;
			if (isNumeric(tmpinput) && tmpinput.length() == 10) {
				temp.adminContNo = stoi(tmpinput);
				update.setValue(2, to_string(temp.adminContNo));
			}
			else {
				cout << "Input for Contact No must be number with 10 digit";
				_getch();
			}
			break;
		case 4:
			Admin = temp;
			Admin.AdminUpdate();
			cout << "Updated successfully. \nPress Enter to continue." << endl;
			_getch();
			main();
			break;
		case 5:
			return;
			break;
		case 6:
			cout << "Delete your account?	(Y/N) ";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				Admin.DeleteAdmin(Admin.adminID);
				cout << "Your account has been deleted. Press Enter to continue." << endl;
				_getch();
				main();
			}
			else if (confirm == 'N' || confirm == 'n')
			{
				_getch();
				return;
			}
			else
			{
				cout << "Please choose between 'Y' for YES or 'N' for NO.";
				_getch();
				return;
			}
			break;
		default:
			break;
		}
	}
}
void UpdateLibrarian()
{
	librarian lib;
	lib.getLibData(lib.libID);
	librarian temp = lib;
	page update;
	string tmpinput;
	char confirm = '0';
	update.header = "========================================\n        Update Librarian Details        \n========================================\n";
	update.addOption("Name");
	update.addOption("Age");
	update.addOption("Contact No");
	update.addOption("Confirm");
	update.addOption("Back");
	update.addOption("Delete Librarian");
	while (1) {
		update.setValue(0, temp.libName);
		update.setValue(1, to_string(temp.libAge));
		update.setValue(2, to_string(temp.libContNo));
		switch (update.prompt())
		{
		case 1:
			cout << "New librarian name: ";
			getline(cin, temp.libName);
			update.setValue(0, temp.libName);
			break;

		case 2:
			cout << "Age: ";
			cin >> temp.libAge;
			update.setValue(1, to_string(temp.libAge));
			break;

		case 3:
			cout << "New contact no: ";
			cin >> tmpinput;
			if (isNumeric(tmpinput) && tmpinput.length() == 10) {
				temp.libContNo = stoi(tmpinput);
				update.setValue(2, to_string(temp.libContNo));
			}
			else {
				cout << "Input for Contact No must be number with 10 digit";
				_getch();
			}
			break;
		case 4:
			lib = temp;
			lib.LibUpdate();
			cout << "Updated successfully. \nPress Enter to continue." << endl;
			_getch();
			main();
			break;
		case 5:
			return;
			break;
		case 6:
			cout << "Delete your account?	(Y/N) ";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				lib.DeleteLibrarian(lib.libID);
				cout << "Your account has been deleted. Press Enter to continue." << endl;
				_getch();
				main();
			}
			else if (confirm == 'N' || confirm == 'n')
			{
				_getch();
				return;
			}
			else
			{
				cout << "Please choose between 'Y' for YES or 'N' for NO.";
				_getch();
				return;
			}
			break;
		default:
			break;
		}
	}
}
void UpdateBook()
{
	book b;
	book temp = b;
	page update;
	string tmpinput;
	char confirm = '0';
	b.GetBookData(b.bID);
	update.header = "========================================\n        Update Book Details        \n========================================\n";
	update.addOption("Title");
	update.addOption("Author");
	update.addOption("Quantity");
	update.addOption("Price");
	update.addOption("ISBN");
	update.addOption("Status");
	update.addOption("Category");
	update.addOption("Language");
	update.addOption("Confirm Update");
	update.addOption("Back");
	update.addOption("Delete Book");
	int cat, lang;
	bool valid;
	char choice = '0';
	ostringstream formattedPrice;
	while (1)
	{
		switch (update.prompt())
		{
		case 1:
			cout << "Title:	 ";
			getline(cin, temp.bTitle);
			update.setValue(0, temp.bTitle);
			break;
		case 2:
			cout << "Author:	";
			getline(cin, temp.Author);
			update.setValue(1, temp.Author);
			break;
		case 3:
			cout << "Quantity:	";
			temp.bQuantity = 1;
			update.setValue(2, to_string(temp.bQuantity));
			break;
		case 4:
			cout << "Price:	 RM";
			cin >> temp.bPrice;
			formattedPrice << fixed << setprecision(2) << temp.bPrice;
			update.setValue(3, formattedPrice.str());
			break;
		case 5:
			cout << "ISBN:	";
			cin >> temp.ISBN;
			update.setValue(4, to_string(temp.ISBN));
			break;
		case 6:
			cout << "Status:	";
			cout << "Available" << endl;
			temp.bStatus = "Available";
			update.setValue(5, temp.bStatus);
			break;
		case 7:
			cout << "Category: " << endl;
			cout << "1. Fiction" << endl;
			cout << "2. Non-Fiction" << endl;
			cout << "3. Reference" << endl;
			cout << "4. Magazine & Newspaper" << endl;
			cout << "5. Dictionary" << endl;
			cout << "6. Encyclopedia" << endl;
			cout << "7. Others" << endl;

			cin >> cat;
			if (cat == 1) {
				temp.category = "Fiction";
				update.setValue(6, temp.category);
			}
			else if (cat == 2) {
				temp.category = "Non-Fiction";
				update.setValue(6, temp.category);
			}
			else if (cat == 3) {
				temp.category = "Reference";
				update.setValue(6, temp.category);
			}
			else if (cat == 4) {
				temp.category = "Magazine & Newspaper";
				update.setValue(6, temp.category);
			}
			else if (cat == 5) {
				temp.category = "Dictionary";
				update.setValue(6, temp.category);
			}
			else if (cat == 6) {
				temp.category = "Encyclopedia";
				update.setValue(6, temp.category);
			}
			else if (cat == 7) {
				temp.category = "Others";
				update.setValue(6, temp.category);
			}
			else
			{
				cout << "Please choose between 1-7. Press enter to continue." << endl;
				_getch();
			}
			break;
		case 8:
			cout << "Language:" << endl;
			cout << "1. English" << endl;
			cout << "2. Malay" << endl;
			cout << "3. Others" << endl;
			cin >> lang;
			if (lang == 1) {
				temp.language = "English";
				update.setValue(7, temp.language);
			}
			else if (lang == 2) {
				temp.language = "Malay";
				update.setValue(7, temp.language);
			}
			else if (lang == 3) {
				temp.language = "Others";
				update.setValue(7, temp.language);
			}
			else
			{
				cout << "Please choose between 1-3. Press enter to try again." << endl;
				_getch();
			}
			break;
		case 9:
			b = temp;
			b.UpdateBook();
			cout << "Updated successfully. Press Enter to continue." << endl;
			_getch();
			main();
			break;
		case 10:
			cout << "Delete this book?	(Y/N) ";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				b.DeleteBook(b.bID);
				cout << "The book has been deleted. Press Enter to continue." << endl;
				_getch();
				main();
			}
			else if (confirm == 'N' || confirm == 'n')
			{
				_getch();
				return;
			}
			else
			{
				cout << "Please choose between 'Y' for YES or 'N' for NO.";
				_getch();
				return;
			}
			break;
		case 11:
			return;
			break;
		}
	}
}
void UpdateUser()
{

}
void LibrarianRegister(string libID) //done
{
	librarian newLib;
	page registerPage;

	registerPage.header = "===========================================\n             Librarian Register             \n===========================================\n";
	registerPage.addOption("Name");
	registerPage.addOption("Age");
	registerPage.addOption("Contact No");
	registerPage.addOption("Confirm");
	registerPage.addOption("Back");
	string tmpinput;
	bool valid;
	while (1)
	{
		switch (registerPage.prompt())
		{
		case 1:
			cout << "Name: ";
			getline(cin, newLib.libName);
			registerPage.setValue(0, newLib.libName);
			break;
		case 2:
			cout << "Age: ";
			cin >> newLib.libAge;
			registerPage.setValue(1, to_string(newLib.libAge));
			break;
		case 3:
			cout << "Contact No: ";
			cin >> tmpinput;
			if (isNumeric(tmpinput) && tmpinput.length() == 10) {
				newLib.libContNo = stoi(tmpinput);
				registerPage.setValue(2, to_string(newLib.libContNo));
			}
			else {
				cout << "Input for Contact No must be number with 10 digit";
				_getch();
			}
			break;
		case 4:
			valid = true;
			if (valid)
			{
				newLib.GenLibID();
				registerPage.setValue(4, newLib.libID);
				newLib.AddLibrarian();
				cout << "Your librarian ID is " << newLib.libID << endl;
				cout << "Registered successfully. \nPress Enter to continue." << endl;
				_getch();
				main();
			}
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}
void LibrarianMenu(librarian lib)
{
	page lmenu;
	lmenu.header = "==============================\n        Librarian Menu        \n==============================\n";
	lmenu.addOption("Borrow");
	lmenu.addOption("Return");
	lmenu.addOption("Add Book");
	lmenu.addOption("Update Book Info");
	lmenu.addOption("Search Book");
	lmenu.addOption("User Register");
	lmenu.addOption("Search User");
	lmenu.addOption("Update User Info");
	lmenu.addOption("Late Return Report");
	lmenu.addOption("Back to Main Menu");
	while (1)
	{
		switch (lmenu.prompt())
		{
		case 1:
			Borrow(lib);
			break;
		case 2:
			Return();
			break;
		case 3:
			//InsertBook(books.bID);
			break;
		case 4:
			UpdateBook();
			break;
		case 5:

			break;
		case 6:
			//UserRegister(users.UID);
			break;
		case 7:

			break;
		case 8:

			break;
		case 9:
			break;
		case 10:
			main();
			break;
		default:
			break;
		}
	}
}

void Borrow(librarian lib)
{
	page brw;
	user users;
	book books;
	issueBook issue;
	time_t timep;
	struct tm* ltm;
	time(&timep);
	ltm = gmtime(&timep);
	brw.header = "====================================\n               Borrow               \n====================================\n";
	brw.addOption("bID");
	brw.addOption("UID");
	brw.addOption("Borrow Date");
	brw.addOption("Return Date");
	brw.addOption("LibrarianID");
	brw.addOption("Borrow");
	brw.addOption("Back");
	while (1)
	{
		switch (brw.prompt())
		{
		case 1:
			cout << "Book ID: ";
			cin >> books.bID;
			//books.returnTitle(books.bTitle);
			//brw.setValue(0, books.bID);
			if (books.isValidBook(books.bTitle))
			{
				issue.bID = books.bID;
				brw.setValue(0, issue.bID);
			}
			break;
		case 2:
			cout << "User ID: ";
			cin >> users.UID;
			if (users.isValidUser(users.username)) {
				issue.UID = users.UID;
				brw.setValue(1, issue.UID);
				cout << users.username << endl;
			}
			break;
		case 3:
			//getBrwDate();
			issue.brwDate = to_string(ltm->tm_year + 1900) + '/' + to_string(ltm->tm_mon + 1) + '/' + to_string(ltm->tm_mday);
			cout << "Borrow Date(YYYY/MM/DD): " << issue.brwDate;
			brw.setValue(2, issue.brwDate);
			break;
		case 4:

			//issue.rtnDate = getRtnDate();
			issue.rtnDate = to_string(ltm->tm_year + 1900) + '/' + to_string(ltm->tm_mon + 1) + '/' + to_string(ltm->tm_mday + 14);
			cout << "Return Date(YYYY/MM/DD) : " << issue.rtnDate;
			brw.setValue(3, issue.rtnDate);
			break;
		case 5:
			issue.libID = lib.libID;
			brw.setValue(4, issue.libID);
			break;
		case 6:
				if (books.bID.empty() || users.UID.empty() || issue.brwDate.empty() || issue.rtnDate.empty() || lib.libID.empty())
				{
					cout << "Please fill in all the information. Press Enter to continue.";
					_getch();
				}
				else 
				{
						if (issue.isBookAvailable())
						{
							cout << "The book is available.";
							issue.GenCaseID();
							brw.setValue(5, issue.caseID);
							issue.borrowBook();
							issue.updateBookStatus(issue.bID);
							cout << "This book has been successfully borrowed. The caseID is " << issue.caseID << endl;
							cout << "\nPress Enter to continue." << endl;
							_getch();
						}
						else
						{
							cout << "This book is currently not available. Please insert other book." << endl;
							_getch();
						}
				}
			break;
		case 7:
			return;
			break;
		default:
			break;
		}
	}
}

void Return()
{
	//first insert bookid-output the return date-calculate fine if late return
	//return(recover book status) -record return date
	//fine payment 2 types- late return -lost book
	//insert amount of fine into table
	page rtn;
	issueBook issue;
	librarian lib;
	bool valid;
	time_t timep;
	struct tm* ltm;
	time(&timep);
	ltm = gmtime(&timep);
	rtn.header = "====================================\n               Return               \n====================================\n";
	rtn.addOption("bID");
	rtn.addOption("LibrarianID");
	rtn.addOption("Check");
	rtn.addOption("Back");
	while (1)
	{
		switch (rtn.prompt())
		{
		case 1:
			cin >> issue.bID;
			rtn.setValue(1, issue.bID);
			break;
		case 2:
			rtn.setValue(2, lib.libID);
			break;
		case 3:
			issue.checkLateRtn();
			break;
		}
	}
}

void InsertBook(string bID) //done
{
	book newBook;
	page insertPage;
	insertPage.header = "====================\n      Add Book      \n====================\n";
	insertPage.addOption("Title");
	insertPage.addOption("Author");
	insertPage.addOption("Quantity");
	insertPage.addOption("Price");
	insertPage.addOption("ISBN");
	insertPage.addOption("Status");
	insertPage.addOption("Category");
	insertPage.addOption("Language");
	insertPage.addOption("Confirm");
	insertPage.addOption("Back");
	int cat, lang;
	bool valid;
	char choice = '0';
	ostringstream formattedPrice;
	while (1)
	{
		switch (insertPage.prompt())
		{
		case 1:
			cout << "Title:	 ";
			getline(cin, newBook.bTitle);
			insertPage.setValue(0, newBook.bTitle);
			break;
		case 2:
			cout << "Author:	";
			getline(cin, newBook.Author);
			insertPage.setValue(1, newBook.Author);
			break;
		case 3:
			cout << "Quantity:	";
			newBook.bQuantity = 1;
			insertPage.setValue(2, to_string(newBook.bQuantity));
			break;
		case 4:
			cout << "Price:	 RM";
			cin >> newBook.bPrice;
			formattedPrice << fixed << setprecision(2) << newBook.bPrice;
			insertPage.setValue(3, formattedPrice.str());
			break;
		case 5:
			cout << "ISBN:	";
			cin >> newBook.ISBN;
			insertPage.setValue(4, to_string(newBook.ISBN));
			break;
		case 6:
			cout << "Status:	";
			cout << "Available" << endl;
			newBook.bStatus = "Available";
			insertPage.setValue(5, newBook.bStatus);
			break;
		case 7:
			cout << "Category: " << endl;
			cout << "1. Fiction" << endl;
			cout << "2. Non-Fiction" << endl;
			cout << "3. Reference" << endl;
			cout << "4. Magazine & Newspaper" << endl;
			cout << "5. Dictionary" << endl;
			cout << "6. Encyclopedia" << endl;
			cout << "7. Others" << endl;

			cin >> cat;
			if (cat == 1) {
				newBook.category = "Fiction";
				insertPage.setValue(6, newBook.category);
			}
			else if (cat == 2) {
				newBook.category = "Non-Fiction";
				insertPage.setValue(6, newBook.category);
			}
			else if (cat == 3) {
				newBook.category = "Reference";
				insertPage.setValue(6, newBook.category);
			}
			else if (cat == 4) {
				newBook.category = "Magazine & Newspaper";
				insertPage.setValue(6, newBook.category);
			}
			else if (cat == 5) {
				newBook.category = "Dictionary";
				insertPage.setValue(6, newBook.category);
			}
			else if (cat == 6) {
				newBook.category = "Encyclopedia";
				insertPage.setValue(6, newBook.category);
			}
			else if (cat == 7) {
				newBook.category = "Others";
				insertPage.setValue(6, newBook.category);
			}
			else
			{
				cout << "Please choose between 1-7. Press enter to continue." << endl;
				_getch();
			}
			break;
		case 8:
			cout << "Language:" << endl;
			cout << "1. English" << endl;
			cout << "2. Malay" << endl;
			cout << "3. Others" << endl;
			cin >> lang;
			if (lang == 1) {
				newBook.language = "English";
				insertPage.setValue(7, newBook.language);
			}
			else if (lang == 2) {
				newBook.language = "Malay";
				insertPage.setValue(7, newBook.language);
			}
			else if (lang == 3) {
				newBook.language = "Others";
				insertPage.setValue(7, newBook.language);
			}
			else
			{
				cout << "Please choose between 1-3. Press enter to try again." << endl;
				_getch();
			}
			break;
		case 9:
			valid = true;
			if (valid)
			{
				newBook.GenBID();
				insertPage.setValue(3, newBook.bID);
				newBook.AddBook();
				cout << newBook.bTitle << endl;
				cout << "The book ID is " << newBook.bID << "\nPress Enter to continue" << endl;
				_getch();
				InsertBook(newBook.bID);
			}
			break;
		case 10:
			return;
			break;
		}
	}
}

void UserRegister(string UID) //done
{
	user newUser;
	page registerPage;

	registerPage.header = "=========================================\n             User  Register             \n=========================================\n";
	registerPage.addOption("Name");
	registerPage.addOption("Email");
	registerPage.addOption("Contact No");
	registerPage.addOption("Address");
	registerPage.addOption("Confirm");
	registerPage.addOption("Back");
	string tmpinput;
	bool valid;
	while (1)
	{
		switch (registerPage.prompt())
		{
		case 1:
			cout << "Name: ";
			getline(cin, newUser.username);
			registerPage.setValue(0, newUser.username);
			break;
		case 2:
			cout << "Email: ";
			cin >> newUser.email;
			registerPage.setValue(1, newUser.email);
			break;
		case 3:
			cout << "Contact No: ";
			cin >> tmpinput;
			if (isNumeric(tmpinput) && tmpinput.length() == 10) {

				newUser.uContNo = stoi(tmpinput);

				registerPage.setValue(2, to_string(newUser.uContNo));
			}
			else {
				cout << "Input for Contact No must be number with 10 digit";
				_getch();
			}
			break;
		case 4:
			cout << "Address:  ";
			getline(cin, newUser.uAddress);
			registerPage.setValue(3, newUser.uAddress);
			break;
		case 5:
			valid = true;
			if (valid)
			{
				newUser.GenUID();
				registerPage.setValue(3, newUser.UID);
				newUser.AddUser();
				cout << "Your user ID is " << newUser.UID << endl;
				cout << "Registered successfully. \nPress Enter to continue." << endl;
				_getch();
				UserRegister(UID);
			}
			break;
		case 6:
			main();
			break;
		default:
			break;
		}
	}
}
void UserMenu()
{
	page umenu;
	umenu.header = "==================================\n                Menu              \n==================================\n";
	umenu.addOption("Recommended Book");
	umenu.addOption("New Arrival Stock");
	umenu.addOption("Search Book");
	umenu.addOption("Exit");
	while (1)
	{
		switch (umenu.prompt())
		{
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			main();
			break;
		}
	}
}

bool isNumeric(string input) {
	for (int i = 0; i < input.length(); i++) {
		// loop through the string and if the character at index is not digit return false
		if (!isdigit(input.at(i))) {
			return false;
		}
	}
	// if loop finishes means all is digit so return true
	return true;
}
/*
time_t time()
{
	struct tm
	{
		int tm_sec;   // seconds of minutes from 0 to 61
		int tm_min;   // minutes of hour from 0 to 59
		int tm_hour;  // hours of day from 0 to 24
		int tm_mday;  // day of month from 1 to 31
		int tm_mon;   // month of year from 0 to 11
		int tm_year;  // year since 1900
		int tm_wday;  // days since sunday
		int tm_yday;  // days since January 1st
	};
	return time();
}
/*
void getBrwDate()
{
	string brwDate;
	auto now = chrono::system_clock::now();
	time_t currentTime = chrono::system_clock::to_time_t(now);
	tm localTimeInfo;
	if (localtime_s(&localTimeInfo, &currentTime) != 0) {
		cerr << "Failed to get local time" << endl;
		return 1;
	}
	int currentYear = localTimeInfo.tm_year + 1900;
	int currentMonth = localTimeInfo.tm_mon + 1;
	int currentDay = localTimeInfo.tm_mday;
	stringstream dd;
	dd << currentYear << "/" << currentMonth << "/" << currentDay;
	brwDate = dd.str();
}
void getRtnDate()
{
	string rtnDate;
	auto now = chrono::system_clock::now();
	time_t currentTime = chrono::system_clock::to_time_t(now);
	tm localTimeInfo;

	if (localtime_s(&localTimeInfo, &currentTime) != 0) {
		cerr << "Failed to get local time" << endl;
		return 1;
	}

	int currentYear = localTimeInfo.tm_year + 1900;
	int currentMonth = localTimeInfo.tm_mon + 1;
	int currentDay = localTimeInfo.tm_mday + 14;
	stringstream dd;
	dd << currentYear << "/" << currentMonth << "/" << currentDay;
	rtnDate = dd.str();
}
*/
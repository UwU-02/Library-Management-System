#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <sstream>
#include <utility>

#include "DbConnection.h"
#include "page.h"
#include "admin.h"
#include "librarian.h"
#include "user.h"
#include "book.h"
#include "issueBook.h"
#include "finePayment.h"
#include "report.h"

using namespace std;

void MainPage();
void AdminLogin();
void AdminRegister();
void AdminMenu(admin admin);
admin UpdateAdmin(admin admin);
void LibrarianList(librarian lib);

book UpdateBook(book books);
void UpdateBookPartTwo(book books);
user UpdateUser(user users);
void UpdateUserPartTwo(user users);
void LibrarianLogin();
void LibrarianMenu(librarian lib);
librarian UpdateLibrarian(librarian lib);
void LibrarianRegister();
void UserMenu();
void UserRegister();
void InsertBook();
void Borrow(librarian lib);
void Return(librarian lib);
void fineCal(issueBook issue, finePayment payfine);
void ReportMenu();
void popularBookList();
bool isNumeric(string input);

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
				AdminMenu(Admin);
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
	bool valid;
	registerPage.header = "=========================================\n             Admin Register             \n=========================================\n";
	registerPage.addOption("Name");
	registerPage.addOption("Password");
	registerPage.addOption("Contact No");
	registerPage.addOption("Confirm");
	registerPage.addOption("Back");
	string tmpinput;
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

void AdminMenu(admin admin) //done
{
	page AMenu;
	librarian lib;
	AMenu.header = "=========================================\n          Welcome to Admin Menu          \n=========================================\n";
	AMenu.addOption("Update Admin Info");
	AMenu.addOption("Add Librarian");
	AMenu.addOption("List of Librarian");
	AMenu.addOption("Back");
	while (1)
	{
		switch (AMenu.prompt())
		{
		case 1:
			admin = UpdateAdmin(admin);
			break;
		case 2:
			LibrarianRegister();
			break;
		case 3:
			LibrarianList(lib);
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}

admin UpdateAdmin(admin Admin) 
{
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
			AdminMenu(Admin);
			break;
		case 5:
			return Admin;
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
				return Admin;
			}
			else
			{
				cout << "Please choose between 'Y' for YES or 'N' for NO.";
				_getch();
				return Admin;
			}
			break;
		default:
			break;
		}
	}
}

void LibrarianList(librarian lib)
{
	page list;
	vector<librarian> librarians;
	string displayString = "", keyword = "", sortColumn = "LibrarianID";
	int libID = -1;
	bool ascending = true;
	list.header = "=========================================\n            List of Librarian            \n=========================================\n";
	//librarians = librarians::LibrarianRecord();
	list.addOption("Search by Keyword");
	list.addOption("Sort by");
	list.addOption("Search");
	list.addOption("Back");
	while (1)
	{
		list.setValue(1, sortColumn);
		if (ascending)
			list.setValue(2, "Ascending");
		else
			list.setValue(3, "Descending");
		
		if (displayString == "")
		{
			displayString = "\nSearch Result: ";
			stringstream tmpString;
			tmpString << fixed << setprecision(2) << setw(5) << "LibrarianID" << "|" << setw(34) << "Name" << "|"
				<< setw(75) << "Age" << setw(30) << "|" << "Contact No" << setw(50) << endl;
			/*
			for (int i = 0; i < lib.size(); i++)
			{
				tmpString << setw(12) << lib[i].libID << setw(34) << "Name" 
					<< setw(75) << "Age" << setw(30) << "Contact No" << setw(50) << endl;
			}
			*/
			displayString += tmpString.str();
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
void LibrarianLogin() 
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

librarian UpdateLibrarian(librarian lib) //done
{
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
			LibrarianMenu(lib);
			return lib;
			break;
		case 5:
			return lib;
			break;
		case 6:
			cout << "Delete your account?	(Y/N) ";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				lib = temp;
				lib.DeleteLibrarian(lib.libID);
				cout << "Your account has been deleted. Press Enter to continue." << endl;
				_getch();
				main();
			}
			else if (confirm == 'N' || confirm == 'n')
			{
				_getch();
				return lib;
			}
			else
			{
				cout << "Please choose between 'Y' for YES or 'N' for NO.";
				_getch();
				return lib;
			}
			break;
		default:
			return lib;
			break;
		}
	}
}

book UpdateBook(book books)
{
	book temp = books;
	page update;
	update.header = "========================================\n        Update Book Details        \n========================================\n";
	update.addOption("Please Enter the BookID. ");
	cout << "BookID: ";
	cin >> books.bID;
	books.GetBookData(books.bID);
	UpdateBookPartTwo(books);
	return books;
}

void UpdateBookPartTwo(book books)
{
	book temp = books;
	librarian lib;
	page update;
	string tmpinput;
	char confirm = '0';
	int cat, lang;
	ostringstream formattedPrice;

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
	while (1)
	{
		update.setValue(0, temp.bTitle);
		update.setValue(1, temp.Author);
		update.setValue(2, to_string(temp.bQuantity));
		update.setValue(3, to_string(temp.bPrice));
		update.setValue(4, to_string(temp.ISBN));
		update.setValue(5, temp.bStatus);
		update.setValue(6, temp.category);
		update.setValue(7, temp.language);
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
			cout << "Quantity: ";
			cin >> temp.bQuantity;
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
			books = temp;
			books.UpdateBook();
			cout << "Updated successfully. Press Enter to continue." << endl;
			_getch();
			LibrarianMenu(lib);
			break;
		case 10:
			return;
			break;
		case 11:
			cout << "Delete this book?	(Y/N) ";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				books.DeleteBook(books.bID);
				cout << "The book has been deleted. Press Enter to continue." << endl;
				_getch();
				main();
			}
			else if (confirm == 'N' || confirm == 'n')
			{
				cout << "Press Enter to return. ";
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
		}
	}
}

user UpdateUser(user users)
{
	user temp = users;
	page update;
	update.header = "====================================\n        Update Users Details        \n====================================\n";
	update.addOption("Please Enter the UserID");
	cout << "UserID: ";
	cin >> users.UID;
	users.getUserData(users.UID);
	UpdateUserPartTwo(users);
	return users;
}

void UpdateUserPartTwo(user users)
{
	page update;
	librarian lib;
	string tmpinput;
	user temp = users;
	char confirm = '0';
	update.header = "====================================\n        Update Users Details        \n====================================\n";
	update.addOption("Username");
	update.addOption("email");
	update.addOption("Contact No");
	update.addOption("Address");
	update.addOption("Confirm");
	update.addOption("Back");
	update.addOption("Delete User");
	while (1) {
		update.setValue(0, temp.username);
		update.setValue(1, temp.email);
		update.setValue(2, to_string(temp.uContNo));
		update.setValue(3, temp.uAddress);
		switch (update.prompt())
		{
		case 1:
			cout << "New username: ";
			getline(cin, temp.username);
			update.setValue(0, temp.username);
			break;
		case 2:
			cout << "New email: ";
			cin >> temp.email;
			update.setValue(1, temp.email);
			break;
		case 3:
			cout << "New contact no: ";
			cin >> tmpinput;
			if (isNumeric(tmpinput) && tmpinput.length() == 10) {
				temp.uContNo = stoi(tmpinput);
				update.setValue(2, to_string(temp.uContNo));
			}
			else {
				cout << "Input for Contact No must be number with 10 digit";
				_getch();
			}
			break;
		case 4:
			cout << "New address: ";
			getline(cin, temp.uAddress);
			update.setValue(3, temp.uAddress);
			break;
		case 5:
			users = temp;
			users.UpdateUser();
			cout << "Updated successfully. \nPress Enter to continue." << endl;
			_getch();
			LibrarianMenu(lib);
			break;
		case 6:
			return;
			break;
		case 7:
			cout << "Delete this user's account?	(Y/N) ";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				users.DeleteUser(users.UID);
				cout << "This user account has been deleted. Press Enter to continue." << endl;
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
			return;
			break;
		}
	}
}

void LibrarianRegister() //done
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
	user users;
	book books;
	lmenu.header = "==============================\n        Librarian Menu        \n==============================\n";
	lmenu.addOption("Borrow");
	lmenu.addOption("Return");
	lmenu.addOption("Add Book");
	lmenu.addOption("Update Book Info");
	lmenu.addOption("Search Book");
	lmenu.addOption("Update Librarian Info");
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
			Return(lib);
			break;
		case 3:
			InsertBook();
			break;
		case 4:
			books = UpdateBook(books);
			break;
		case 5:

			break;
		case 6:
			lib = UpdateLibrarian(lib);
			break;
		case 7:
			UserRegister();
			break;
		case 8:

			break;
		case 9:
			users = UpdateUser(users);
			break;
		case 10:

			break;
		case 11:
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
	brw.addOption("Date");
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
			issue.brwDate = to_string(ltm->tm_year + 1900) + '-' + to_string(ltm->tm_mon + 1) + '-' + to_string(ltm->tm_mday);
			cout << "Borrow Date(YYYY-MM-DD): " << issue.brwDate;
			brw.setValue(2, issue.brwDate);
			break;
		case 4:
			issue.libID = lib.libID;
			brw.setValue(3, issue.libID);
			break;
		case 5:
			if (books.bID.empty() || users.UID.empty() || issue.brwDate.empty() || lib.libID.empty())
			{
				cout << "Please fill in all the information. Press Enter to continue.";
				_getch();
			}
			else
			{
				if (users.UserBorrowRecord())
				{
					if (issue.isBookAvailable())
					{
						//cout << "The book is available.";
						issue.GenCaseID();
						issue.borrowBook();
						issue.updateBookStatus(issue.caseID);
						issue.updateExpDate(issue.caseID);
						cout << "\nThis book has been successfully borrowed.\n The CaseID is " << issue.caseID <<".\n";
						cout << "The EXPIRY DATE is " << issue.expDate << "." << endl << endl;
						cout << "Press Enter to continue." << endl;
						_getch();
						Borrow(lib);
					}
					else
					{
						cout << "This book is currently not available. Please insert other book." << endl;
						_getch();
					}
				}
				else
				{
					cout << "This user has book have not returned. All users are only allowed to borrow a book." << endl;
					_getch();
					
				}
			}
			break;
		case 6:
			return;
			break;
		default:
			break;
		}
	}
}

void Return(librarian lib)
{
	page rtn;
	issueBook issue;
	finePayment payfine;
	time_t timep;
	struct tm* ltm;
	time(&timep);
	ltm = gmtime(&timep);
	ostringstream formattedFine;
	rtn.header = "====================================\n               Return               \n====================================\n";
	rtn.addOption("CaseID");
	rtn.addOption("Date");
	rtn.addOption("LibrarianID");
	rtn.addOption("Check");
	rtn.addOption("Back");
	while (1)
	{
		switch (rtn.prompt())
		{
		case 1:
			cout << "CaseID: ";
			cin >> issue.caseID;
			if (issue.checkCase())
			{
				rtn.setValue(0, issue.caseID);
			}
			else
			{
				cout << "This CaseID does not exists or has been returned. Please try again. " << endl;
				_getch();
			}
			break;
		case 2:
			issue.rtnDate = to_string(ltm->tm_year + 1900) + '-' + to_string(ltm->tm_mon + 1) + '-' + to_string(ltm->tm_mday);
			cout << "Return Date(YYYY-MM-DD): " << issue.rtnDate;
			rtn.setValue(1, issue.rtnDate);
			break;
		case 3:
			cout << "Librarian ID: ";
			issue.libID = lib.libID;
			rtn.setValue(2, issue.libID);
			break;
		case 4:
			if (issue.checkLateRtn())
			{
				issue.DaysCal();
				if (issue.daysCount > 0)
				{
					payfine.fine = issue.daysCount * 0.2;
					cout << "This user has late return for " << issue.daysCount << " day." << endl;
					cout << "The total fine is RM" << fixed << setprecision(2) << payfine.fine << endl << endl;
					cout << "Press Enter to continue." << endl;
					_getch();
					fineCal(issue, payfine);
				}
			}
			else
			{
				issue.returnBook();
				cout << "The book has been successfully returned. Press Enter to continue. " << endl;
				_getch();
				Return(lib);
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

void fineCal(issueBook issue, finePayment payfine)
{
	page f;
	librarian lib;
	user users;
	payfine.libID = issue.libID;
	payfine.caseID = issue.caseID;
	f.header = "===========================================\n                  Payment                  \n===========================================";
	f.addOption("Cash");
	f.addOption("Credit/Debit Card");
	f.addOption("QR Pay");
	f.addOption("Back");
	while (1)
	{
		switch (f.prompt())
		{
			case 1:
				payfine.payMethod = "Cash";
				payfine.genPayID();
				payfine.insertPay();
				issue.returnBook();
				cout << "The PaymentID is " << payfine.payID << "." << endl;
				cout << "The payment has done. Press Enter to continue.";
				_getch();
				LibrarianMenu(lib);
				break;
			case 2:
				payfine.payMethod = "Credit/Debit Card";
				payfine.genPayID();
				payfine.insertPay();
				issue.returnBook();
				cout << "The PaymentID is " << payfine.payID << "." << endl;
				cout << "The payment has done. Press Enter to continue.";
				_getch();
				LibrarianMenu(lib);
				break;
			case 3:
				payfine.payMethod = "QR Pay";
				payfine.genPayID();
				payfine.insertPay();
				issue.returnBook();
				cout << "The PaymentID is " << payfine.payID << "." << endl;
				cout << "The payment has done. Press Enter to continue.";
				_getch();
				LibrarianMenu(lib);
				break;
			case 4:
				return;
				break;
			default:
				cout << "Please insert between 1-3. Press Enter to continue. " << endl;
				_getch();
				break;
		}
	}
}

void InsertBook() //done
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
				InsertBook();
			}
			break;
		case 10:
			return;
			break;
		}
	}
}

void UserRegister() //done
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
				UserRegister();
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
			ReportMenu();
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

void ReportMenu() 
{
	page rep;
	rep.header = "========================================\n              Report Menu               \n========================================\n";
	rep.addOption("Top 10 Most Borrowed Books");
	rep.addOption("Top 10 Popular English Fiction");
	rep.addOption("Top 10 Popular Malay Fiction");
	//rep.addOption("Generate");
	rep.addOption("Back");
	while (1)
	{
		switch (rep.prompt())
		{
		case 1:
			popularBookList();
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}

void popularBookList()
{
	page rep;
	report report;
	rep.header = "======================================================\n              Top 10 Most Borrowed Books              \n======================================================\n";
	cout << setfill(' ') << '|' << left << setw(9) << "Title" << setfill(' ') << '|' << setw(200) << "Borrow Count" << setfill(' ') << '|' << setw(20) << endl;

	return;
	//report.TopTenPopularBook();
}



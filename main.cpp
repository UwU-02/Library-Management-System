#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <sstream>
#include <utility>
#include<fstream>
#include <regex>

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
using namespace sql;

void MainPage();
void AdminRegister();
void AdminLogin();
void AdminMenu(admin admin);
admin UpdateAdmin(admin admin);

void LibrarianRegister();
void LibrarianLogin();
void LibrarianList();
librarian UpdateLibrarian(librarian lib);
void LibrarianMenu(librarian lib);

void LibMenuUser();
void UserRegister();
void UserMenu();
void SearchUser();
user UpdateUser(user users);
void UpdateUserPartTwo(user users);

void LibMenuBook();
void InsertBook();
void SearchBook();
book UpdateBook(book books);
void UpdateBookPartTwo(book books);

void Borrow(librarian lib);
void Return(librarian lib);
void fineCal(issueBook issue, finePayment payfine);
void ReportMenu();
void popularBookList();
void engBookList();
void malayBookList();
void newStock();
void lateReturnRepo();
bool isNumeric(string input);
bool validDate(const string& date);

int main()
{
	system("color 0B");
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
				cout << "______________________________________________________\n\n";
				cout << "\tYour admin ID is " << newAcc.adminID << endl;
				cout << "______________________________________________________\n";
				cout << "\nRegistered successfully. \nPress Enter to continue." << endl;
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
			LibrarianList();
			break;
		case 4:
			main();
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
				Admin.updateLastRow();
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
				cout << "______________________________________________________\n\n";
				cout << "\tYour librarian ID is " << newLib.libID << endl;
				cout << "______________________________________________________\n";
				cout << "\nRegistered successfully. \nPress Enter to continue." << endl;
				_getch();
				return;
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

void LibrarianList()
{
	page list;
	vector <librarian> lib;
	list.addOption("Back");
	lib = librarian::SearchLibrarian();

	while (1)
	{
		stringstream ss;
		ss << "=========================================================================================================\n					   List of Librarian\n=========================================================================================================\n";

		ss << endl << setfill(' ') << '|' << left << setw(15) << "     LibrarianID      " << setfill(' ') << '|' << setw(20) << "        Name               " << setfill(' ') << '|' << setw(10) << "         Age       " << setfill(' ') << '|' << setw(25) << "          Contact No            " << setfill(' ') << '|' << endl;

		for (int i = 0; i < lib.size(); i++)
		{
			ss << endl << setfill(' ') << '|' << left << "       " << setw(15) << lib[i].libID << setfill(' ') << '|' << "     " << setw(22) << lib[i].libName << setfill(' ') << '|' << setw(10) << " " << lib[i].libAge << "       " << setfill(' ') << '|' << "         " << setw(23) << lib[i].libContNo << setfill(' ') << '|' << endl;
		}

		list.header = ss.str();

		switch (list.prompt())
		{
		case 1:
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
				lib.updateLastRow();
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

void LibrarianMenu(librarian lib)
{
	page lmenu;
	user users;
	book books;
	lmenu.header = "==============================\n        Librarian Menu        \n==============================\n";
	lmenu.addOption("Borrow");
	lmenu.addOption("Return");
	lmenu.addOption("Manage Book");
	lmenu.addOption("Manage User");
	lmenu.addOption("Late Return Report");
	lmenu.addOption("Update Librarian Info");
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
			LibMenuBook();
			break;
		case 4:
			LibMenuUser();
			break;
		case 5:
			lateReturnRepo();
			break;
		case 6:
			lib = UpdateLibrarian(lib);
			break;
		case 7:
			main();
			break;
		default:
			break;
		}
	}
}

void LibMenuUser()
{
	page lmenu;
	user users;
	lmenu.header = "==============================\n        Librarian Menu        \n==============================\n";
	lmenu.addOption("User Register");
	lmenu.addOption("Update User Info");
	lmenu.addOption("Search User");
	lmenu.addOption("Back");
	while (1)
	{
		switch (lmenu.prompt())
		{
		case 1:
			UserRegister();
			break;
		case 2:
			users = UpdateUser(users);			
			break;
		case 3:
			SearchUser();
			break;
		case 4:
			return;
			break;
		default:
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
				cout << "______________________________________________________\n\n";
				cout << "\tThe user ID is " << newUser.UID << endl;
				cout << "______________________________________________________\n\n";
				cout << "Registered successfully. \nPress Enter to continue." << endl;
				_getch();
				UserRegister();
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

void UserMenu()
{
	page umenu;
	umenu.header = "==================================\n                Menu              \n==================================\n";
	umenu.addOption("Recommended Book");
	umenu.addOption("New Arrival Stock");
	umenu.addOption("Search Book");
	umenu.addOption("Back");
	while (1)
	{
		switch (umenu.prompt())
		{
		case 1:
			ReportMenu();
			break;
		case 2:
			newStock();
			break;
		case 3:
			SearchBook();
			break;
		case 4:
			main();
			break;
		}
	}
}

void SearchUser()
{
	page search;
	vector<user> users;
	string keyword = "";

	search.addOption("Search by User Name");
	search.addOption("Search");
	search.addOption("Back");
	while (1)
	{
		stringstream ss;
		ss << "==============================================================================================================\n                                                   Search User\n==============================================================================================================\n";

		ss << endl << setfill(' ') << '|' << left << setw(10) << "UserID" << setfill(' ') << '|' << setw(40) << "   User Name" << setfill(' ') << '|' << setw(15) << "   Contact No" << setfill(' ') << '|' << setw(40) << "   Address" << setfill(' ') << '|' << endl;

		for (int i = 0; i < users.size(); i++)
		{
			ss << endl << setfill(' ') << '|' << left << setw(10) << users[i].UID << setfill(' ') << '|' << setw(40) << users[i].username << setfill(' ') << '|' << setw(15) << users[i].uContNo << setfill(' ') << '|' << setw(40) << users[i].uAddress << setfill(' ') << '|' << endl;
		}

		search.header = ss.str();

		switch (search.prompt())
		{
		case 1:
			cout << "User Name: ";
			cin >> keyword;
			search.setValue(0, keyword);
			break;
		case 2:
			users.clear();
			users = user::SearchUser(keyword);
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}
	return;
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
				users.updateLastRow();
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

void LibMenuBook()
{
	page lmenu;
	book books;
	lmenu.header = "==============================\n        Librarian Menu        \n==============================\n";
	lmenu.addOption("Add Book");
	lmenu.addOption("Update Book Info");
	lmenu.addOption("Search Book");
	lmenu.addOption("Back");
	while (1)
	{
		switch (lmenu.prompt())
		{
		case 1:
			InsertBook();
			break;
		case 2:
			books = UpdateBook(books);
			break;
		case 3:
			SearchBook();
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}

void InsertBook() //done
{
	book newBook;
	page insertPage;
	time_t timep;
	struct tm* ltm;
	time(&timep);
	ltm = gmtime(&timep);
	insertPage.header = "====================\n      Add Book      \n====================\n";
	insertPage.addOption("Title");
	insertPage.addOption("Author");
	insertPage.addOption("Quantity");
	insertPage.addOption("Price");
	insertPage.addOption("ISBN");
	insertPage.addOption("Status");
	insertPage.addOption("Category");
	insertPage.addOption("Language");
	insertPage.addOption("Date");
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
			newBook.insertDate = to_string(ltm->tm_year + 1900) + '-' + to_string(ltm->tm_mon + 1) + '-' + to_string(ltm->tm_mday);
			cout << "Borrow Date(YYYY-MM-DD): " << newBook.insertDate;
			insertPage.setValue(8, newBook.insertDate);
			break;
		case 10:
			valid = true;
			if (valid)
			{
				newBook.GenBID();
				insertPage.setValue(9, newBook.bID);
				newBook.AddBook();
				cout << "______________________________________________________\n\n";
				cout << "\tThe book ID is " << newBook.bID << endl;
				cout << "______________________________________________________\n";
				cout << "\n\nPress Enter to Continue.";
				_getch();
				InsertBook();
			}
			break;
		case 11:
			return;
			break;
		}
	}
}

void SearchBook()
{
	page search;
	vector<book> books;
	string keyword = "";
	int choice = 0, stat=0, cat = 0, lang = 0;

	search.addOption("Search by: ");
	search.addOption("Search");
	search.addOption("Back");
	while (1)
	{
		stringstream ss;
		ss << "=========================================================================================================\n                                           Search Book                                         \n=========================================================================================================\n";

		ss << endl << setfill(' ') << '|' << left << setw(10) << "BookID" << setfill(' ') << '|' << setw(50) << "   Title" << setfill(' ') << '|' << setw(30) << "  Author" << setfill(' ') << '|' << setw(10) << "   Status" << setfill(' ') << '|' << endl;

		for (int i = 0; i < books.size(); i++)
		{
			ss << endl << setfill(' ') << '|' << left << setw(10) << books[i].bID << setfill(' ') << '|' << setw(50) << books[i].bTitle << setfill(' ') << '|' << setw(30) << books[i].Author<< setfill(' ') << '|' << setw(10) << books[i].bStatus << setfill(' ') << '|' << endl;
		}

		search.header = ss.str();

		switch (search.prompt())
		{
		case 1:
			cout << "1. Title" <<endl;
			cout << "2. Author" << endl;
			cout << "3. Book Status" << endl;
			cout << "4. Category" << endl;
			cout << "5. Language" << endl;
			cin >> choice;
			if (choice == 1)
			{
				cout << "\nKeyword of the Book Title: ";
				cin>> keyword; 
				search.setValue(0, keyword);
			}
			else if (choice == 2)
			{
				cout << "\nAuthor's Name: ";
				cin >> keyword;
				search.setValue(0, keyword);
			}
			else if (choice == 3)
			{
				cout << "\nBook Status: " << endl;
				cout << "1. Available Books" << endl;
				cout << "2. Borrowing Books" << endl;
				cin >> stat;
				if (stat == 1)
				{
					keyword = "Available";
					search.setValue(0, keyword);
				}
				else if (stat == 2)
				{
					keyword = "Borrowing";
					search.setValue(0, keyword);
				}
				else
				{
					cout << "Please choose between 1 & 2. Press Enter to try again.";
					_getch();
				}
			}
			else if (choice == 4)
			{
				cout << "\nCategory: " << endl;
				cout << "1. Fiction" << endl;
				cout << "2. Non-Fiction" << endl;
				cout << "3. Reference" << endl;
				cout << "4. Magazine & Newspaper" << endl;
				cout << "5. Dictionary" << endl;
				cout << "6. Encyclopedia" << endl;
				cout << "7. Others" << endl;
				cin >> cat;
				if (cat == 1)
				{
					keyword = "Fiction";
					search.setValue(0, keyword);
				}
				else if (cat == 2)
				{
					keyword = "Non-Fiction";
					search.setValue(0, keyword);
				}
				else if (cat == 3)
				{
					keyword = "Reference";
					search.setValue(0, keyword);
				}
				else if (cat == 4)
				{
					keyword = "Magazine & Newspaper";
					search.setValue(0, keyword);
				}
				else if (cat == 5)
				{
					keyword = "Dictionary";
					search.setValue(0, keyword);
				}
				else if (cat == 6)
				{
					keyword = "Encyclopedia";
					search.setValue(0, keyword);
				}
				else if (cat == 7)
				{
					keyword = "Others";
					search.setValue(0, keyword);
				}
				else
				{
					cout << "Please choose between 1-7. Press Enter to try again.";
					_getch();
				}

			}
			else if (choice == 5)
			{
				cout << "\nLanguage:" << endl;
				cout << "1. English" << endl;
				cout << "2. Malay" << endl;
				cout << "3. Others" << endl;
				cin >> lang;
				if (lang == 1)
				{
					keyword = "English";
					search.setValue(0, keyword);
				}
				else if (lang == 2)
				{
					keyword = "Malay";
					search.setValue(0, keyword);
				}
				else if (lang == 3)
				{
					keyword = "Others";
					search.setValue(0, keyword);
				}
				else
				{
					cout << "Please choose between 1-3. Press Enter to try again.";
					_getch();
				}
			}
			else
			{
				cout << "\nPlease choose between 1-5. Press Enter to try again.";
				_getch();
			}
			break;
		case 2:
			books.clear();
			books = book::SearchBook(keyword, choice);
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}
	return;
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
				books.updateLastRow();
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
	brw.addOption("BookID");
	brw.addOption("UserID");
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
						cout << "___________________________________________________________\n";
						cout << "\n\tThe CaseID is " << issue.caseID <<".\n";
						cout << "\tThe EXPIRY DATE is " << issue.expDate << "." << endl;
						cout << "___________________________________________________________\n\n";
						cout << "This book has been successfully borrowed. Press Enter to continue." << endl;
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
			LibrarianMenu(lib);
			break;
		default:
			break;
		}
	}
}

void Return(librarian lib)
{
	page rtn;
	int daysCount;
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
			LibrarianMenu(lib);
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
	payfine.payDate = issue.rtnDate;
	payfine.UID = issue.UID;
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
			engBookList();
			break;
		case 3:
			malayBookList();
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
	vector <report> result;
	rep.addOption("Date");
	rep.addOption("Go");
	rep.addOption("Back");
	string brwDate;

	while (1)
	{
		stringstream ss;
		ss << "===========================================================================================\n                                Top 10 Most Popular Books                                  \n===========================================================================================\n";

		ss <<endl<< setfill(' ') << '|' << left << setw(70) << "Title" << setfill(' ') << '|' << setw(15) << "   Borrow Count   " << setfill(' ') << '|'<< endl;

		for (int i = 0; i < result.size(); i++)
		{
			ss<< endl << setfill(' ') << '|' << left << setw(70) << result[i].bTitle << setfill(' ') << '|' << "         " << setw(9) << result[i].issueCount << setfill(' ') << '|' << endl;
		}

		rep.header = ss.str();

		switch (rep.prompt())
		{
		case 1:
			cout << "Insert Date: ";
			cin >> brwDate;
			if (!validDate(brwDate))
			{
				cout << "Invalid date. Please try again. ";
				_getch();
			}
			else
			{
				rep.setValue(0, brwDate);
			}
			break;
		case 2:
			result.clear();
			result = report::TopPopularBook(brwDate);
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}

	return;
}

void engBookList()
{
	page rep;
	vector <report> result;
	rep.addOption("Date");
	rep.addOption("Go");
	rep.addOption("Back");
	string brwDate;

	while (1)
	{
		stringstream ss;
		ss << "===========================================================================================\n                          Top 10 Most Popular English Literature                           \n===========================================================================================\n";

		ss << endl << setfill(' ') << '|' << left << setw(70) << "Title" << setfill(' ') << '|' << setw(15) << "   Borrow Count   " << setfill(' ') << '|' << endl;

		for (int i = 0; i < result.size(); i++)
		{
			ss << endl << setfill(' ') << '|' << left << setw(70) << result[i].bTitle << setfill(' ') << '|' << "         " << setw(9) << result[i].issueCount << setfill(' ') << '|' << endl;
		}

		rep.header = ss.str();

		switch (rep.prompt())
		{
		case 1:
			cout << "Insert Date (YYYY-MM-DD): ";
			cin >> brwDate;
			if (!validDate(brwDate))
			{
				cout << "Invalid date. Please try again. ";
				_getch();
			}
			else
			{
				rep.setValue(0, brwDate);
			}
			break;
		case 2:
			result.clear();
			result = report::TopTenEngFic(brwDate);
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}

	return;
}

void malayBookList()
{
	page rep;
	vector <report> result;
	rep.addOption("Date");
	rep.addOption("Go");
	rep.addOption("Back");
	string keyword;

	while (1)
	{
		stringstream ss;
		ss << "===========================================================================================\n                           Top 10 Most Popular Malay Literature                            \n===========================================================================================\n";
		ss << endl << setfill(' ') << '|' << left << setw(70) << "Title" << setfill(' ') << '|' << setw(15) << "   Borrow Count   " << setfill(' ') << '|' << endl;

		for (int i = 0; i < result.size(); i++)
		{
			ss << endl << setfill(' ') << '|' << left << setw(70) << result[i].bTitle << setfill(' ') << '|' << "         " << setw(9) << result[i].issueCount << setfill(' ') << '|' << endl;
		}

		rep.header = ss.str();

		switch (rep.prompt())
		{
		case 1:
			cout << "Insert Date (YYYY-MM-DD): ";
			cin >> keyword;
			if (!validDate(keyword))
			{
				cout << "Invalid date. Please try again. ";
				_getch();
			}
			else
			{
				rep.setValue(0, keyword);
			}
			break;
		case 2:
			result.clear();
			result = report::TopTenMalayFic(keyword);
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}

	return;
}

void newStock()
{
	page rep;
	vector <book> result;
	string insertDate;
	string keyword = "";
	rep.addOption("Date");
	rep.addOption("Go");
	rep.addOption("Back");

	while(1)
	{
		stringstream ss;
		ss << "===================================================================================\n                                    New Books                                      \n===================================================================================\n";

		ss << endl << setfill(' ') << '|' << left << setw(10) << "BookID" << setfill(' ') << '|' << setw(69) << "          Title" << setfill(' ') << '|' << endl;

		for (int i = 0; i < result.size(); i++)
		{
			ss << endl << setfill(' ') << '|' << left << setw(10) << result[i].bID << setfill(' ') << '|' << "         " << setw(60) << result[i].bTitle << setfill(' ') << '|' << endl;
		}

		rep.header = ss.str();


		switch (rep.prompt())
		{
		case 1:
			cout << "Insert Date (YYYY-MM-DD): ";
			cin >> keyword;
			if (!validDate(keyword))
			{
				cout << "Invalid date. Please try again. ";
				_getch();
			}
			else
			{
				rep.setValue(0, keyword);
			}
			break;
		case 2:
			result.clear();
			result = book::NewStock(keyword);
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}
	return;
}

void lateReturnRepo()
{
	page rep;
	vector <finePayment> result;
	string payDate="";
	double totalFine = 0;
	ofstream outputFile("Total_Fine_Report.txt");
	rep.addOption("Checkout Date");
	rep.addOption("Go");
	rep.addOption("Back");

	while (1)
	{
		stringstream ss;
		ss << "===================================================================================\n                                   Late Return                                     \n===================================================================================\n";

		ss << endl << setfill(' ') << '|' << left << setw(15) << "     PaymentID      " << setfill(' ') << '|' << setw(10) << "    UserID      " << setfill(' ') << '|' << setw(10) << "     Fine      " << setfill(' ') << '|' << setw(25) << "     Payment Method         " << setfill(' ') << '|' << endl;

		for (int i = 0; i < result.size(); i++)
		{
			ss << endl << setfill(' ') << '|' << left << "     " << setw(15) << result[i].payID << setfill(' ') << '|' << "    " << setw(12) << result[i].UID << setfill(' ') << '|' << setw(10) << "     RM" << result[i].fine << "  " << setfill(' ') << '|' << "     " << setw(23) << result[i].payMethod << setfill(' ') << '|' << endl;
			totalFine += result[i].fine;
		}

		ss << "\n\n_____________________________________________________________________________________" << endl << endl;
		ss << "Total Fine: RM " << setprecision(2) << totalFine << endl;
		ss << "_____________________________________________________________________________________" << endl;
		rep.header = ss.str();
		
		switch (rep.prompt())
		{
		case 1:
			cout << "Checkout Date (YYYY-MM-DD): ";
			cin >> payDate;
			if (!validDate(payDate))
			{
				cout << "Invalid date. Please try again. ";
				_getch();
			}
			else 
			{
				rep.setValue(0, payDate);
			}
			break;
		case 2:
			result.clear();
			result = finePayment::LateReturnReport(payDate);
			if (outputFile.is_open())
			{
				ss.str(""); // Clear the stringstream
				ss.clear();
				ss << "===================================================================================\n                                   Late Return                                     \n===================================================================================\n";

				ss << endl << setfill(' ') << '|' << left << setw(15) << "     PaymentID      " << setfill(' ') << '|' << setw(10) << "    UserID      " << setfill(' ') << '|' << setw(10) << "     Fine      " << setfill(' ') << '|' << setw(25) << "     Payment Method         " << setfill(' ') << '|' << endl;

				for (int i = 0; i < result.size(); i++)
				{
					ss << endl << setfill(' ') << '|' << left << "     " << setw(15) << result[i].payID << setfill(' ') << '|' << "    " << setw(12) << result[i].UID << setfill(' ') << '|' << setw(10) << "     RM" << result[i].fine << "  " << setfill(' ') << '|' << "     " << setw(23) << result[i].payMethod << setfill(' ') << '|' << endl;

				}

				ss << "\n\n_____________________________________________________________________________________" << endl << endl;
				ss << "Total Fine: RM " << setprecision(2) << totalFine << endl;
				ss << "Date: " << payDate << endl;
				ss << "_____________________________________________________________________________________" << endl;

				outputFile << ss.str();
				outputFile.close();
			}
			else 
			{
				cerr << "Error opening text file.\n";
			}

			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}

	return;
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

bool validDate(const string& date)
{
	regex datePattern("^\\d{4}[/-]\\d{2}[/-]\\d{2}$"); 

	if (!regex_match(date, datePattern)) {
		return false;
	}

	tm tmDate = {};
	stringstream ss(date);
	ss >> get_time(&tmDate, "%Y/%m/%d");

	if (ss.fail()) {
		ss.clear();
		ss.str(date);
		ss >> get_time(&tmDate, "%Y-%m-%d");
		if (ss.fail()) {
			return false;
		}
	}

	return mktime(&tmDate) != -1;
}
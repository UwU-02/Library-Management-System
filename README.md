# 📚 Library Management System (C++)

This is a simple **Library Management System** written in C++ that provides basic **CRUD (Create, Read, Update, Delete)** functionalities. Additionally, it includes the ability to generate **fine receipts** for overdue books.

## 🧩 Features

- 📥 Add new books to the system
- 🔍 View all books or search by title/author
- ✏️ Update book information
- ❌ Delete books from the library
- 👤 Manage borrower records
- 📄 Generate fine receipts for overdue books

## 💡 How Fine Calculation Works

The system tracks the due date of borrowed books and calculates fines based on the number of days overdue. For example:
- Fine rate: RM0.20 per day
- If a book is 5 days overdue, the fine is **RM1.00**

A receipt is generated and printed in the console with the following details:
- PaymentID
- UserID
- Payment Method
- Date
- Total fine

## 🛠 Technologies Used

- **Language**: C++
- **Console Application**: User interacts through a menu-driven terminal interface

## 📝 Notes

- This project is intended for beginner-level learning and practice with file handling and object-oriented programming in C++.
- No external libraries are used.

## 📄 License

This project is open-source and free to use for educational purposes.

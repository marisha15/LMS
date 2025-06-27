# LMS
---Library Management System---
By Marisha Thorat

1.Description:
This Library Management System, implemented in C++, offers an efficient solution for managing library resources and user interactions. The entire system is encapsulated within a single file, mylib1.cpp, and provides core functionality including book management, user account tracking, and transaction history. It facilitates seamless borrowing, returning, and reserving of books, while keeping real-time records of user activities such as borrowed books, overdue days, and applicable fines.

2.Core Features:

a.User Authentication & Management:
Users log in with their unique User ID, with their credentials securely stored in user.csv.
Three distinct user roles are supported- Student, Faculty, and Librarian, each with role-specific permissions.

b.Book Operations:
Manage books by adding, editing, deleting, or viewing their details.
Users can borrow, return, and reserve books.

c.Account & Transaction Tracking:
Each user’s activity is tracked with a dedicated account file (e.g., 201.csv), which records borrow history, overdue items, and fines.
A central user.csv file serves as the repository for all user-related data, such as borrowed books, overdue counts, and fine details.

3.System Architecture:
mylib1.cpp:
This is the core file containing all the necessary logic for the Library Management System. It integrates all components, from user and book management to transaction handling and data synchronization.

Data Files:
user.csv: A comprehensive file containing user details — such as ID, name, role, borrowed items, overdue records, and fines.
books.csv: A list of all books in the library’s collection, including availability and status.
<UserID>.csv: Individual files created for each user, storing their borrowing history and fine records.

Note:
Temporary Files:
The temp.csv file is used internally for secure operations, such as data updates or deletions.
Dynamic Account Files:
Account files like 201.csv are generated on-the-fly during a user’s first interaction with the system, making each user’s transaction history unique.

4.System Requirements:
A C++11 or later compatible compiler (e.g., g++, clang++) is required.
Standard libraries <iostream>, <fstream>, <sstream>, <vector>, and others.
All CSV files (user.csv, books.csv) must be in the same directory as the compiled program.


5.Build & Execution:
Compilation:
To compile the system, use the following command

g++ -o run1 mylib1.cpp

Execution:
To start the application, execute

./run1

6.Operational Workflow:
User Login:
    The program prompts the user to enter their user ID and username, with the latter being stored securely in the user.csv file.

Role-Based Features:
    Students/Faculty: Access a menu for browsing books, borrowing, returning, reserving, and managing fines.
    Librarians: Manage book entries and update user records for efficient library operation.

Data Syncing:
    After each action, whether it’s borrowing a book or updating an account, the system ensures that all records in user.csv and individual user files are synchronized, maintaining consistency across the entire system.


//comments-while choosing option 2 for adding book in faculty menu, please enter "2 " instead of "2".

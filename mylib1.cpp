#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <sstream>
using namespace std;



//classes code<3



class Collection {
private:
    string data_file = "books.csv";

public:
    string getDataFile() const { return data_file; }

    void loadPublications() {
        ifstream input(data_file);
        if (!input.is_open()) {
            cout << "error :'< could not open " << data_file << "\n";
            return;
        }
        string record;
        while (getline(input, record)) {
            if (record.empty()) continue;
            stringstream parser(record);
            string isbn, title, author, publisher, yearStr, statusStr, issuedTo, issuedDate;
            getline(parser, isbn, ',');
            getline(parser, title, ',');
            getline(parser, author, ',');
            getline(parser, publisher, ',');
            getline(parser, yearStr, ',');
            getline(parser, statusStr, ',');
            getline(parser, issuedTo, ',');
            getline(parser, issuedDate, ',');
        }
        input.close();
    }
    void showAll() {
        ifstream input(data_file);
        if (!input.is_open()) {
            cout << "error :'< could not open " << data_file << "\n";
            return;
        }
        cout << "\nlist of books <3\n";
        string record;
        int counter = 0;
        while (getline(input, record)) {
            if (record.empty()) continue;
            stringstream parser(record);
            string isbn, title, author, publisher, yearStr, statusStr, issuedTo, issuedDate;
            int year, status;
            getline(parser, isbn, ',');
            getline(parser, title, ',');
            getline(parser, author, ',');
            getline(parser, publisher, ',');
            getline(parser, yearStr, ',');
            getline(parser, statusStr, ',');
            getline(parser, issuedTo, ',');
            getline(parser, issuedDate, ',');
            try {
                year = stoi(yearStr);
                status = stoi(statusStr);
            } catch (...) {
                cerr << "error :'< could not convert numeric fields for " << title << "\n";
                continue;
            }
            counter++;
            cout << "\nbook " << counter << "\n";
            cout << "ISBN       : " << isbn << "\n";
            cout << "title      : " << title << "\n";
            cout << "author     : " << author << "\n";
            cout << "publisher  : " << publisher << "\n";
            cout << "year       : " << year << "\n";
            cout << "status     : " << (status == 1 ? "available" : (status == 0 ? "borrowed" : "reserved")) << "\n";
            if (status == 0) {
                cout << "issued to  : " << issuedTo << "\n";
                cout << "issued date: " << issuedDate << "\n";
            }
        }
        input.close();
    }
    void addItem() {
        string isbn, title, author, publisher;
        int year, status;
        cin.ignore();
        cout << "enter ISBN: ";
        getline(cin, isbn);
        cout << "enter title: ";
        getline(cin, title);
        cout << "enter author: ";
        getline(cin, author);
        cout << "enter publisher: ";
        getline(cin, publisher);
        cout << "enter year: ";
        cin >> year;
        cout << "enter status>> borrowed(0), available(1), reserved(2): ";
        cin >> status;
        ofstream output(data_file, ios::app);
        if (!output) {
            cerr << "error :'< could not open " << data_file << "\n";
            return;
        }
        output << isbn << "," << title << "," << author << "," << publisher << "," << year << "," << status << ",-,-\n";
        output.close();
        cout << "successfully added <3\n";
    }   
    void modifyStatus(const string& isbn, int newStatus, const string& issuedTo, const string& issuedDate) { 
        vector<string> records;
        ifstream input(data_file);
        if (!input) {
            cerr << "error :'< could not open " << data_file << " to update\n";
            return;
        }        
        string record;
        while (getline(input, record)) {
            if(record.empty()) continue;
            stringstream parser(record);
            string bookIsbn, title, author, publisher, yearStr, statusStr, currentIssuedTo, currentIssuedDate;
            getline(parser, bookIsbn, ',');
            getline(parser, title, ',');
            getline(parser, author, ',');
            getline(parser, publisher, ',');
            getline(parser, yearStr, ',');
            getline(parser, statusStr, ',');
            getline(parser, currentIssuedTo, ',');
            getline(parser, currentIssuedDate, ',');        
            if (bookIsbn == isbn) {
                stringstream updated;
                updated << isbn << "," << title << "," << author << "," << publisher << "," 
                       << yearStr << "," << newStatus << "," << issuedTo << "," << issuedDate;
                records.push_back(updated.str());
            } else {
                records.push_back(record);
            }
        }
        input.close();        
        ofstream output(data_file);
        for (const auto& updated : records) {
            output << updated << "\n";
        }
        output.close();
    }    
    void updateItem() {
        cout << "enter the ISBN of the book you want to update: ";
        string searchISBN;
        getline(cin, searchISBN);
        vector<string> records;
        bool found = false;
        ifstream input(data_file);
        if (!input.is_open()) {
            cerr << "error :;< could not open " << data_file << "\n";
            return;
        }
        string record;
        while (getline(input, record)) {
            if(record.empty()) continue;
            stringstream parser(record);
            string isbn, title, author, publisher, yearStr, statusStr, issuedTo, issuedDate;            
            getline(parser, isbn, ',');
            getline(parser, title, ',');
            getline(parser, author, ',');
            getline(parser, publisher, ',');
            getline(parser, yearStr, ',');
            getline(parser, statusStr, ',');
            getline(parser, issuedTo, ',');
            getline(parser, issuedDate, ',');           
            if (isbn == searchISBN) {
                found = true;
                cout << "enter new title: ";
                getline(cin, title);
                cout << "enter new author: ";
                getline(cin, author);
                cout << "enter new publisher: ";
                getline(cin, publisher);
                cout << "enter new year: ";
                cin >> yearStr;
                cout << "enter new status borrowed(0), available(1), reserved(2): ";
                cin >> statusStr;
                cin.ignore();
            }
            stringstream updated;
            updated << isbn << "," << title << "," << author << "," << publisher << "," << yearStr << ","
                   << statusStr << "," << issuedTo << "," << issuedDate;
            records.push_back(updated.str());
        }
        input.close();
        ofstream output(data_file);
        for (const string& updated : records) {
            output << updated << "\n";
        }
        output.close();
        if (found) {
            cout << "success <3\n";
        } else {
            cout << "could not find the book with ISBN " << searchISBN << "\n";
        }
    }    
    void removeItem() {
        cout << "to remove, enter ISBN of the book: ";
        string searchISBN;        
        getline(cin, searchISBN);
        vector<string> records;
        bool found = false;
        ifstream input(data_file);
        if (!input.is_open()) {
            cerr << "error :'< could not open " << data_file << "\n";
            return;
        }
        string record;
        while (getline(input, record)) {
            if(record.empty()) continue;
            stringstream parser(record);
            string isbn, title, author, publisher, yearStr, statusStr, issuedTo, issuedDate;
            int year,status;
            getline(parser, isbn, ',');
            getline(parser, title, ',');
            getline(parser, author, ',');
            getline(parser, publisher, ',');
            getline(parser, yearStr, ',');
            getline(parser, statusStr, ',');
            getline(parser, issuedTo, ',');
            getline(parser, issuedDate, ',');
            year = stoi(yearStr);
            status = stoi(statusStr);
            if (isbn == searchISBN) {
                found = true;
                cout << "book '" << title << "' removed from library\n";
                continue;
            }
            records.push_back(record);
        }
        input.close();
        ofstream output(data_file);
        for (const string& updated : records) {
            output << updated << "\n";
        }
        output.close();
        if (!found) {
            cout << "could not find the book with ISBN " << searchISBN << "\n";
        }
    }
};
class Publication {
public:
    string title, author, publisher, ISBN;
    int year;
    int status;
    string issuedto;
    string issuedate;
};
class MemberAccount {
private:
    string memberID;
    string accountType;

    struct LoanRecord {
        string itemCode;
        time_t checkoutDate;
        time_t dueDate;
        time_t returnDate;
    };
    vector<LoanRecord> activeLoans;
    vector<LoanRecord> loanHistory;
    vector<LoanRecord> heldItems;
    int overdueFee;
public:
    MemberAccount(string id, string type) : memberID(id), accountType(type), overdueFee(0) {
        loadRecords();
        calculateFees();
    }    
    void checkoutItem(string code, Collection& collection) {
        calculateFees();
        bool available = false;
        if (overdueFee > 0) {
            cout << "book cannot be borrowed before paying the due amount " << overdueFee << "\n";
            return;
        }
        ifstream input(collection.getDataFile());
        if (!input) {
            cerr << "error :'< could not open " << collection.getDataFile() << "\n";
            return;
        }    
        string record;
        while (getline(input, record)) {
            if (record.empty()) continue;    
            stringstream parser(record);
            string isbn, title, author, publisher, yearStr, statusStr, issuedUser, issuedDate;
            getline(parser, isbn, ',');
            getline(parser, title, ',');
            getline(parser, author, ',');
            getline(parser, publisher, ',');
            getline(parser, yearStr, ',');
            getline(parser, statusStr, ',');
            getline(parser, issuedUser, ',');
            getline(parser, issuedDate, ',');    
            if (isbn == code) {
                if (stoi(statusStr) == 1) {
                    available = true;
                }
                break;
            }
        }
        input.close();
        if (!available) {
            cout << "the book with ISBN " << code << " is already borrowed by someone\n";
            return;
        }
        int maxBooks = (accountType == "Student") ? 3 : 5;
        if (activeLoans.size() >= maxBooks) {
            cout << "borrowing limit reached >>" << maxBooks << " books\n";
            return;
        }
        time_t now = time(0);
        for (const auto& book : activeLoans) {
            double overdueDays = difftime(now, book.dueDate) / 86400; 
            if (overdueDays > 60 && accountType == "Faculty") {
                cout << "you have an overdue book for more than 60 days, return it before borrowing new books\n";
                return;
            }
        }        
        time_t due = now + ((accountType == "Student") ? (15 * 86400) : (30 * 86400));        
        LoanRecord newBook = {code, now, due, 0};
        activeLoans.push_back(newBook);
        string currentDate = string(ctime(&now));
        collection.modifyStatus(code,0,memberID,currentDate);        
        cout << "book " << code << " borrowed with due date: " << ctime(&due);
        saveRecords();
    }
    void returnItem(string code, Collection& collection) {
        time_t now = time(0);
        for (auto it = activeLoans.begin(); it != activeLoans.end(); ++it) {
            if (it->itemCode == code) {
                int overdueDays = (now > it->dueDate) ? (now - it->dueDate) / 86400 : 0;
                if (accountType == "Student" && overdueDays > 0) {
                    overdueFee += overdueDays * 10;
                }
                it->returnDate = now;
                loanHistory.push_back(*it);
                activeLoans.erase(it);
                string currentDate = string(ctime(&now));
                collection.modifyStatus(code,1,"-","-");
                cout << "book " << code << " returned with overdue: " << overdueDays 
                     << " days. the current fine is Rs " << overdueFee << "\n";
                saveRecords();
                return;
            }
        }
        cout << "book " << code << " not found in borrowed list\n";
    }    
    void holdItem(Collection& collection, string code) {
        time_t now = time(0); 
        string currentDate = string(ctime(&now));    
        int bookStatus = -1; 
        string issuedTo = "-";    
        ifstream input(collection.getDataFile());
        if (!input) {
            cerr << "error :'< could not open " << collection.getDataFile() << "\n";
            return;
        }    
        string record;
        while (getline(input, record)) {
            if (record.empty()) continue;    
            stringstream parser(record);
            string isbn, title, author, publisher, yearStr, statusStr, issuedUser, issuedDate;
            getline(parser, isbn, ',');
            getline(parser, title, ',');
            getline(parser, author, ',');
            getline(parser, publisher, ',');
            getline(parser, yearStr, ',');
            getline(parser, statusStr, ',');
            getline(parser, issuedUser, ',');
            getline(parser, issuedDate, ',');    
            if (isbn == code) {
                bookStatus = stoi(statusStr);
                issuedTo = issuedUser;
                break;
            }
        }
        input.close();    
        if (bookStatus == -1) {
            cout << "could not find book with ISBN " << code << "\n";
            return;
        }
        if (bookStatus == 1) {
            cout << "the book is available and does not need a reservation\n";
            return;
        }
        if (bookStatus == 2) {
            cout << "book is already reserved by another user\n";
            return;
        }    
        cout << "book " << code << " is currently borrowed by another user, reserving for user " << memberID << ".\n";
        LoanRecord reservedBook = {code, now, 0, 0};
        heldItems.push_back(reservedBook);
        collection.modifyStatus(code, 2, memberID, currentDate);
        saveRecords();      
        cout << "success <3\n";
    }    
    void showAccount() {
        time_t now = time(0);
        cout << "\naccount of user " << memberID << " (" << accountType << ") <3\n";
        cout << "\nborrowed books at the moment:\n";
        if (activeLoans.empty()) cout << "none\n";
        for (const auto& book : activeLoans) {
            int overdueDays = (now > book.dueDate) ? (now - book.dueDate) / 86400 : 0;
            cout << "  " << book.itemCode << " | borrowed: " << ctime(&book.checkoutDate) 
                 << "due: " << ctime(&book.dueDate)
                 << "overdue: " << overdueDays << " days\n";
        }        
        cout <<"\nreserved books:\n";
        if(heldItems.empty()) cout <<"none\n";
        for (const auto& book : heldItems) {
            cout << "  " << book.itemCode << " | reserved on: " << ctime(&book.checkoutDate) << "\n";
        }
        cout << "\nborrowing history (returned books):\n";
        if (loanHistory.empty()) cout << "none\n";
        for (const auto& book : loanHistory) {
            cout << "  " << book.itemCode << " | borrowed: " << ctime(&book.checkoutDate)
                 << "returned: " << ctime(&book.returnDate) << "\n";
        }
        cout << "\ntotal fine is of rs " << overdueFee << "\n";
    }
    void payFees() {
        calculateFees();
        if (overdueFee == 0) {
            cout << "no pending dues <3\n";
            return;
        }
        cout << "total fine paid: Rs. " << overdueFee << "\n";
        overdueFee = 0;
        saveRecords();
    }
    void calculateFees() {
        time_t now = time(0);
        overdueFee = 0;
        for (const auto& book : activeLoans) {
            if (now > book.dueDate && accountType == "Student") {
                overdueFee += ((now - book.dueDate) / 86400) * 10;
            }
        }
    }
    void saveRecords() {
        string filename = memberID + ".csv";
        ofstream output(filename);
        if (!output.is_open()) return;
        for (const auto& book : activeLoans) {
            output << book.itemCode << "," << book.checkoutDate << "," << book.dueDate << ",0\n";
        }
        for (const auto& book : loanHistory) {
            output << book.itemCode << "," << book.checkoutDate << "," << book.dueDate << "," << book.returnDate << "\n";
        }
        output << "FineAmount," << overdueFee << "\n";
        output.close();
    }
    void loadRecords() {
        string filename = memberID + ".csv";
        ifstream input(filename);
        if (!input.is_open()) return;
        activeLoans.clear();
        loanHistory.clear();
        string record;
        while (getline(input, record)) {
            stringstream parser(record);
            string isbn, borrowStr, dueStr, returnStr;
            getline(parser, isbn, ',');
            getline(parser, borrowStr, ',');
            getline(parser, dueStr, ',');
            getline(parser, returnStr, ',');
            if (isbn == "FineAmount") {
                overdueFee = stoi(borrowStr);
                continue;
            }
            LoanRecord record = {
                isbn,
                static_cast<time_t>(stoll(borrowStr)),
                static_cast<time_t>(stoll(dueStr)),
                static_cast<time_t>(stoll(returnStr))
            };
            if (record.returnDate == 0) {
                activeLoans.push_back(record);
            } else {
                loanHistory.push_back(record);
            }
        }
        input.close();
    }
};  
class Member {    
protected:
    string identifier;
    string fullName,accountType;
    string itemsOut,daysLate,penalty;
public:
    Member(string id, string name, string type, string items, string days, string fee) {
        identifier = id;
        fullName = name;
        accountType = type;
        itemsOut = items;
        daysLate = days;
        penalty = fee;
    }
    virtual ~Member() {}
    virtual void placeholder() {} 
    string getID() { return identifier; }
    string getType() { return accountType; }
    string getName() { return fullName; }
    string getItemsOut() { return itemsOut; }
    string getDaysLate() { return daysLate; }
    string getPenalty() { return penalty; }
    void setItemsOut(string items) { itemsOut = items; }
    void setDaysLate(string days) { daysLate = days; }
    void setPenalty(string fee) { penalty = fee; }
};
class MemberSystem {
private:
    string memberFile = "user.csv"; 
public:
    vector<Member*> members;
    void loadMembers(vector<Member*>& memberList) {
        ifstream input(memberFile);
        if (!input.is_open()) {
            cerr << "error :'< could not open the user data file\n";
            return;
        }
        string record;
        while (getline(input, record)) {
            stringstream parser(record);
            string id, name, type, booksStr, overdueStr, fineStr;
            getline(parser, id, ',');
            getline(parser, name, ',');
            getline(parser, type, ',');
            getline(parser, booksStr, ',');
            getline(parser, overdueStr, ',');
            getline(parser, fineStr, ',');
            memberList.push_back(new Member(id, name, type, booksStr, overdueStr, fineStr));
        }
        input.close();
    }
    void showMembers() {
        ifstream input(memberFile);
        if (!input) {
            cerr << "error :'< could not the open user database\n";
            return;
        }
        cout << "\nuser list <3\n";
        string record;
        while (getline(input, record)) {
            cout << record << "\n";
        }
        input.close();
    }
    void addMember() {
        string id,name, type;
        string borrowed_books = "0", overdue_days = "0", fine = "0";
        cout << "enter user ID: ";
        getline(cin,id);
        cout << "enter username: ";
        getline(cin, name);
        cout << "enter type>> Student/Faculty/Librarian : ";
        getline(cin, type);
        ofstream output(memberFile, ios::app);
        if (!output) {
            cerr << "error :'< could not open user database\n";
            return;
        }
        output << id << "," << name << "," << type << ","
             << borrowed_books << "," << overdue_days << "," << fine << "\n";

        output.close();
        cout << "successfully added the user <3 user ID: " << id << "\n";
    }

    void updateMember() {
        string search_id;
        cout << "\n to update, enter user ID: ";
        cin >> search_id;
        ifstream input(memberFile);
        ofstream temp("temp.csv");
        if (!input || !temp) {
            cout << "error :'<could not access the user database\n";
            return;
        }
        string id, name, type,borrowed_books,overdue_days,fine;
        bool found = false;
        string record;
        while (getline(input, record)) {
            stringstream parser(record);
            getline(parser, id, ',');
            getline(parser, name, ',');
            getline(parser, type, ',');
            getline(parser, borrowed_books, ',');
            getline(parser, overdue_days, ',');
            getline(parser, fine, ',');
            if (id == search_id) {
                found = true;
                cout << "\nupdating user with user ID: " << id << "\n";
                cout << "enter the new name: ";
                cin.ignore();
                getline(cin, name);
                cout << "\nenter the new type>> Student/Faculty: ";
                getline(cin, type);
                cout << "\nenter number of borrowed books: ";
                getline(cin, borrowed_books);
                cout << "\nenter number of overdue days: ";
                getline(cin, overdue_days);
                cout << "\n enter the fine amount: ";
                getline(cin,fine);
            }
            temp << id << "," << name << "," << type << ","
            << borrowed_books << "," << overdue_days << "," << fine << "\n";
        }
        input.close();
        temp.close();
        if (found) {
            remove(memberFile.c_str());
            rename("temp.csv", memberFile.c_str());
            cout << "\n User details updated successfully.\n";
        } else {
            remove("temp.csv");
            cout << "\n User ID not found. No changes made.\n";
        }
    }
    void removeMember() {
        string search_id;
        cout << "\nto delete, enter the user ID: ";
        cin >> search_id;    
        ifstream input(memberFile);
        ofstream temp("temp.csv");    
        if (!input || !temp) {
            cout << "error :'< could not access the user database\n";
            return;
        }    
        string record;
        bool found = false;    
        while (getline(input, record)) {
            stringstream parser(record);
            string id, name, type, borrowed_books, overdue_days, fine;    
            getline(parser, id, ',');
            getline(parser, name, ',');
            getline(parser, type, ',');
            getline(parser, borrowed_books, ',');
            getline(parser, overdue_days, ',');
            getline(parser, fine, ',');    
            if (id == search_id) {
                found = true;
                cout << "\nthe user '" << name << "' with ID: " << id << " has been removed :'<\n";
                continue;
            }    
            temp << record << "\n";
        }    
        input.close();
        temp.close();    
        if (found) {
            remove(memberFile.c_str());
            rename("temp.csv", memberFile.c_str());
        } else {
            remove("temp.csv");
            cout << "\ncouldn't find the user id, so no changes were made\n";
        }
    }    
    void syncData() {
        for (Member* person : members) {
            string accountFile = person->getID() + ".csv";
            ifstream input(accountFile);
            int borrowed_count = 0;
            int total_overdue_days = 0;
            int fine_amount = 0;
            time_t now = time(0);    
            if (input.is_open()) {
                string entry;
                while (getline(input, entry)) {
                    if (entry.empty()) continue;
                    if (entry.find("FineAmount") != string::npos) {
                        size_t pos = entry.find(',');
                        if (pos != string::npos) {
                            string fine_val = entry.substr(pos + 1);
                            fine_amount = stoi(fine_val);
                        }
                    } else {
                        stringstream parser(entry);
                        string isbn, borrowedStr, dueStr, returnedStr;
                        getline(parser, isbn, ',');
                        getline(parser, borrowedStr, ',');
                        getline(parser, dueStr, ',');
                        getline(parser, returnedStr, ',');
                        if (returnedStr == "0") {
                            borrowed_count++;
                            time_t due = stoll(dueStr);
                            if (now > due) {
                                int overdue_days = (now - due) / 86400;
                                total_overdue_days += overdue_days;
                            }
                        }
                    }
                }
                input.close();
            }    
            person->setItemsOut(to_string(borrowed_count));
            person->setDaysLate(to_string(total_overdue_days));
            person->setPenalty(to_string(fine_amount));
        }    
        ofstream output(memberFile);
        if (!output.is_open()) {
            cerr << "error :'< could not open " << memberFile << " for writing\n";
            return;
        }
        for (Member* person : members) {
            output << person->getID() << "," << person->getName() << "," << person->getType()
                    << "," << person->getItemsOut() << "," 
                    << person->getDaysLate() << "," 
                    << person->getPenalty() << "\n";
        }
        output.close();
        cout << "success <3\n";
    }
};    
class StudentAccount : public Member {
private:
    MemberAccount studentRecord;
    Collection& collection; 
    MemberSystem &memberSys;
public:
    StudentAccount(string id, string name, string type, string items, string days, string fee, Collection& coll, MemberSystem& sys)
        : Member(id, name, type, items, days, fee), studentRecord(id, "Student"), collection(coll), memberSys(sys) {}
    void showMenu() {
        int option = 0;
        while (true) {
            cout << "\n\nmenu for students <3\n\n";
            cout << "1. list of books\n";
            cout << "2. borrow a book\n";
            cout << "3. return a book\n";
            cout << "4. past activity\n";
            cout << "5. pay fine\n";
            cout << "6. logout\n";
            cout << "enter your choice: ";
            cin >> option;
            if (option == 1) {
                collection.showAll();
            } 
            else if (option == 2) {
                checkOut();
            } 
            else if (option == 3) {
                returnItem();
            } 
            else if (option == 4) {
                viewHistory();
            } 
            else if (option == 5) {
                payFees();
            } 
            else if (option == 6) {
                cout << "logging out <3\n";
                break;
            } 
            else {
                cout << "your choice is invalid, re-enter <3\n";
            }
        }
    }
    void checkOut() {
        string code;
        cout << "to borrow, enter ISBN: ";
        cin >> code;
        studentRecord.checkoutItem(code, collection);
        memberSys.syncData();
    }
    void returnItem() {
        string code;
        cout << "to return, enter ISBN: ";
        cin >> code;
        studentRecord.returnItem(code, collection);
        memberSys.syncData();
    }
    void viewHistory() {
        studentRecord.showAccount();
    } 
    void payFees() {
        studentRecord.payFees();
        memberSys.syncData();
    }
};    
class FacultyAccount : public Member {
private:
    MemberAccount facultyRecord;
    Collection& collection; 
    MemberSystem &memberSys;
public:
    FacultyAccount(string id, string name, string type, string items, string days, string fee, Collection& coll, MemberSystem& sys)
        : Member(id, name, type, items, days, fee), facultyRecord(id, "Faculty"), collection(coll), memberSys(sys) {}
    void showMenu() {
        int option = 0;
        while (true) {
            cout << "\n\nmenu for faculty <3\n";
            cout << "1. list of books\n";
            cout << "2. borrow a book\n";
            cout << "3. return a book\n";
            cout << "4. past activity\n";
            cout << "5. logout\n";
            cout << "enter your choice:";
            cin >> option;
            if(option == 1){
                collection.showAll();
            }
            else if (option == 2) {
                checkOut();
            } 
            else if (option == 3) {
                returnItem();
            } 
            else if (option == 4) {
                viewHistory();
            } 
            else if (option == 5) {
                cout << "logging out <3\n";
                break;  
            } 
            else {
                cout << "your choice is invalid, re-enter <3\n";
            }
        }
    }
    void checkOut() {
        string code;
        cout << "to borrow, enter ISBN : ";
        cin >> code;
        facultyRecord.checkoutItem(code, collection);
        memberSys.syncData();
    }
    void returnItem() {
        string code;
        cout << "to return, enter ISBN : ";
        cin >> code;
        facultyRecord.returnItem(code, collection);
        memberSys.syncData();
    }
    void viewHistory() {
        facultyRecord.showAccount();
    }
};
class StaffAccount : public Member {
private:
    Collection &collection;
    MemberSystem &memberSys;
public:
    StaffAccount(string id, string name, Collection &coll, MemberSystem &sys)
        : Member(id, name, "Librarian", "0", "0", "0"), collection(coll), memberSys(sys) {}
    void showMenu() {
        while (true) {
            cout << "\n\nmenu for Librarian <3 \n\n";
            cout << "1. list of books\n";
            cout << "2. add a book\n";
            cout << "3. update a book\n";
            cout << "4. remove a book\n";
            cout << "5. list of users\n";
            cout << "6. add an user\n";
            cout << "7. remove an user\n";
            cout << "8. update an user\n";
            cout << "9. logout\n";
            cout << "enter your choice: ";
            int option;
            cin >> option;
            cin.ignore();
            if (option == 1) {
                collection.showAll();
            }
            else if (option == 2) {
                collection.addItem();
            } 
            else if (option == 3) {
                collection.updateItem();
            } 
            else if (option == 4) {
                collection.removeItem();
            }  
            else if (option == 5) {
                memberSys.showMembers();
            } 
            else if (option == 6) {
                memberSys.addMember();
            } 
            else if (option == 7) {
                memberSys.removeMember();
            } 
            else if (option == 8) {
                memberSys.updateMember();
            } 
            else if (option == 9) {
                cout << "logging out <3\n";
                break;  
            } 
            else {
                cout << "your choice is invalid, re-enter <3\n";
            }
        }
    }
};  
int main() {
    Collection library;
    MemberSystem memberSys;
    library.loadPublications();
    memberSys.loadMembers(memberSys.members);
    cout << "\nlibrary management system:\n";
    string enteredID, enteredPassword;
    cout << "enter your user id: ";
    cin >> enteredID;
    Member* loggedInUser = nullptr;
    for (Member* person : memberSys.members) {
        if (person->getID() == enteredID) {
            loggedInUser = person;
            break;
        }
    }
    if (!loggedInUser) {
        cout << "incorrect user id\n";
        return 0;
    }
    cout << "enter your username:";
    cin >> enteredPassword;
    if (enteredPassword != loggedInUser->getName()) {  
        cout << "incorrect username\n";
        return 0;
    }
    cout << "\nhello "<< loggedInUser->getName() <<" <3\n";
    if (loggedInUser->getType() == "Librarian") {
        StaffAccount staff(loggedInUser->getID(), loggedInUser->getName(), library, memberSys);
        staff.showMenu();
    }
    else if (loggedInUser->getType() == "Student") {
        StudentAccount student(loggedInUser->getID(), loggedInUser->getName(), "Student",
                    loggedInUser->getItemsOut(), loggedInUser->getDaysLate(),
                    loggedInUser->getPenalty(), library, memberSys);        
        student.showMenu();
    } 
    else if (loggedInUser->getType() == "Faculty") {
        FacultyAccount faculty(loggedInUser->getID(), loggedInUser->getName(), "Faculty",
                    loggedInUser->getItemsOut(), loggedInUser->getDaysLate(),
                    loggedInUser->getPenalty(), library, memberSys);
        faculty.showMenu();
    } 
    for (Member* person : memberSys.members) {
        delete person;
    }    
    cout << "\nhave a nice day <3\n";
    return 0;
}
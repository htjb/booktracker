#include "book.h"
#include "database.h"
#include "utils.h"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void addBook(string title, int databaseLength) {

  struct Book newBook;
  newBook.title = title;
  newBook.id = databaseLength + 1;
  cout << "Author: ";
  getline(cin, newBook.author);
  cout << "Day started (YYYY-MM-DD): ";
  getline(cin, newBook.dayStarted);
  while (!checkDate(newBook.dayStarted)) {
    cout << "Invalid date format. Please enter date in YYYY-MM-DD format: ";
    getline(cin, newBook.dayStarted);
  }
  cout << "Status (reading, read, tbr, dnf): ";
  getline(cin, newBook.status);
  checkStatus(newBook);
  if (newBook.status == "read") {
    cout << "Day completed (YYYY-MM-DD): ";
    getline(cin, newBook.dayCompleted);
    while (!checkDate(newBook.dayCompleted)) {
      cout << "Invalid date format. Please enter date in YYYY-MM-DD format: ";
      getline(cin, newBook.dayCompleted);
    }
  } else {
    newBook.dayCompleted = "";
  }
  cout << "Notes (if any, else leave blank): ";
  getline(cin, newBook.notes);

  auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
  stringstream ss;
  ss << put_time(localtime(&time), "%Y-%m-%d");
  newBook.dayAdded = ss.str();

  cout << "Added book: " << newBook.title << endl;

  saveBook(newBook, getenv("HOME"));
}

void deleteBook(int id, vector<Book> books) {
  for (int i = 0; i < books.size(); i++) {
    if (books[i].id == id) {
      books.erase(books.begin() + i);
      cout << "Deleted book with ID: " << id << endl;
    }
  }
  saveAllBooks(books, getenv("HOME"));
}

void list(vector<Book> books) {
  cout << left << setw(4) << "ID" << setw(25) << "Title" << setw(20) << "Author"
       << setw(14) << "Started" << setw(16) << "Completed" << setw(10)
       << "Status" << '\n';

  cout << string(89, '-') << '\n';

  for (const auto &b : books) {
    cout << left << setw(4) << b.id << setw(25) << b.title << setw(20)
         << b.author << setw(14) << b.dayStarted << setw(16) << b.dayCompleted
         << setw(10) << b.status << '\n';
  }
}

void showBook(int id, vector<Book> books) {
  for (Book b : books) {
    if (b.id == id) {
      cout << left << setw(15) << "ID: " << b.id << endl;
      cout << left << setw(15) << "Title: " << b.title << endl;
      cout << left << setw(15) << "Author: " << b.author << endl;
      cout << left << setw(15) << "Day Started: " << b.dayStarted << endl;
      cout << left << setw(15) << "Day Completed: " << b.dayCompleted << endl;
      cout << left << setw(15) << "Day Added: " << b.dayAdded << endl;
      cout << left << setw(15) << "Status: " << b.status << endl;
      cout << left << setw(15) << "Notes: " << b.notes << endl;
      return;
    }
  }
  cout << "Book with ID " << id << " not found." << endl;
}

void modifyBook(int id, string section, string newValue, vector<Book> books) {

  const vector<string> validSections{"title",     "author", "started",
                                     "completed", "status", "notes"};
  const vector<string> validStatuses{"reading", "read", "tbr", "dnf"};

  if (find(validSections.begin(), validSections.end(), section) ==
      validSections.end()) {
    cout << "Invalid section: " << section << endl;
    return;
  }

  for (int i = 0; i < books.size(); i++) {
    if (books[i].id == id) {
      cout << "Modifying book with ID: " << id << endl;
      if (section == "title") {
        books[i].title = newValue;
      } else if (section == "author") {
        books[i].author = newValue;
      } else if (section == "started") {
        books[i].dayStarted = newValue;
        if (!checkDate(newValue)) {
          cout << "Invalid date format. Please enter date in YYYY-MM-DD format."
               << endl;
          return;
        }
      } else if (section == "completed") {
        books[i].dayCompleted = newValue;
        if (!checkDate(newValue)) {
          cout << "Invalid date format. Please enter date in YYYY-MM-DD format."
               << endl;
          return;
        }
      } else if (section == "status") {
        if (find(validStatuses.begin(), validStatuses.end(), newValue) ==
            validStatuses.end()) {
          cout << "Invalid status. Please enter one of the following: ";
          for (const auto &status : validStatuses) {
            cout << status << " ";
          }
          cout << endl;
          return;
        }
        books[i].status = newValue;
      } else if (section == "notes") {
        books[i].notes = newValue;
      }
      cout << "Book with ID " << id << " has been modified." << endl;
    }
  }

  saveAllBooks(books, getenv("HOME"));
}

void plot() {
  auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
  stringstream ss;
  ss << put_time(localtime(&time), "%Y");
  string year = ss.str();

  vector<string> validStatus{"reading", "read", "tbr", "dnf"};

  vector<string> months{"01", "02", "03", "04", "05", "06",
                        "07", "08", "09", "10", "11", "12"};

  vector<vector<int>> counts;

  for (int i = 0; i < months.size(); i++) {
    vector<int> month_counts;
    for (int j = 0; j < validStatus.size(); j++) {
      int c =
          filterDateStatus(getenv("HOME"), year + months[i], validStatus[j]);
      month_counts.push_back(c);
    }
    counts.push_back(month_counts);
  }

  FILE *gp = popen("gnuplot -persistent", "w");

  fprintf(gp, "set terminal dumb 80 25\n");
  fprintf(gp, "plot '-' with points\n");

  for (int j = 0; j < validStatus.size(); ++j) {
    for (int i = 0; i < months.size(); ++i) {
      fprintf(gp, "%f %f\n", i + 1, counts[i][j]);
    }
    fprintf(gp, "e\n");
  }

  pclose(gp);
}

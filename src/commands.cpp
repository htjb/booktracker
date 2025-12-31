#include "book.h"
#include "database.h"
#include "utils.h"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <numeric>
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
  while (!checkDate(newBook.dayStarted) && newBook.dayStarted != "") {
    cout << "Invalid date format. Please enter date in YYYY-MM-DD format: ";
    getline(cin, newBook.dayStarted);
  }
  cout << "Status (reading, read, tbr, dnf): ";
  getline(cin, newBook.status);
  checkStatus(newBook);
  if (newBook.status == "read") {
    cout << "Day completed (YYYY-MM-DD): ";
    getline(cin, newBook.dayCompleted);
    while (!checkDate(newBook.dayCompleted) && newBook.dayCompleted != "") {
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
    cout << left << setw(4) << b.id << setw(25) << fit(b.title, 25) << setw(20)
         << fit(b.author, 20) << setw(14) << fit(b.dayStarted, 14) << setw(16)
         << fit(b.dayCompleted, 16) << setw(10) << fit(b.status, 10) << '\n';
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
        if (!checkDate(newValue) && newValue != "") {
          cout << "Invalid date format. Please enter date in YYYY-MM-DD format."
               << endl;
          return;
        }
      } else if (section == "completed") {
        books[i].dayCompleted = newValue;
        if (!checkDate(newValue) && newValue != "") {
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

void plot_stacked_bars(const vector<vector<int>> &counts,
                       const vector<string> &months,
                       const vector<string> &statuses) {
  int max_total = 0;

  for (const auto &month_counts : counts)
    max_total =
        max(max_total, accumulate(month_counts.begin(), month_counts.end(), 0));

  if (max_total == 0) {
    cout << "No books finished this year!" << endl;
    return;
  }

  cout << "\nStacked Bar Chart of Books Completed per Month\n";

  int height = max_total * 2; // vertical resolution

  // Print chart from top to bottom
  for (int h = height; h >= 1; --h) {

    float yval = h * max_total / float(height);
    printf("%.1f |", yval);
    for (int i = 0; i < counts.size(); ++i) {
      int sum = 0;
      for (int j = 0; j < counts[i].size(); ++j)
        sum += counts[i][j];
      int level = sum * height / max_total;
      if (level >= h)
        cout << "██";
      else
        cout << "   ";
    }
    cout << " " << endl;
  }

  // Print X-axis
  cout << "     ";
  for (int i = 0; i < counts.size(); ++i) {
    cout << "---";
  }
  cout << endl;

  // Print month labels
  cout << "      ";
  for (int i = 0; i < months.size(); ++i) {
    cout << months[i] << " ";
  }
  cout << endl;

  cout << "                     " << "Month" << endl;
}

// Usage
void plot(vector<Book> books) {
  vector<string> validStatus{"reading", "read", "tbr", "dnf"};
  vector<string> months{"01", "02", "03", "04", "05", "06",
                        "07", "08", "09", "10", "11", "12"};

  vector<vector<int>> counts;
  auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
  stringstream ss;
  ss << put_time(localtime(&now), "%Y");
  string year = ss.str();

  for (const auto &month : months) {
    vector<int> month_counts;
    for (const auto &status : validStatus) {
      int c = filterDateStatus(books, year + "-" + month, status);
      month_counts.push_back(c);
    }
    counts.push_back(month_counts);
  }

  plot_stacked_bars(counts, months, validStatus);
}

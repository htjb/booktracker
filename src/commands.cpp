/* Functions to handle book database commands such as add, delete, list,
 * show, and modify.
 *
 * Authors: Harry Bevins
 *
 */
#include "book.h"
#include "database.h"
#include "utils.h"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void addBook(string title, int databaseLength) {
  /* Function to add a new book to the database.
   * Params:
   *   title - title of the book to add
   *   databaseLength - current number of books in the database
   */

  // Create new Book struct
  struct Book newBook;
  newBook.title = title;
  newBook.id = databaseLength + 1;

  // Input author
  cout << "Author: ";
  getline(cin, newBook.author);

  // Input status with validation
  cout << "Status (reading, read, tbr, dnf): ";
  getline(cin, newBook.status);
  checkStatus(newBook);

  // Input start date with validation
  if (newBook.status != "tbr") {
    cout << "Day started (YYYY-MM-DD): ";
    getline(cin, newBook.dayStarted);
    while (!checkDate(newBook.dayStarted) && newBook.dayStarted != "") {
      cout << "Invalid date format. Please enter date in YYYY-MM-DD format: ";
      getline(cin, newBook.dayStarted);
    }
  } else {
    newBook.dayStarted = "";
  }

  // Input completion date and rating if status is "read"
  if (newBook.status == "read") {
    cout << "Day completed (YYYY-MM-DD): ";
    getline(cin, newBook.dayCompleted);
    while (!checkDate(newBook.dayCompleted) && newBook.dayCompleted != "") {
      cout << "Invalid date format. Please enter date in YYYY-MM-DD format: ";
      getline(cin, newBook.dayCompleted);
    }
    cout << "Rating (1-5, optional): ";
    getline(cin, newBook.rating);
    checkRating(newBook);
  } else {
    newBook.dayCompleted = "";
    newBook.rating = "";
  }

  // Input notes
  cout << "Notes (if any, else leave blank): ";
  getline(cin, newBook.notes);

  // Set dayAdded to current date
  auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
  stringstream ss;
  ss << put_time(localtime(&time), "%Y-%m-%d");
  newBook.dayAdded = ss.str();

  cout << "Added book: " << newBook.title << endl;

  // Save new book to database
  saveBook(newBook, getenv("HOME"));
}

void deleteBook(int id, vector<Book> &books) {
  /* Function to delete a book from the database by ID.
   * Params:
   *  id - ID of the book to delete
   *  books - vector of Book structs representing the collection
   */
  for (int i = 0; i < books.size(); i++) {
    if (books[i].id == id) {
      books.erase(books.begin() + i);
      cout << "Deleted book with ID: " << id << endl;
    }
  }
  saveAllBooks(books, getenv("HOME"));
}

void list(vector<Book> &books) {
  /* Function to list all books in the database in a formatted table.
   * Params:
   *  books - vector of Book structs representing the collection
   */

  int termWidth = terminalWidth();
  float colWidth = float(termWidth) / 100;

  if (termWidth < 50) {
    cout << left << setw(4 * colWidth * 2) << "ID" << setw(20 * colWidth * 2)
         << "Title" << setw(15 * colWidth * 2) << "Author" << '\n';

    for (Book b : books) {
      cout << left << setw(4 * colWidth * 2) << b.id << setw(20 * colWidth * 2)
           << fit(b.title, 20 * colWidth * 2) << setw(15 * colWidth * 2)
           << fit(b.author, 15 * colWidth * 2) << '\n';
    }
  } else {

    cout << left << setw(4 * colWidth) << "ID" << setw(25 * colWidth) << "Title"
         << setw(20 * colWidth) << "Author" << setw(14 * colWidth) << "Started"
         << setw(16 * colWidth) << "Completed" << setw(10 * colWidth)
         << "Status" << '\n';

    cout << string(colWidth * 89, '-') << '\n';

    for (Book b : books) {
      cout << left << setw(4 * colWidth) << b.id << setw(25 * colWidth)
           << fit(b.title, 25 * colWidth) << setw(20 * colWidth)
           << fit(b.author, 20 * colWidth) << setw(14 * colWidth)
           << fit(b.dayStarted, 14 * colWidth) << setw(16 * colWidth)
           << fit(b.dayCompleted, 16 * colWidth) << setw(10 * colWidth)
           << fit(b.status, 10 * colWidth) << '\n';
    }
  }
}

void showBook(int id, vector<Book> &books) {
  /* Function to display detailed information about a specific book.
   * Params:
   *  id - ID of the book to display
   *  books - vector of Book structs representing the collection
   */

  int termWidth = terminalWidth();

  int maxLength = termWidth - 20;

  for (Book b : books) {
    if (b.id == id) {
      cout << left << setw(15) << "ID: " << b.id << endl;
      cout << left << setw(15) << "Title: " << fit(b.title, maxLength) << endl;
      cout << left << setw(15) << "Author: " << fit(b.author, maxLength)
           << endl;
      cout << left << setw(15)
           << "Day Started: " << fit(b.dayStarted, maxLength) << endl;
      cout << left << setw(15)
           << "Day Completed: " << fit(b.dayCompleted, maxLength) << endl;
      cout << left << setw(15) << "Day Added: " << fit(b.dayAdded, maxLength)
           << endl;
      cout << left << setw(15) << "Status: " << fit(b.status, maxLength)
           << endl;
      cout << left << setw(15) << "Rating: " << fit(b.rating, maxLength)
           << endl;
      cout << left << setw(15) << "Notes: " << fit(b.notes, maxLength) << endl;
      return;
    }
  }
  cout << "Book with ID " << id << " not found." << endl;
}

void modifyBook(int id, string section, string newValue, vector<Book> &books) {
  /* Function to modify a specific section of a book's details.
   * Params:
   *  id - ID of the book to modify
   *  section - section of the book to modify (e.g., "title", "author", etc.)
   *  newValue - new value to set for the specified section
   *  books - vector of Book structs representing the collection
   */

  const vector<string> validSections{"title",  "author", "started", "completed",
                                     "status", "rating", "notes"};
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
      } else if (section == "rating") {
        books[i].rating = newValue;
        const vector<string> validRatings{"1", "2", "3", "4", "5", ""};
        if (find(validRatings.begin(), validRatings.end(), newValue) ==
            validRatings.end()) {
          cout << "Invalid rating. Please enter a rating between 1 and 5, or "
                  "leave blank."
               << endl;
          return;
        }
      }
      cout << "Book with ID " << id << " has been modified." << endl;
    }
  }

  saveAllBooks(books, getenv("HOME"));
}

#include "book.h"
#include "database.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void addBook(string title, int databaseLength) {

  struct Book newBook;
  newBook.title = title;
  newBook.id = databaseLength + 1;
  cout << "Author: ";
  getline(cin, newBook.author);
  cout << "Day started: ";
  getline(cin, newBook.dayStarted);
  cout << "Status (e.g., reading, completed): ";
  getline(cin, newBook.status);
  cout << "Day completed (if applicable, else leave blank): ";
  getline(cin, newBook.dayCompleted);
  cout << "Notes (if any, else leave blank): ";
  getline(cin, newBook.notes);

  cout << "Added book: " << newBook.title << endl;

  saveBook(newBook);
}

void deleteBook(int id, vector<Book> books) {
  for (int i = 0; i < books.size(); i++) {
    if (books[i].id == id) {
      books.erase(books.begin() + i);
      cout << "Deleted book with ID: " << id << endl;
    }
  }

  ofstream out("books.txt", ios::trunc);
  for (Book b : books) {
    out << b.id << "|" << b.title << "|" << b.author << "|" << b.dayStarted
        << "|" << b.dayCompleted << "|" << b.status << "\n";
  }
}

void list(vector<Book> books) {
  cout << left
       << setw(4)  << "ID" 
       << setw(25) << "Title"
       << setw(20) << "Author"
       << setw(14) << "Started"
       << setw(16) << "Completed"
       << setw(10) << "Status" << '\n';

  cout << string(89, '-') << '\n';

  for (const auto& b : books) {
    cout << left
         << setw(4)  << b.id
         << setw(25) << b.title
         << setw(20) << b.author
         << setw(14) << b.dayStarted
         << setw(16) << b.dayCompleted
         << setw(10) << b.status << '\n';
  }
}

void showBook(int id, vector<Book> books) {
  for (Book b : books) {
    if (b.id == id) {
      cout << "ID: " << b.id << endl;
      cout << "Title: " << b.title << endl;
      cout << "Author: " << b.author << endl;
      cout << "Day Started: " << b.dayStarted << endl;
      cout << "Day Completed: " << b.dayCompleted << endl;
      cout << "Status: " << b.status << endl;
      cout << "Notes: " << b.notes << endl;
      return;
    }
  }
  cout << "Book with ID " << id << " not found." << endl;
}

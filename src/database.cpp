/* Save and load functions for the database *
 * Author: Harry Bevins
 */

#include "book.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void saveBook(Book b, string homeDir) {
    /* Saves a single book to the database file.
     *
     * Params:
     *   b - Book struct to save
     *   homeDir - path to the user's home directory
     */
  ofstream out(homeDir + "/.book/books.txt", ios::app);
  out << b.id << "|" << b.title << "|" << b.author << "|" << b.dayStarted << "|"
      << b.dayCompleted << "|" << b.dayAdded << "|" << b.status << "|"
      << b.rating << "|" << b.format << "|" << b.pages << "|" << b.notes << "\n";
}

vector<Book> loadBooks(string homeDir) {
  /* Loads all books from the database file.
   *
   * Params:
   *   homeDir - path to the user's home directory
   * Returns:
   *   vector of Book structs representing all books in the database
   */
  vector<Book> books;
  ifstream in(homeDir + "/.book/books.txt");
  string line;

  while (getline(in, line)) {
    stringstream ss(line);
    Book b;

    string idstr;
    getline(ss, idstr, '|');
    b.id = stoi(idstr);

    getline(ss, b.title, '|');
    getline(ss, b.author, '|');
    getline(ss, b.dayStarted, '|');
    getline(ss, b.dayCompleted, '|');
    getline(ss, b.dayAdded, '|');
    getline(ss, b.status, '|');
    getline(ss, b.rating, '|');
    getline(ss, b.format, '|');

    string pagesstr;
    getline(ss, pagesstr, '|');
    b.pages = stoi(pagesstr);

    getline(ss, b.notes, '|');
    books.push_back(b);
  }
  return books;
}

void saveAllBooks(const vector<Book> &books, const string homeDir) {
  /* Saves all books to the database file, overwriting existing data.
   * Params:
   *   books - vector of Book structs to save
   *   homeDir - path to the user's home directory
   */
  ofstream out(homeDir + "/.book/books.txt", ios::trunc);
  for (Book b : books) {
    out << b.id << "|" << b.title << "|" << b.author << "|" << b.dayStarted
        << "|" << b.dayCompleted << "|" << b.dayAdded << "|" << b.status << "|"
        << b.rating << "|" << b.format << "|" << b.pages << "|" << b.notes << "\n";
  }
}

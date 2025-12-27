#include <fstream>
#include <string>
#include <vector>
#include "book.h"

using namespace std;

void saveAllBooks(const vector<Book> books, const string homeDir) {
  ofstream out(homeDir + "/.book/books.txt", ios::trunc);
  for (Book b : books) {
    out << b.id << "|" << b.title << "|" << b.author << "|" << b.dayStarted
        << "|" << b.dayCompleted << "|" << b.status << "|" << b.notes << "\n";
  }
}

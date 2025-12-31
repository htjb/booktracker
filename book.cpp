#include "src/book.h"
#include "src/commands.h"
#include "src/database.h"
#include "src/version.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

  const vector<string> allowed_commands{
      "add", "ls", "list", "del", "delete", "mod", "modify", "help", "show", "version", "plot"};

  string command = argv[1];

  if (find(allowed_commands.begin(), allowed_commands.end(), command) ==
      allowed_commands.end()) {
    cout << "Unknown command: " << command << endl;
    return 1;
  }

  string homeDir = getenv("HOME");
 
  vector<Book> books = loadBooks(homeDir);
  vector<int> ids;
  for (Book b : books) {
    ids.push_back(b.id);
  }

  int maxId =
      ids.size() > 0 ? *max_element(ids.begin(), ids.end()) : 0;

  if (command == "add") {
    addBook(argv[2], maxId);
  } else if (command == "delete" || command == "del") {
    int id = stoi(argv[2]);
    deleteBook(id, books);
  } else if (command == "list" || command == "ls") {
    list(books);
  } else if (command == "show") {
    int id = stoi(argv[2]);
    showBook(id, books);
  } else if (command == "mod" || command == "modify") {
    int id = stoi(argv[2]);
    modifyBook(id, argv[3], argv[4], books);
  } else if (command == "help") {
    cout << "Available commands: add, list (ls), delete (del), show, modify "
            "(mod), help"
         << endl;
  } else if (command == "version") {
    cout << "BookTracker version " << BOOKTRACKER_VERSION << endl;
  } else if (command == "plot") {
    plot(books);
  }
  return 0;
}

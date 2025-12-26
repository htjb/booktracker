#include <iostream>
#include <vector>
#include "src/commands.h"
#include "src/database.h"
#include "src/book.h"

using namespace std;

int main(int argc, char* argv[]) {
    string command = argv[1];
    
    vector<Book> books = loadBooks();

    int databaseLength = books.size();

    if (command == "add") {
        addBook(argv[2], databaseLength);
    } else if (command == "delete" || command == "del") {
        int id = stoi(argv[2]);
        deleteBook(id, books);
    } else if (command == "list" || command == "ls") {
        list();
    } else {
        cout << "Unknown command: " << command << endl;
        return 1;
    }
    return 0;
}

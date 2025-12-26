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
        add(argv[2], databaseLength);
    } else if (command == "list") {
        list();
    } else {
        cout << "Unknown command: " << command << endl;
        return 1;
    }
    return 0;
}

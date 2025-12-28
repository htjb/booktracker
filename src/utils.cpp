#include "book.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void checkStatus(Book &newBook) {
  const vector<string> validStatuses{"reading", "completed", "tbr", "dnf"};

  while (find(validStatuses.begin(), validStatuses.end(), newBook.status) ==
         validStatuses.end()) {
    cout << "Invalid status. Please enter one of the following: ";
    for (const auto &status : validStatuses) {
      cout << status << " ";
    }
    cout << endl;
    cout << "Status: ";
    getline(cin, newBook.status);
  }
}

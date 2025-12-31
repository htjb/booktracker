#include "book.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void checkStatus(Book &newBook) {
  const vector<string> validStatuses{"reading", "read", "tbr", "dnf"};

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

bool checkDate(string date){
    istringstream iss(date);
    year_month_day ymd;
    iss >> parse("%Y-%m-%d", ymd);
    if (iss.fail()){
        return false;
    }
    return ymd.ok();
}

int filterDateStatus(vector<Book> books, string date, string status){

    int count = 0;
    for (const auto& book : books) {
        if (book.dayCompleted.find(date) != string::npos &&
            book.status == status) {
            count += 1;
        }
    }

    return count;
}

string fit(const string& s, size_t w) {
  if (s.size() <= w) return s;
  return s.substr(0, w - 1) + "…";
}

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

int filterDateStatus(string homeDir, string date, string status){
    ifstream in(homeDir + "/.book/books.txt");
    string line;
    
    int count = 0;
    while (getline(in, line)) {
        if (line.find(date) != npos &&
            line.find(status) != npos) {
            count += 1;
        }
    }

    return count;
}

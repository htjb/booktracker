#include "book.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
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
    

#include "book.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

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

void checkRating(Book &newBook) {
    /* Function to validate book rating input 
     * Params:
     *  newBook - reference to Book struct to validate rating for
     * */
    const vector<string> validRatings{"1", "2", "3", "4", "5", ""};
    while (find(validRatings.begin(), validRatings.end(), newBook.rating) ==
           validRatings.end()) {
      cout << "Invalid rating. Please enter a rating between 1 and 5, or leave blank: ";
      getline(cin, newBook.rating);
    }
}

bool checkDate(string date) {
  istringstream iss(date);
  year_month_day ymd;
  iss >> parse("%Y-%m-%d", ymd);
  if (iss.fail()) {
    return false;
  }
  return ymd.ok();
}

int filterDateStatus(vector<Book> books, string date, string status) {

  int count = 0;
  for (const auto &book : books) {
    if (book.dayCompleted.find(date) != string::npos && book.status == status) {
      count += 1;
    }
  }

  return count;
}

string fit(const string &s, size_t w) {
  if (s.size() <= w)
    return s;
  return s.substr(0, w - 1) + "…";
}

int terminalWidth() {
  winsize w{};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

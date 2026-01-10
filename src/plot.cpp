#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "book.h"
#include "utils.h"
#include <cstdio>

using namespace std;

void plot_stacked_bars(const vector<vector<int>> &counts,
                       const vector<string> &months,
                       const vector<string> &statuses) {
  int max_total = 0;

  for (const auto &month_counts : counts)
    max_total =
        max(max_total, accumulate(month_counts.begin(), month_counts.end(), 0));

  if (max_total == 0) {
    cout << "No books finished this year!" << endl;
    return;
  }

  cout << "\nStacked Bar Chart of Books Completed per Month\n";

  int height = max_total * 2; // vertical resolution

  // Print chart from top to bottom
  for (int h = height; h >= 1; --h) {

    float yval = h * max_total / float(height);
    printf("%.1f |", yval);
    for (int i = 0; i < counts.size(); ++i) {
      int sum = 0;
      for (int j = 0; j < counts[i].size(); ++j)
        sum += counts[i][j];
      int level = sum * height / max_total;
      if (level >= h)
        cout << "██";
      else
        cout << "   ";
    }
    cout << " " << endl;
  }

  // Print X-axis
  cout << "     ";
  for (int i = 0; i < counts.size(); ++i) {
    cout << "---";
  }
  cout << endl;

  // Print month labels
  cout << "      ";
  for (int i = 0; i < months.size(); ++i) {
    cout << months[i] << " ";
  }
  cout << endl;

  cout << "                     " << "Month" << endl;
}

// Usage
void plot(vector<Book> books) {
  vector<string> validStatus{"reading", "read", "tbr", "dnf"};
  vector<string> months{"01", "02", "03", "04", "05", "06",
                        "07", "08", "09", "10", "11", "12"};

  vector<vector<int>> counts;
  auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
  stringstream ss;
  ss << put_time(localtime(&now), "%Y");
  string year = ss.str();

  for (const auto &month : months) {
    vector<int> month_counts;
    for (const auto &status : validStatus) {
      int c = filterDateStatus(books, year + "-" + month, status);
      month_counts.push_back(c);
    }
    counts.push_back(month_counts);
  }

  plot_stacked_bars(counts, months, validStatus);
}

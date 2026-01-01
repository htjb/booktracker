#ifndef COMMANDS_H
#define COMMANDS_H

#include "book.h"
#include <iostream>
#include <string>
#include <vector>

void plot(std::vector<Book> books);
void plot_stacked_bars(const std::vector<std::vector<int>>& counts,
                        const std::vector<std::string>& months,
                        const std::vector<std::string>& statuses);

#endif

#include <iostream>
#include <vector>
#include "src/commands.h"

using namespace std;

int main(int argc, char* argv[]) {
    string command = argv[1];

    if (command == "add") {
        add(argv[2]);
    }
}

// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>

namespace st = std;

auto const nrOfTables = 10;
auto const nrOfLinesPerTable = 10;

void printLine (int tableNr, int lineNr) {
    st::cout << lineNr << " x " << tableNr << " = " << lineNr * tableNr << '\n';
}

void printTable (int tableNr) {
    for (auto lineNr = 1; lineNr <= nrOfLinesPerTable; lineNr++) {
        printLine (tableNr, lineNr);
    }
    st::cout << '\n';
}

int main () {
    for (auto tableNr = 1; tableNr <= nrOfTables; tableNr++) {
        printTable (tableNr);
    }

    return 0;
}

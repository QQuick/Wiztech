// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
namespace st = std;

#include "heaper.hpp"
namespace hp = heaper;

int main () {
    st::cout << '\n';
    
    st::cout << 111 << '\n';
    auto string0 = hp::String ("fiets");
    st::cout << 222 << '\n';
    auto string1 = hp::String ("pomp");
    st::cout << 333 << "\n\n" ;

    auto string2 = string0 + string1;
    st::cout << 444 << '\n';
    auto string3 = string2;
    st::cout << 555 << "\n\n";
    
    string2 = "huisdeur";
    st::cout << 666 << "\n\n";

    auto string4 = hp::String ();
    st::cout << 777 << "\n\n";

    st::cout << "Hoe heet je?\n";
    st::cout << 888 << '\n';
    st::cin >> string4;
    st::cout << 999 << "\n\n";

    st::cout << string0 << '\n' << string1 << '\n' << string2 << '\n' << string3 << '\n' << string4 << "\n\n";
    return 0;
}

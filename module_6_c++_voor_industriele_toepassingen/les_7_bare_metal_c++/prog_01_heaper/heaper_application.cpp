#include <iostream>
namespace st = std;

#include "heaper.hpp"
namespace hp = heaper;

auto string0 = hp::String ("fiets");
auto string1 = hp::String ("pomp");
auto string2 = string0 + string1;
auto string3 = string2;

auto string4 = "huisdeur";

auto string5 = hp::String ();
st::cout << "Hoe heet je? ";
st::cin >> string7;

st::cout << string0 << ' ' << string1 << ' ' << string2 << ' ' << string3 << ' ' << string4 << ' ' << string5 << '\n';

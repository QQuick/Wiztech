// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
#include <iomanip>
namespace st = std;

template <class T>
class Named {
    public:
        Named (T value, st::string name):
            value (value),
            name (name)
        {}

        T value;
        st::string name;
};

int main () {
    auto number = Named <float> (3.14, "pi");
    auto person = Named <st::string> ("007", "james");
    
    st::cout << '\n';
    st::cout << st::setw (10) << number.name << ": " << number.value << '\n';
    st::cout << st::setw (10) << person.name << ": " << person.value << '\n';
    st::cout << '\n';
    
    return 0;
}

// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
#include <vector>
namespace st = std;

// ====== Deal with ints, strings, floats, chars etc.

template <class T>
bool between (T left, T middle, T right, bool label = true) {
    if (label) {
        st::cout << 'a';
    }
    
    return
        left <= middle && middle <= right ||
        right <= middle && middle <= left;
}

// ====== Deal with chars in particular

bool between (char left, char middle, char right) {
    st::cout << 'b';
    return between (left, middle, right, false);
}

// ====== Deal with any combination

int toInt (int const anInt) {
    return anInt;
}

int toInt (st::string const aString) {
    auto strings = st::vector <st::string> {"een", "twee", "drie"};
    for (auto stringIndex = 0; stringIndex < strings.size (); stringIndex++) {
        if (strings [stringIndex] == aString) {
            return stringIndex + 1;
        }
    }
    return 0;
}

int toInt (char const aChar) {
    return aChar - '0';
}

template <class T1, class T2, class T3>
bool between (T1 left, T2 middle, T3 right) {
    st::cout << 'c';
    return between (toInt (left), toInt (middle), toInt (right), false);
}

// ====== Main entrypoint

int main () {

    st::cout <<
        "\n" <<    
        between (1, 2, 3) << " 1\n" <<
        between (3, 2, 1) << " 1\n" <<
        between (1, 3, 2) << " 0\n" <<
        between (2, 3, 1) << " 0\n" <<
        "\n" <<
        between ('1', '2', '3') << " 1\n" <<
        between ('3', '2', '1') << " 1\n" <<
        between ('1', '3', '2') << " 0\n" <<
        between ('2', '3', '1') << " 0\n" <<
        "\n" <<
        between ("maan", "roos", "vis") << " 1\n" <<
        between ("vis", "roos", "maan") << " 1\n" <<
        between ("maan", "vis", "roos") << " 0\n" <<
        between ("roos", "vis", "maan") << " 0\n" <<
        "\n" <<
        between (1, "twee", '3') << " 1\n" <<
        between ("een", 2 , "drie") << " 1\n" <<
        between ("een", "drie", 2) << " 0\n" <<
        between ("twee", '1', "drie") << " 0\n" <<
        "\n";

    return 0;
}

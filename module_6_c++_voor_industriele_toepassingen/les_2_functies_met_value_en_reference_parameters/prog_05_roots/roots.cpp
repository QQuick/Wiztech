// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
#include <cmath>
#include <string>

namespace st = std;

float root (float number, float power = 2) {
    return pow (number, 1 / power);
}

st::string root (st::string verb) {
    return verb.substr (3);
}

int main () {
    st::cout << root (16) << ' ' << root (125, 3) << ' ' << root ("to walk") << ' ' << root ("to run") << '\n';
    return 0;
}

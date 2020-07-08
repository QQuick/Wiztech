#include <iostream>

namespace st = std;

template <class T>
bool between (T left, T middle, T right, bool label = true) {
    if (label) {
        st::cout << 'a';
    }
    
    return
        left <= middle && middle <= right ||
        right <= middle && middle <= left;
}

bool between (char left, char middle, char right) {
    st::cout << 'b';
    return between (left, middle, right, false);
}

template <class T1, class T2, class T3>
bool between (T1 left, T2 middle, T3 right) {
    st::cout << 'c';
    return false;
}

int main () {

    st::cout <<
        "\n" <<    
        between (1, 2, 3) << " a1\n" <<
        between (3, 2, 1) << " a1\n" <<
        between (1, 3, 2) << " a0\n" <<
        between (2, 3, 1) << " a0\n" <<
        "\n" <<
        between ('1', '2', '3') << " b1\n" <<
        between ('3', '2', '1') << " b1\n" <<
        between ('1', '3', '2') << " b0\n" <<
        between ('2', '3', '1') << " b0\n" <<
        "\n" <<
        between ("maan", "roos", "vis") << " a1\n" <<
        between ("vis", "roos", "maan") << " a1\n" <<
        between ("maan", "vis", "roos") << " a0\n" <<
        between ("roos", "vis", "maan") << " a0\n" <<
        "\n" <<
        between (1, "twee", '3') << " c0\n" <<
        between ("een", 2 , "drie") << " c0\n" <<
        between ("een", "twee", 3) << " c0\n" <<
        between ('1', "twee", "drie") << " c0\n" <<
        "\n";

    return 0;
}

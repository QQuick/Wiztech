#include <iostream>
#include <vector>
#include <string>

namespace st = std;

int main() {
    auto planetNames = st::vector <st::string> ({
        "mercurius",
        "venus",
        "aarde",
        "mars",
        "jupiter",
        "saturnus",
        "uranus",
        "neptunus"
    });
    
    for (auto planetName: planetNames) {
        st::cout << planetName << '\n';
    }
}

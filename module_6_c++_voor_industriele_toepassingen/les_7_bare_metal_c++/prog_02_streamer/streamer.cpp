// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
#include <fstream>
#include <sstream>

namespace st = std;

int main () {

    st::cout <<  "\n====== Console streams\n\n";
    
    auto name = st::string ();
    auto number = int ();

    st::cout << "111 <naam> <nummer>? ";
    st::cin >> name >> number;
    st::cout << "222 <naam> <nummer>: " << name << ' ' << number << '\n';
    
    st::cout <<  "\n====== Text file streams\n\n";
    
    auto const textFileName = st::string ("test.txt");
    
    auto outputTextFile = st::ofstream (textFileName);
    outputTextFile << name << ' ' << number;
    outputTextFile.close ();

    name = "";
    number = 0;
    st::cout << "333 <naam> <nummer>: " << name << ' ' << number << '\n';

    auto inputTextFile = st::ifstream (textFileName);
    inputTextFile >> name >> number;
    inputTextFile.close ();
    st::cout << "444 <naam> <nummer>: " << name << ' ' << number << '\n';
    
    st::cout << "\n====== String streams:\n\n";
    
    auto aStringStream = st::stringstream ();
    aStringStream << name << ' ' << number;
    auto aString = aStringStream.str ();
    st::cout << "555 <naam> <nummer>: " << aString << "\n";

    name = "";
    number = 0;
    st::cout << "666 <naam> <nummer>: " << name << ' ' << number << '\n';
    
    aStringStream >> name >> number;
    st::cout << "777 <naam> <nummer>: " << name << ' ' << number << '\n';
    
    st::cout << "\n ====== Binary file streams\n\n";
    
    auto binaryOutputFile = st::fstream ("test.bin", st::ios::out |st::ios::binary);
    for (auto position = 0; position < 10; position++) {
        st::int8_t number = 3 * position;
        st::cout << int (number) << ' ';
        binaryOutputFile.seekp (position * sizeof (number));
        binaryOutputFile.write ((char*) &number, sizeof (number));
    }
    binaryOutputFile.close ();
    st::cout << '\n';
    
    auto binaryInputFile = st::fstream ("test.bin", st::ios::in |st::ios::binary);
    for (auto position = 9; position >= 0; position--) {
        st::int8_t number;
        binaryInputFile.seekp (position * sizeof (number));
        binaryInputFile.read ((char*) &number, sizeof (number));
        st::cout << int (number) << ' ';
    }
    binaryInputFile.close ();
    st::cout << "\n\n";
    
    return 0;
}

#include <iostream>
#include <vector>

namespace st = std;

float &getLowest (st::vector <float> &numbers) {
    auto minimumNumberIndex = 0;
    
    for (auto numberIndex = 0; numberIndex < numbers.size (); numberIndex++) {
        if (numbers [numberIndex] < numbers [minimumNumberIndex]) {
            minimumNumberIndex = numberIndex;
        }
    }
    
    return numbers [minimumNumberIndex];
}

void printNumbers (st::vector <float> &numbers, st::string caption) {
    st::cout << '\n' << caption << '\n';\
    for (auto number: numbers) {
        st::cout << number << '\n';
    }
    st::cout << '\n';
}

int main () {
    auto grade = float ();
    auto grades = st::vector <float> ();
    
    st::cout << "Geef cijfers (negatief is stoppen)" << '\n';
    while (true) {
        st::cout << "Cijfer nr. " << grades.size () + 1 << ": "; 
        st::cin >> grade;
        
        if (grade < 0) {
            break;
        }
        else {
            grades.push_back (grade);
        }
    }
    
    printNumbers (grades, "Cijfers voor herkansing");
    
    st::cout << "Geef cijfer herkansing: ";
    st::cin >> grade;
    
    getLowest (grades) = grade;
    printNumbers (grades, "Cijfers na herkansing");
    
    return 0;
}
 


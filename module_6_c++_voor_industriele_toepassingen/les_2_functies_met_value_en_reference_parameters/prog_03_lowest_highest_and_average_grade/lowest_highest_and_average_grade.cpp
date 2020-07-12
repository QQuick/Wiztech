// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
#include <vector>
#include <cstdlib>

namespace st = std;

void computeStatistics (st::vector <float> &numbers, float &minimum, float &maximum, float &mean) {
    auto const finity = 1e100;

    minimum = finity;
    maximum = -finity;

    auto sum = float ();
    
    for (auto number: numbers) {
        if (number < minimum) {
            minimum = number;
        }
        
        if (number > maximum) {
            maximum = number;
        }
            
        sum += number;
    }
    
    mean = sum / numbers.size ();
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
    
    auto lowestGrade = float ();
    auto highestGrade = float ();
    auto averageGrade = float ();
    
    computeStatistics (grades, lowestGrade, highestGrade, averageGrade);
    
    st::cout << "Het laagste is: " << lowestGrade << '\n';
    st::cout << "Het hoogste is: " << highestGrade << '\n';
    st::cout << "Het gemiddelde is: " << averageGrade << '\n';
    
    return 0;
}
 

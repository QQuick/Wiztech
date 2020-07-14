// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
namespace st = std;

#include "matrixpp.hpp"
namespace mt = matrix;

int main () {
    auto const nrOfRows = 3;
    auto const nrOfColumns = nrOfRows;
        
    mt::Matrix <long double> matrix0 (nrOfRows, st::vector <long double> ({
        0, 1, 2,
        3, 4, 5,
        6, 7, 9
    }));
    
    mt::Matrix <long double> matrix1 (nrOfRows, st::vector <long double> ({
        2, 1, 0,
        3, 4, 5,
        9, 7, 6
    }));

    auto matrix2 = matrix0 + matrix1;
    
    auto matrix3 = matrix0 * matrix1;
    
    auto matrix4 = 3 * matrix0;
    
    auto matrix5 = matrix1 * 4;
    
    mt::Matrix <short int> matrix6 (nrOfColumns, nrOfRows);
    
    st::cout <<
        matrix0 << matrix1 << matrix2 << matrix3 << matrix4 << matrix5 <<
        matrix0.getEntriesSize () << ' ' << matrix6.getEntriesSize () << "\n\n";
}

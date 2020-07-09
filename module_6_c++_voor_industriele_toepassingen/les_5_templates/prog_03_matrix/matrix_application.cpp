#include <iostream>
namespace st = std;

#include "matrix.hpp"

namespace mt = matrix;

int main () {
    int const nrOfRows = 3;
    int const nrOfColumns = nrOfRows;
        
    mt::Matrix <long double> matrix0 (nrOfRows, st::vector <long double> ({
        0, 1, 2,
        3, 4, 5,
        6, 7, 9
    }));
    matrix0.print (st::cout);
    
    mt::Matrix <long double> matrix1 (nrOfRows, st::vector <long double> ({
        2, 1, 0,
        3, 4, 5,
        9, 7, 6
    }));
    matrix1.print (st::cout);

    auto matrix2 = mt::add (matrix0, matrix1);
    matrix2.print (st::cout);
    
    auto matrix3 = mt::multiply (matrix0, matrix1);
    matrix3.print (st::cout);
    
    auto matrix4 = mt::multiply (3, matrix0);
    matrix4.print (st::cout);
    
    auto matrix5 = mt::multiply (matrix1, 4);
    matrix5.print (st::cout);
    
    mt::Matrix <short int> matrix6 (nrOfColumns, nrOfRows);
    
    st::cout << matrix0.getEntriesSize () << ' ' << matrix6.getEntriesSize () << "\n\n";
}

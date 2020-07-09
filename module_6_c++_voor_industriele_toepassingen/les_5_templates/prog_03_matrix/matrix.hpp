#pragma once

#include <vector>
#include <iomanip>
namespace st = std;

namespace matrix {

template <class T>
class Matrix {
    public:
        Matrix (int nrOfRows = 0, int nrOfColumns = 0);
        Matrix (int nrOfRows, st::vector <T> const &entries);
        // Matrix (Matrix const &matrix);   // Uncomment to check copy elision
        T &access (int rowIndex, int columnIndex);        
        void print (st::ostream &outputStream);
        int getEntriesSize ();
        
    protected:
        int nrOfRows;
        int nrOfColumns;
        st::vector <T> entries;
    
    template <class U>
    friend Matrix <U> add (Matrix <U> &matrix0, Matrix <U> &matrix1);

    template <class U>
    friend Matrix <U> multiply (Matrix <U> &matrix0, Matrix <U> &matrix1);

    template <class U, class V>
    friend Matrix <U> multiply (V scalar, Matrix <U> &matrix);

    template <class U, class V>
    friend Matrix <U> multiply (Matrix <U> &matrix, V scalar);
};

#include "matrix.cpp"

}

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
        T &operator () (int rowIndex, int columnIndex);        
        int getEntriesSize ();
        
    protected:
        int nrOfRows;
        int nrOfColumns;
        st::vector <T> entries;
        
    template <class U>
    friend st::ostream &operator << (st::ostream &outputStream, Matrix <U> &matrix);
        
    template <class U>
    friend Matrix <U> operator + (Matrix <U> &matrix0, Matrix <U> &matrix1);

    template <class U>
    friend Matrix <U> operator * (Matrix <U> &matrix0, Matrix <U> &matrix1);

    template <class U, class V>
    friend Matrix <U> operator * (V scalar, Matrix <U> &matrix);

    template <class U, class V>
    friend Matrix <U> operator * (Matrix <U> &matrix, V scalar);
};

#include "matrixpp.cpp"

}

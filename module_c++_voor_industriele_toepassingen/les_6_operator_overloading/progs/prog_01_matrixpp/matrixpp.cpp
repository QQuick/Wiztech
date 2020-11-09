// Copyright: GEATEC engineering, 2020
// License: Apache 2

// ====== Members

template <class T>
Matrix <T> ::Matrix (int nrOfRows, int nrOfColumns):
    nrOfRows (nrOfRows),
    nrOfColumns (nrOfColumns),
    entries (nrOfRows * nrOfColumns)
{}
    
template <class T>
Matrix <T> ::Matrix (int nrOfRows, st::vector <T> const &entries):
    nrOfRows (nrOfRows),
    nrOfColumns (entries.size () / nrOfRows),
    entries (entries)
{}

template <class T>
T &Matrix <T> ::operator () (int rowIndex, int columnIndex) {
    return entries [rowIndex * nrOfColumns + columnIndex];
}

template <class T>
int Matrix <T> ::getEntriesSize () {
    return sizeof (T) * entries.capacity ();
}

// ====== Friends

template <class U>
st::ostream & operator << (st::ostream &outputStream, Matrix <U> &matrix) {
    outputStream << '\n';
    for (auto rowIndex = 0; rowIndex < matrix.nrOfRows; rowIndex++) {
        for (auto columnIndex = 0; columnIndex < matrix.nrOfColumns; columnIndex++) {
            outputStream << st::setw (10) << matrix (rowIndex, columnIndex);
        }
        outputStream << '\n';
    }
    outputStream << '\n';
    return outputStream;
}

template <class U>
Matrix <U> operator + (Matrix <U> &matrix0, Matrix <U> &matrix1) {
    auto result = Matrix <U> (matrix0);
    for (auto entryIndex = 0; entryIndex < result.entries.size (); entryIndex++) {
        result.entries [entryIndex] += matrix1.entries [entryIndex];
    }
    return result;
}

template <class U>
Matrix <U> operator * (Matrix <U> &matrix0, Matrix <U> &matrix1) {
    auto result = Matrix <U> (matrix0.nrOfRows, matrix1.nrOfColumns);
    for (auto rowIndex = 0; rowIndex < result.nrOfRows; rowIndex++) {
        for (auto columnIndex = 0; columnIndex < result.nrOfColumns; columnIndex++) {
            for (auto termIndex = 0; termIndex < matrix0.nrOfColumns; termIndex++) {
                result (rowIndex, columnIndex) += matrix0 (rowIndex, termIndex) * matrix1 (termIndex, columnIndex);
            }
        }
    }
    return result;
}

template <class U, class V>
Matrix <U> operator * (V scalar, Matrix <U> &matrix) {
    auto result = Matrix <U> (matrix);
    for (auto entryIndex = 0; entryIndex < result.entries.size (); entryIndex++) {
        result.entries [entryIndex] *= scalar;
    }
    return result;
}

template <class U, class V>
Matrix <U> operator * (Matrix <U> &matrix, V scalar) {
    return scalar * matrix;
}


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
Matrix <T> ::Matrix (Matrix <T> const &matrix):
    nrOfRows (matrix.nrOfRows),
    nrOfColumns (matrix.nrOfColumns),
    entries (matrix.entries)
{}

template <class T>
T &Matrix <T>::access (int rowIndex, int columnIndex) {
    return entries [rowIndex * nrOfColumns + columnIndex];
}

template <class T>
void Matrix <T> ::print (st::ostream &outputStream) {
    outputStream << '\n';
    for (auto rowIndex = 0; rowIndex < nrOfRows; rowIndex++) {
        for (auto columnIndex = 0; columnIndex < nrOfColumns; columnIndex++) {
            outputStream << st::setw (10) << this->access (rowIndex, columnIndex);
        }
        outputStream << '\n';
    }
    outputStream << '\n';
}

template <class U>
Matrix <U> add (Matrix <U> &matrix0, Matrix <U> &matrix1) {
    auto result = Matrix <U> (matrix0);
    for (auto entryIndex = 0; entryIndex < result.entries.size (); entryIndex++) {
        result.entries [entryIndex] += matrix1.entries [entryIndex];
    }
    return result;
}

template <class U>
Matrix <U> multiply (Matrix <U> &matrix0, Matrix <U> &matrix1) {
    auto result = Matrix <U> (matrix0.nrOfRows, matrix1.nrOfColumns);
    for (auto rowIndex = 0; rowIndex < result.nrOfRows; rowIndex++) {
        for (auto columnIndex = 0; columnIndex < result.nrOfColumns; columnIndex++) {
            for (auto termIndex = 0; termIndex < matrix0.nrOfColumns; termIndex++) {
                result.access (rowIndex, columnIndex) += matrix0.access (rowIndex, termIndex) * matrix1.access (termIndex, columnIndex);
            }
        }
    }
    return result;
}

template <class U>
Matrix <U> multiply (U scalar, Matrix <U> &matrix) {
    auto result = Matrix <U> (matrix);
    for (auto entryIndex = 0; entryIndex < result.entries.size (); entryIndex++) {
        result.entries [entryIndex] *= scalar;
    }
    return result;
}

template <class U>
Matrix <U> multiply (Matrix <U> &matrix, U scalar) {
    return multiply (scalar, matrix);
}

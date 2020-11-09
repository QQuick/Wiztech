class Matrix:
    def __mul__ (self, other):	# Overload * operator
        if self.nColumns == other.nRows:
            result = Matrix (self.nRows, other.nColumns)    # Instantiate zero result matrix
            for iRow in range (result.nRows):               # For each iRow of the result matrix
                for iColumn in range (result.nColumns):     # For each iColumn of result matrix
                    for iTerm in range (self.nColumns):     # Compute dot product of iRow'th rowvector of self and iColumn'th columnvector of other
                        result [iRow][iColumn] += self [iRow][iTerm] * other[iTerm][iColumn]
            return result
        else:
            raw_input ('Non matching dimensions')
            exit (1)

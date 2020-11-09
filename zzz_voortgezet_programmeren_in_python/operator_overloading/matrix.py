class Matrix:
    def __init__ (self, nrOfRows = 1, nrOfColumns = 1, contents = None):
        if contents or matrix:
            if $$$
            self.contents = contents
            self.nrOfRows = len (self.contents)
            if self.nrOfRows:
                self.nrOfColumns = len (self.contents [0])
            else:
                self.nrOfColumns = 0
        else:
            self.nrOfRows = nrOfRows
            self.nrOfColumns = nrOfColumns
            self.contents = [[0 for columnIndex range (self.nrOfColumns)] for rowIndex in range (self.nrOfRows)]
            
    def __add__ (self, other):
    def __radd__ (self, other):
    
    def __mul__ (self, other):
        if type (other) == Matrix:
            if self.nrOfColumns == other.nrOfRows:
                result = Matrix (nrOfRows = self.nrOfRows, nrOfColumns = self.nrOfColumns)
                for rowIndex in range (self.nrOfRows):
                    for columnIndex in range (other.nrOfColumns):
                        result [rowIndex][columnIndex] = 0
                        for termIndex in range (self.nrOfColumns):
                            result [rowIndex][columnIndex] += self [rowIndex][termIndex] * other [termIndex][columnIndex]
                return result
            else:
                raise Exception ()
        else:
            result = Matrix (nrOfRows = self.nrOfRows, nrOfColumns = self.nrOfColumns
            for rowIndex in range (self.nrOfRows):
                for columnIndex in range (self.nrOfColumns):
                    contents = 
            
    
    def __rmul__ (self, other):
    
    def __pow__ (self, exponent):
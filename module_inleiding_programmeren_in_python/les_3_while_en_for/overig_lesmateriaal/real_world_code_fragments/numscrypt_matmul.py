class ndarray:
    def __matmul__ (self, other):
        result = empty ((self.ns_nrows, other.ns_ncols), self.dtype)
        
        if self.ns_complex:
            iresult = 0
            for irow in range (self.ns_nrows):
                for icol in range (other.ns_ncols):
                    result.realbuf [iresult] = 0
                    result.imagbuf [iresult] = 0
                    iself = self.ns_ncols * irow
                    iother = icol
                    for iterm in range (self.ns_ncols):
                        result.realbuf [iresult] += self.realbuf [iself] * other.realbuf [iother] - self.imagbuf [iself] * other.imagbuf [iother]
                        result.imagbuf [iresult] += self.realbuf [iself] * other.imagbuf [iother] + self.imagbuf [__postinc__ (iself)] * other.realbuf [iother]
                        iother += other.ns_ncols
                    iresult += 1
        else:
            iresult = 0
            for irow in range (self.ns_nrows):
                for icol in range (other.ns_ncols):
                    result.realbuf [iresult] = 0
                    iself = self.ns_ncols * irow
                    iother = icol
                    for iterm in range (self.ns_ncols):
                        result.realbuf [iresult] += self.realbuf [__postinc__ (iself)] * other.realbuf [iother]
                        iother += other.ns_ncols
                    iresult += 1
            
        return result

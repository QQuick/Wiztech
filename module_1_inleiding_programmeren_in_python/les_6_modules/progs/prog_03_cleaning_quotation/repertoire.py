import utils as ut

class Normbook (ut.Lookup):
    '''Table to lookup cleaning actions'''
    def __init__ (self, filePrename):
        super () .__init__ (filePrename + '.normbook')
        self.items = [Action (line) for line in self.parser.tree [1]]

class Action:
    '''Elementary cleaning act with a fixed norm in m2/hour and frequency in times/year'''
    def __init__ (self, symbols): 
        self.name = symbols [0]
        self.norm = float (symbols [1])
        self.frequency = float (symbols [2])

    def report (self, quotationFile, area, qualityFactor):
        effort = self.frequency * (area / self.norm) * qualityFactor
        print (f'            {self.name:40s} kost {effort:7.2f} mens-uur per jaar', file = quotationFile)
        return effort
        
class Repertoire (ut.Lookup):
    '''Table to lookup cleaning programs'''
    def __init__ (self, filePrename):
        super () .__init__ (filePrename + '.repertoire')
        self.items = [Program (block) for block in self.parser.tree [1:]]

class Program:
    '''Standardized set of cleaning acts for a particular category of building sections'''
    def __init__ (self, lines): 
        self.name = lines [0][0]
        self.actionHints = [line [0] for line in lines [1:]]
            
    def report (self, quotationFile, normbook, area, qualityFactor):
        effort = sum ([
                normbook.get (actionHint) .report (quotationFile, area, qualityFactor)
            for actionHint in self.actionHints
        ]) 
        print (f'        Sectie met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar\n', file = quotationFile)
        return area, effort         

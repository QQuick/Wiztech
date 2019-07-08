class Action:
    '''Elementary cleaning act with a fixed norm in m2/hour and frequency in times/year'''
    def __init__ (self, line): 
        name, norm, frequency = [word.strip () for word in line.split ('  ') if word]
        self.name = name.strip ()
        self.norm = float (norm)
        self.frequency = float (frequency)

    def report (self, quotationFile, area, qualityFactor):
        effort = self.frequency * (area / self.norm) * qualityFactor
        print (f'            {self.name:40s} kost {effort:7.2f} mens-uur per jaar', file = quotationFile)
        return effort

class Program:
    '''Standardized set of cleaning acts for a particular category of building sections'''
    def __init__ (self, block):
        lines = block.split ('\n') 
        self.name = lines [0]
        self.actionHints = [line for line in lines [1:] if line]
            
    def report (self, quotationFile, normbook, area, qualityFactor):
        effort = sum ([
                normbook.get (actionHint) .report (quotationFile, area, qualityFactor)
            for actionHint in self.actionHints
        ]) 
        print (f'        Sectie met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar\n', file = quotationFile)
        return area, effort       

class Lookup:
    '''Utility class to look up an item by its abbreviated name'''
    def __init__ (self, quotationFileName):    
        with open (quotationFileName) as quotationFile:
            blocks = quotationFile.read () .split ('\n\n')
        self.name = blocks [0] .split ()[0]
        self.parseTail (blocks [1:])
        
    def get (self, key):
        for item in self.items:
            if item.name.startswith (key):
                return item
        raise Exception (f'No item of class {self.__class__.__name__} starts with {key}')   

class Normbook (Lookup):
    '''Table to lookup cleaning actions'''
    def parseTail (self, tailBlocks):
        self.items = [Action (line) for line in tailBlocks [0].split ('\n') if line]
        
class Repertoire (Lookup):
    '''Table to lookup cleaning programs'''
    def parseTail (self, tailBlocks):
        self.items = [Program (block) for block in tailBlocks]
    
import sys as ss

import basedata as bd

class Section:
    '''Lumped up areas in one category, e.g. toilets, all with the same cleaning program'''
    def __init__ (self, building, line):
        self.building = building
        name, area, program = [word.strip () for word in line.split ('  ') if word]
        self.name = name.strip ()
        self.area = float (area)
        self.program = self.building.object.repertoire.get (program)
    
    def report (self, quotationFile, qualityFactor):
        print (f'        {self.name}', file = quotationFile)
        return self.program.report (quotationFile, self.building.object.normbook, self.area, qualityFactor)

class Building:
    '''Part of object that is considered an architectural unit'''
    def __init__ (self, object, block):
        self.object = object
        lines = block.split ('\n')
        self.name = lines [0]
        self.sections = [Section (self, line) for line in lines [1:] if line]
    
    def report (self, quotationFile, qualityFactor):
        print (f'    {self.name}\n', file = quotationFile)
        area = 0
        effort = 0
        for section in self.sections:
            sectionArea, sectionEffort = section.report (quotationFile, qualityFactor)
            area += sectionArea
            effort += sectionEffort
        print (f'    Gebouw met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar\n\n', file = quotationFile)
        return area, effort
         
class Object:
    '''Set of buildings that's the subject of a single quotation'''
    def __init__ (self, objectFilePrename, targetNorm):
        with open (objectFilePrename + '.object') as objectFile:
            blocks = objectFile.read () .split ('\n\n')
            nameLine, normbookLine, repertoireLine = blocks [0] .split ('\n')
            self.name = nameLine.split ('  ')[0]
            self.normbook = bd.Normbook (normbookLine.split ()[-1] + '.normbook')
            self.repertoire = bd.Repertoire (repertoireLine.split ()[-1] + '.repertoire')            
        self.targetNorm = targetNorm         
        self.buildings = [Building (self, block) for block in blocks [1:]]
    
    def report (self, objectFilePrename, qualityFactor = 1):
        with open (objectFilePrename + '.quotation', 'w') as quotationFile:
            print (f'Offerte {self.name}\n', file = quotationFile)
            area = 0
            effort = 0
            for building in self.buildings:
                buildingArea, buildingEffort = building.report (quotationFile, qualityFactor)
                area += buildingArea
                effort += buildingEffort
            realNorm = area / (effort / 250)
            print (f'Object met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar', file = quotationFile)
            print (f'Dit komt neer op een uurprestatie op jaarbasis van {realNorm:.2f} m2\n\n\n', file = quotationFile)
            return realNorm / self.targetNorm

print ('\nBezig met maken van offertes')
objectFilePrename, targetNorm = ss.argv [1], float (ss.argv [2])
object = Object (objectFilePrename, targetNorm)
qualityFactor = object.report ('standaard_offerte.txt')
object.report (f'aangepaste_offerte_{targetNorm}_m2.txt', qualityFactor)
print ('Offertes zijn klaar\n')

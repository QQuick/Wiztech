import sys as ss

import utils as ut
import repertoire as rp

class Section:
    '''Lumped up areas in one category, e.g. toilets, all with the same cleaning program'''
    def __init__ (self, building, symbols):
        self.building = building
        self.name = symbols [0]
        self.area = float (symbols [1])
        self.program = self.building.object.repertoire.get (symbols [2])
    
    def report (self, quotationFile, qualityFactor):
        print (f'        {self.name}', file = quotationFile)
        return self.program.report (quotationFile, self.building.object.normbook, self.area, qualityFactor)

class Building:
    '''Part of object that is considered an architectural unit'''
    def __init__ (self, object, lines):
        self.object = object
        self.name = lines [0]
        self.sections = [Section (self, line) for line in lines [1:]]
    
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
        self.parser = ut.Parser (objectFilePrename + '.object')
        self.name = self.parser.tree [0][0][0]
        self.normbook = rp.Normbook (self.parser.tree [0][1][-1])
        self.repertoire = rp.Repertoire (self.parser.tree [0][2][-1])            
        self.targetNorm = targetNorm         
        self.buildings = [Building (self, block) for block in self.parser.tree [1:]]
    
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

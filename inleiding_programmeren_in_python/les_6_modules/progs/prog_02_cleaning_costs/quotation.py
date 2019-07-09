import dataclasses as dc
import typing as tp

import base as bs
import repertoire as rp

@dc.dataclass
class Section:
    name: str
    area: float
    program: bs.Program
    
    def report (self, file, qualityFactor):
        print (f'        {self.name}', file = file)
        return self.program.report (file, self.area, qualityFactor)

@dc.dataclass
class Building:
    name: str
    sections: tp.List [Section]
    
    def report (self, file, qualityFactor):
        print (f'    {self.name}\n', file = file)
        area = 0
        effort = 0
        for section in self.sections:
            sectionArea, sectionEffort = section.report (file, qualityFactor)
            area += sectionArea
            effort += sectionEffort
        print (f'    Gebouw met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar\n\n', file = file)
        return area, effort
         
@dc.dataclass
class Object:
    name: str
    targetNorm: float
    buildings: tp.List [Building]
    
    def report (self, fileName, qualityFactor = 1):
        with open (fileName, 'w') as file:
            print (f'Offerte {self.name}\n', file = file)
            area = 0
            effort = 0
            for building in self.buildings:
                buildingArea, buildingEffort = building.report (file, qualityFactor)
                area += buildingArea
                effort += buildingEffort
            realNorm = area / (effort / 250)
            print (f'Object met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar', file = file)
            print (f'Dit komt neer op een uurprestatie op jaarbasis van {realNorm:.2f} m2\n\n\n', file = file)
            return realNorm / self.targetNorm
        
targetNorm = 300        
    
object = Object ('Bedrijvencomplex Technopolis', targetNorm, [
    Building ('Centrum voor Bio Engineering', [
        Section ('Gangen', 1000, rp.repertoire.get ('Verkeer')),
        Section ('Trappenhuizen', 300, rp.repertoire.get ('Verkeer')),
        Section ('Ingang Oost', 100, rp.repertoire.get ('Entree')),
        Section ('Ingang Noord', 100, rp.repertoire.get ('Entree')),
        Section ('Darwinzaal', 5000, rp.repertoire.get ('Vergader')),
        Section ('Humboldtzaal', 1000, rp.repertoire.get ('Vergader')),       
        Section ('Lamarckzaal', 800, rp.repertoire.get ('Vergader')),      
        Section ('Kantoren verkoop', 3000, rp.repertoire.get ('Kantoren zacht')),
        Section ('Gemengde ruimten R&D', 6000, rp.repertoire.get ('Kantoren hard')),
        Section ('Damestoiletten', 300, rp.repertoire.get ('Toilet')),
        Section ('Herentoiletten', 200, rp.repertoire.get ('Toilet')),
        Section ('Pantry', 15, rp.repertoire.get ('Nat')),
        Section ('Douche', 5, rp.repertoire.get ('Nat')),
    ]),
    Building ('Laagbouw Geofysisch Laboratorium', [
        Section ('Gangen', 500, rp.repertoire.get ('Verkeer')),
        Section ('Trappenhuizen', 200, rp.repertoire.get ('Verkeer')),
        Section ('Hoofdingang', 50, rp.repertoire.get ('Entree')),
        Section ('Zijingang', 50, rp.repertoire.get ('Entree')),
        Section ('Grote zaal', 1500, rp.repertoire.get ('Vergader')),
        Section ('Kleine zaal', 500, rp.repertoire.get ('Vergader')),        
        Section ('Afdeling Statistiek en Modelvorming', 300, rp.repertoire.get ('Kantoren zacht')),
        Section ('Afdeling Engineering en Data-acquisitie', 600, rp.repertoire.get ('Kantoren hard')),
        Section ('Damestoiletten', 150, rp.repertoire.get ('Toilet')),
        Section ('Herentoiletten', 100, rp.repertoire.get ('Toilet')),
        Section ('Pantry 1', 10, rp.repertoire.get ('Nat')),
        Section ('Pantry 1', 10, rp.repertoire.get ('Nat')),
        Section ('Douche 1', 3, rp.repertoire.get ('Nat')),
        Section ('Douche 1', 3, rp.repertoire.get ('Nat')),
    ]),
    Building ('Hoogbouw verzamel IT en Telecom', [
        Section ('Gangen', 200, rp.repertoire.get ('Verkeer')),
        Section ('Trappenhuizen', 50, rp.repertoire.get ('Verkeer')),
        Section ('Ingang', 20, rp.repertoire.get ('Entree')),
        Section ('Niklaus Wirth zaal', 100, rp.repertoire.get ('Vergader')),    
        Section ('Bjarne Stroustrup zaal', 100, rp.repertoire.get ('Vergader')),      
        Section ('Guido van Rossum zaal', 100, rp.repertoire.get ('Vergader')),       
        Section ('Kantoren sales', 500, rp.repertoire.get ('Kantoren zacht')),
        Section ('Kantoren development 12', 800, rp.repertoire.get ('Kantoren hard')),
        Section ('Damestoiletten', 100, rp.repertoire.get ('Toilet')),
        Section ('Herentoiletten', 60, rp.repertoire.get ('Toilet')),
        Section ('Pantry', 8, rp.repertoire.get ('Nat')),
        Section ('Douche', 2, rp.repertoire.get ('Nat')),
    ]),
])

print ('Bezig met maken van offertes')
qualityFactor = object.report ('standaard_offerte.txt')
object.report (f'aangepaste_offerte_{targetNorm}_m2.txt', qualityFactor)
print ('Offertes zijn klaar')

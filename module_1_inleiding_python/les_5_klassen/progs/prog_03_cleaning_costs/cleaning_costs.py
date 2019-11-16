import dataclasses as dc
import typing as tp

class Lookup:
    def get (self, key):
        for item in self.items:
            if item.name.startswith (key):
                return item
        raise Exception (f'No item of class {self.__class__.__name__} starts with {key}')   

@dc.dataclass
class Action:
    name: str
    norm: float
    frequency: float

    def report (self, area, qualityFactor):
        effort = self.frequency * (area / self.norm) * qualityFactor
        print (f'            {self.name:40s} kost {effort:7.2f} mens-uur per jaar')
        return effort        

@dc.dataclass
class Normbook (Lookup):
    name: str
    items: tp.List [Action]
        
@dc.dataclass
class Program:
    name: str
    actions: tp.List [Action]
            
    def report (self, area, qualityFactor):
        effort = 0
        for action in self.actions:
            effort += action.report (area, qualityFactor)
        print (f'        Sectie met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar\n')
        return area, effort
     
@dc.dataclass
class Repertoire (Lookup):
    name: str
    items: tp.List [Program]
    
@dc.dataclass
class Section:
    name: str
    area: float
    program: Program
    
    def report (self, qualityFactor):
        print (f'        {self.name}')
        return self.program.report (self.area, qualityFactor)

@dc.dataclass
class Building:
    name: str
    sections: tp.List [Section]
    
    def report (self, qualityFactor):
        print (f'    {self.name}\n')
        area = 0
        effort = 0
        for section in self.sections:
            sectionArea, sectionEffort = section.report (qualityFactor)
            area += sectionArea
            effort += sectionEffort
        print (f'    Gebouw met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar\n\n')
        return area, effort
         
@dc.dataclass
class Object:
    name: str
    targetNorm: float
    buildings: tp.List [Building]
    
    def report (self, qualityFactor = 1):
        print (f'Offerte {self.name}\n')
        area = 0
        effort = 0
        for building in self.buildings:
            buildingArea, buildingEffort = building.report (qualityFactor)
            area += buildingArea
            effort += buildingEffort
        realNorm = area / (effort / 250)
        print (f'Object met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar')
        print (f'Dit komt neer op een uurprestatie op jaarbasis van {realNorm:.2f} m2\n\n\n')
        return realNorm / self.targetNorm
         
normbook = Normbook ('Nederlands Inkoop Centrum', [
    Action ('Stofzuigen', 400, 50),
    Action ('Bijtippen', 800, 250),
    Action ('Dampmoppen', 200, 50),
    Action ('Lamparmaturen reinigen', 100, 4),
    Action ('Ramen reinigen binnezijde', 300, 25),
    Action ('Stof droog afnemen', 200, 100),
    Action ('Stof nat afnemen', 150, 11),
    Action ('Toiletten reinigen', 50, 250),
    Action ('Natte ruimten reinigen', 50, 125),
    Action ('Vloer strippen en waxen', 50, 2),
    Action ('Plinten reinigen', 600, 25),
    Action ('Bureau apparatuur vochtig reinigen', 25, 11),
    Action ('Stoelen stofzuigen', 100, 11),
])

repertoire = Repertoire ('Bedrijfsgebouwen Wetenschap en Techniek', [
    Program ('Verkeersruimten', [
        normbook.get ('Damp'),
        normbook.get ('Vloer'),
        normbook.get ('Plint'),
        normbook.get ('Ramen'),
        normbook.get ('Lamp'),
    ]),
    Program ('Entree', [
        normbook.get ('Stofzuig'),
        normbook.get ('Bijtip'),
        normbook.get ('Ramen'),
        normbook.get ('Lamp'),
    ]),
    Program ('Vergaderruimten', [
        normbook.get ('Stofzuig'),
        normbook.get ('Bijtip'),
        normbook.get ('Plint'),
        normbook.get ('Ramen'),
        normbook.get ('Lamp'),
    ]),
    Program ('Kantoren zachte vloerbedekking', [
        normbook.get ('Stofzuig'),
        normbook.get ('Bijtip'),
        normbook.get ('Plint'),
        normbook.get ('Ramen'),
        normbook.get ('Lamp'),
        normbook.get ('Bureau'),
        normbook.get ('Stoelen'),
        normbook.get ('Stof droog'),
    ]),
    Program ('Kantoren harde vloerbedekking', [
        normbook.get ('Damp'),
        normbook.get ('Vloer'),
        normbook.get ('Plint'),
        normbook.get ('Ramen'),
        normbook.get ('Lamp'),
        normbook.get ('Bureau'),
        normbook.get ('Stoelen'),
        normbook.get ('Stof nat'),
    ]),
    Program ('Toiletten', [
        normbook.get ('Toilet'),
        normbook.get ('Lamp'),
    ]),
    Program ('Natte ruimten', [
        normbook.get ('Nat'),
        normbook.get ('Lamp'),
    ]),
])
    
object = Object ('Bedrijvencomplex Technopolis', 300, [
    Building ('Centrum voor Bio Engineering', [
        Section ('Gangen', 1000, repertoire.get ('Verkeer')),
        Section ('Trappenhuizen', 300, repertoire.get ('Verkeer')),
        Section ('Ingang Oost', 100, repertoire.get ('Entree')),
        Section ('Ingang Noord', 100, repertoire.get ('Entree')),
        Section ('Darwinzaal', 5000, repertoire.get ('Vergader')),
        Section ('Humboldtzaal', 1000, repertoire.get ('Vergader')),       
        Section ('Lamarckzaal', 800, repertoire.get ('Vergader')),      
        Section ('Kantoren verkoop', 3000, repertoire.get ('Kantoren zacht')),
        Section ('Gemengde ruimten R&D', 6000, repertoire.get ('Kantoren hard')),
        Section ('Damestoiletten', 300, repertoire.get ('Toilet')),
        Section ('Herentoiletten', 200, repertoire.get ('Toilet')),
        Section ('Pantry', 15, repertoire.get ('Nat')),
        Section ('Douche', 5, repertoire.get ('Nat')),
    ]),
    Building ('Laagbouw Geofysisch Laboratorium', [
        Section ('Gangen', 500, repertoire.get ('Verkeer')),
        Section ('Trappenhuizen', 200, repertoire.get ('Verkeer')),
        Section ('Hoofdingang', 50, repertoire.get ('Entree')),
        Section ('Zijingang', 50, repertoire.get ('Entree')),
        Section ('Grote zaal', 1500, repertoire.get ('Vergader')),
        Section ('Kleine zaal', 500, repertoire.get ('Vergader')),        
        Section ('Afdeling Statistiek en Modelvorming', 300, repertoire.get ('Kantoren zacht')),
        Section ('Afdeling Engineering en Data-acquisitie', 600, repertoire.get ('Kantoren hard')),
        Section ('Damestoiletten', 150, repertoire.get ('Toilet')),
        Section ('Herentoiletten', 100, repertoire.get ('Toilet')),
        Section ('Pantry 1', 10, repertoire.get ('Nat')),
        Section ('Pantry 1', 10, repertoire.get ('Nat')),
        Section ('Douche 1', 3, repertoire.get ('Nat')),
        Section ('Douche 1', 3, repertoire.get ('Nat')),
    ]),
    Building ('Hoogbouw verzamel IT en Telecom', [
        Section ('Gangen', 200, repertoire.get ('Verkeer')),
        Section ('Trappenhuizen', 50, repertoire.get ('Verkeer')),
        Section ('Ingang', 20, repertoire.get ('Entree')),
        Section ('Niklaus Wirth zaal', 100, repertoire.get ('Vergader')),    
        Section ('Bjarne Stroustrup zaal', 100, repertoire.get ('Vergader')),      
        Section ('Guido van Rossum zaal', 100, repertoire.get ('Vergader')),       
        Section ('Kantoren sales', 500, repertoire.get ('Kantoren zacht')),
        Section ('Kantoren development 12', 800, repertoire.get ('Kantoren hard')),
        Section ('Damestoiletten', 100, repertoire.get ('Toilet')),
        Section ('Herentoiletten', 60, repertoire.get ('Toilet')),
        Section ('Pantry', 8, repertoire.get ('Nat')),
        Section ('Douche', 2, repertoire.get ('Nat')),
    ]),
])

print ('\nEerst gaan we uit van een gemiddelde situatie:\n')
qualityFactor = object.report ()
print ()

print ('\nDaarna komen we de klant tegemoet:\n')
object.report (qualityFactor)
print ()


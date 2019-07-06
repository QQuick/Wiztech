import dataclasses as dc
import typing as tp

@dc.dataclass
class Action:
    name: str
    norm: float
    frequency: float

    def report (self, area, fudgeFactor):
        effort = self.frequency * (area / self.norm) * fudgeFactor
        print (f'            {self.name} kost {effort} mens-uur per jaar')
        return effort

@dc.dataclass
class Normbook:
    name: str
    actions: tp.List [Action]

    def getAction (self, key):
        for action in self.actions:
            if action.name.startswith (key):
                return action
        raise Exception ('No action starts with', key)
        
@dc.dataclass
class Section:
    name: str
    area: float
    actions: tp.List [Action]
    
    def report (self, fudgeFactor):
        print (f'        {self.name}')
        effort = 0
        for action in self.actions:
            effort += action.report (self.area, fudgeFactor)
        print (f'        Sectie met oppervlak {self.area} m2 kost {effort} mens-uur per jaar')
        return (self.area, effort)

@dc.dataclass
class Building:
    name: str
    sections: tp.List [Section]
    
    def report (self, fudgeFactor):
        print (f'    {self.name}')
        area = 0
        effort = 0
        for section in self.sections:
            sectionArea, sectionEffort = section.report (fudgeFactor)
            area += sectionArea
            effort += sectionEffort
        print (f'    Gebouw met oppervlak {area} m2 kost {effort} mens-uur per jaar')
        return (area, effort)
         
@dc.dataclass
class Project:
    name: str
    targetNorm: float
    buildings: tp.List [Building]
    
    def report (self, fudgeFactor = 1):
        print (f'Offerte {self.name}')
        area = 0
        effort = 0
        for building in self.buildings:
            buildingArea, buildingEffort = building.report (fudgeFactor)
            area += buildingArea
            effort += buildingEffort
        realNorm = area / (effort / 250)
        print (f'Project met oppervlak {area} m2 kost {effort} mens-uur per jaar')
        print (f'Dit komt neer op een uurprestatie op jaarbasis van {realNorm}')
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
    Action ('Stoelen stofzuigen', 100, 11)
])

project = Project ('Amtelijke Molen Complex', 300, [
    Building ('Reservaat Razende Regelgevers', [
        Section ('Verkeersruimten', 1000, [
            normbook.getAction ('Damp'),
            normbook.getAction ('Vloer'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Entree', 100, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Vergaderruimten', 5000, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Kantoren zachte vloerbedekking', 3000, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
            normbook.getAction ('Bureau'),
            normbook.getAction ('Stoelen'),
            normbook.getAction ('Stof droog'),
        ]),
        Section ('Kantoren harde vloerbedekking', 6000, [
            normbook.getAction ('Damp'),
            normbook.getAction ('Vloer'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
            normbook.getAction ('Bureau'),
            normbook.getAction ('Stoelen'),
            normbook.getAction ('Stof nat'),
        ]),
        Section ('Toiletten', 200, [
            normbook.getAction ('Toilet'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Natte ruimten', 150, [
            normbook.getAction ('Nat'),
            normbook.getAction ('Lamp'),
        ]),
    ]),
    Building ('Secretariaat Stoffige Stoelenwarmers', [
        Section ('Verkeersruimten', 100, [
            normbook.getAction ('Damp'),
            normbook.getAction ('Vloer'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Entree', 10, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Vergaderruimten', 500, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Kantoren zachte vloerbedekking', 300, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
            normbook.getAction ('Bureau'),
            normbook.getAction ('Stoelen'),
            normbook.getAction ('Stof droog'),
        ]),
        Section ('Kantoren harde vloerbedekking', 600, [
            normbook.getAction ('Damp'),
            normbook.getAction ('Vloer'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
            normbook.getAction ('Bureau'),
            normbook.getAction ('Stoelen'),
            normbook.getAction ('Stof nat'),
        ]),
        Section ('Toiletten', 100, [
            normbook.getAction ('Toilet'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Natte ruimten', 75, [
            normbook.getAction ('Nat'),
            normbook.getAction ('Lamp'),
        ]),
    ]),
    Building ('Directoraat Drammende Droogstoppels', [
        Section ('Verkeersruimten', 500, [
            normbook.getAction ('Damp'),
            normbook.getAction ('Vloer'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Entree', 50, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Vergaderruimten', 2500, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Kantoren zachte vloerbedekking', 6000, [
            normbook.getAction ('Stofzuig'),
            normbook.getAction ('Bijtip'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
            normbook.getAction ('Bureau'),
            normbook.getAction ('Stoelen'),
            normbook.getAction ('Stof droog'),
        ]),
        Section ('Kantoren harde vloerbedekking', 2000, [
            normbook.getAction ('Damp'),
            normbook.getAction ('Vloer'),
            normbook.getAction ('Plint'),
            normbook.getAction ('Ramen'),
            normbook.getAction ('Lamp'),
            normbook.getAction ('Bureau'),
            normbook.getAction ('Stoelen'),
            normbook.getAction ('Stof nat'),
        ]),
        Section ('Toiletten', 400, [
            normbook.getAction ('Toilet'),
            normbook.getAction ('Lamp'),
        ]),
        Section ('Natte ruimten', 300, [
            normbook.getAction ('Nat'),
            normbook.getAction ('Lamp'),
        ]),
    ]),
])

print ('\nEerst proberen we eerlijk te zijn:\n')
fudgeFactor = project.report ()
print ()

print ('\nDaarna geven we de klant waar hij om vraagt:\n')
project.report (fudgeFactor)
print ()

print ('\nEen smerig gebouw...\n')

print (project)


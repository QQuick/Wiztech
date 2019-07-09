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

    def report (self, file, area, qualityFactor):
        effort = self.frequency * (area / self.norm) * qualityFactor
        print (f'            {self.name:40s} kost {effort:7.2f} mens-uur per jaar', file = file)
        return effort

@dc.dataclass
class Program:
    name: str
    actions: tp.List [Action]
            
    def report (self, file, area, qualityFactor):
        effort = 0
        for action in self.actions:
            effort += action.report (file, area, qualityFactor)
        print (f'        Sectie met oppervlak {area:.2f} m2 kost {effort:.2f} mens-uur per jaar\n', file = file)
        return area, effort        

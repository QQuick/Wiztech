import dataclasses as dc
import typing as tp

import base as bs
import normbook as nb
     
@dc.dataclass
class Repertoire (bs.Lookup):
    name: str
    items: tp.List [bs.Program]
    
repertoire = Repertoire ('Bedrijfsgebouwen Wetenschap en Techniek', [
    bs.Program ('Verkeersruimten', [
        nb.normbook.get ('Damp'),
        nb.normbook.get ('Vloer'),
        nb.normbook.get ('Plint'),
        nb.normbook.get ('Ramen'),
        nb.normbook.get ('Lamp'),
    ]),
    bs.Program ('Entree', [
        nb.normbook.get ('Stofzuig'),
        nb.normbook.get ('Bijtip'),
        nb.normbook.get ('Ramen'),
        nb.normbook.get ('Lamp'),
    ]),
    bs.Program ('Vergaderruimten', [
        nb.normbook.get ('Stofzuig'),
        nb.normbook.get ('Bijtip'),
        nb.normbook.get ('Plint'),
        nb.normbook.get ('Ramen'),
        nb.normbook.get ('Lamp'),
    ]),
    bs.Program ('Kantoren zachte vloerbedekking', [
        nb.normbook.get ('Stofzuig'),
        nb.normbook.get ('Bijtip'),
        nb.normbook.get ('Plint'),
        nb.normbook.get ('Ramen'),
        nb.normbook.get ('Lamp'),
        nb.normbook.get ('Bureau'),
        nb.normbook.get ('Stoelen'),
        nb.normbook.get ('Stof droog'),
    ]),
    bs.Program ('Kantoren harde vloerbedekking', [
        nb.normbook.get ('Damp'),
        nb.normbook.get ('Vloer'),
        nb.normbook.get ('Plint'),
        nb.normbook.get ('Ramen'),
        nb.normbook.get ('Lamp'),
        nb.normbook.get ('Bureau'),
        nb.normbook.get ('Stoelen'),
        nb.normbook.get ('Stof nat'),
    ]),
    bs.Program ('Toiletten', [
        nb.normbook.get ('Toilet'),
        nb.normbook.get ('Lamp'),
    ]),
    bs.Program ('Natte ruimten', [
        nb.normbook.get ('Nat'),
        nb.normbook.get ('Lamp'),
    ]),
])
    
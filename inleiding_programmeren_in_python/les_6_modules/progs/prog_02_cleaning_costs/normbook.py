import dataclasses as dc
import typing as tp

import base as bs

@dc.dataclass
class Normbook (bs.Lookup):
    name: str
    items: tp.List [bs.Action]
    
normbook = Normbook ('Nederlands Inkoop Centrum', [
    bs.Action ('Stofzuigen', 400, 50),
    bs.Action ('Bijtippen', 800, 250),
    bs.Action ('Dampmoppen', 200, 50),
    bs.Action ('Lamp-armaturen reinigen', 100, 4),
    bs.Action ('Ramen reinigen binnezijde', 300, 25),
    bs.Action ('Stof droog afnemen', 200, 100),
    bs.Action ('Stof nat afnemen', 150, 11),
    bs.Action ('Toiletten reinigen', 50, 250),
    bs.Action ('Natte ruimten reinigen', 50, 125),
    bs.Action ('Vloer strippen en waxen', 50, 2),
    bs.Action ('Plinten reinigen', 600, 25),
    bs.Action ('Bureau apparatuur vochtig reinigen', 25, 11),
    bs.Action ('Stoelen stofzuigen', 100, 11),
])

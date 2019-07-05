# === Root class

class Animal:
    def __init__ (self, sound, kind = None, name = 'naamloos'):
        self.sound = sound
        self.kind = kind
        self.name = name
        print (f'Een {self._getSpecies ()} is geinstantieerd, {self.name}')
        
    def eat (self, food = 'wat de pot schaft'):
        self._introduce ()
        print (f'en ik eet {food}')
    
    def _introduce (self):
        print (
            f'Hallo, ik ben {self.name}, mijn soort is {self._getSpecies ()}',
            end = ' '
        )
        
    def _getSpecies (self):
        return self.kind if self.kind else self.__class__.__name__
        
# === Motion classes
       
class LandAnimal (Animal):
    def move (self):
        self._introduce ()
        print (f'en ik loop')
        
class AirborneAnimal (Animal):
    def move (self):
        self._introduce ()
        print (f'en ik vlieg')

class AquaticAnimal (Animal):
    def move (self):
        self._introduce ()
        print (f'en ik zwem')
    
# === Reproduction classes
    
class OviparousAnimal (Animal):
    def reproduce (self, aantal = 6):
        self._introduce ()
        print (f'en ik leg gemiddeld {aantal} eieren')
    
class Mamal (Animal):
    def reproduce (self, aantal = 3):
        self._introduce ()
        print (f'en ik krijg gemiddeld {aantal} jongen')
    
# === Leaf classes
    
class Bird (AirborneAnimal, OviparousAnimal):
    pass

class Fish (AquaticAnimal, OviparousAnimal):
    pass
    
class Bat (AirborneAnimal, Mamal):
    def echoLocate (self):
        self._introduce ()
        print ('en ik gebruik sonar')

class Dolphin (AquaticAnimal, Mamal):
    def blowWater (self):
        self._introduce ()
        print ('en ik spuit water')

class Iguana (LandAnimal, OviparousAnimal):
    pass
    
class Velociraptor (LandAnimal, OviparousAnimal):
    pass

class Dog (LandAnimal, Mamal):
    def wagTail (self):
        self._introduce ()
        print ('en ik kwispel')

class Cat (LandAnimal, Mamal):
    def purr (self):
        self._introduce ()
        print ('en ik spin')
        
print ('\n111')
myDog = Dog ('wraff', 'Retriever', 'Bello')
yourDog = Dog ('kef', 'Poodle', 'Nouchka')

print ('\n222')    
myDog.eat ('blikvoer')
myDog.wagTail ()
yourDog.eat ('droogvoer')
myDog.reproduce (4)
yourDog.move ()
yourDog.reproduce (5)
myDog.move ()
yourDog.wagTail ()
  
print ('\n333')  
zoo = [
    Bird ('kwaak', 'Duck', 'Donald'),
    Bird ('pingping', 'Duck', 'Dagobert'),
    Bird ('roekoe', 'Pigeon'),
    Cat ('miauw', name = 'Felix'),
    Dog ('woooofff', 'Doberman', 'Nero'),
    Dog ('wrieff', 'Chihuahua', name = 'Fifi'),
    Fish ('blub', 'Herring'),
    Bat ('........ (ultrasoon)'),
    Dolphin ('knierp', name = 'Flipper'),
    Iguana ('Ssshhh'),    
]

print ('\n444')
for animal in zoo:
    animal.eat ()
    animal.move ()
    animal.reproduce ()    # Birth control
    
    try:
        animal.purr ()
    except:
        pass
        
    try:
        animal.wagTail ()
    except:
        pass
        
    print ()

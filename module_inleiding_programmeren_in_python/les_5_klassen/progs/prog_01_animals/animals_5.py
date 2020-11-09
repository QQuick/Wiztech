class Animal:
    def __init__ (self, sound, kind = None, name = 'naamloos'):
        self.sound = sound
        self.kind = kind
        self.name = name
        print (f'Een {self._getSpecies ()} is geinstantieerd, {self.name}')
        
    def eat (self, food = 'wat de pot schaft'):
        self._introduce ()
        print (f'en ik eet {food}')
    
    def reproduce (self, aantal = 3):
        self._introduce ()
        print (f'en ik krijg gemiddeld {aantal} jongen')
        
    def _introduce (self):
        print (
            f'Hallo, ik ben {self.name}, mijn soort is {self._getSpecies ()}',
            end = ' '
        )
        
    def _getSpecies (self):
        return self.kind if self.kind else self.__class__.__name__
        
class Dog (Animal):
    def move (self):
        self._introduce ()
        print (f'en ik loop')

    def wagTail (self):
        self._introduce ()
        print ('en ik kwispel')
        
class Cat (Animal):        
    def move (self):
        self._introduce ()
        print (f'en ik sluip')

    def purr (self):
        self._introduce ()
        print ('en ik spin')
                
print ('\n111')
myDog = Dog ('wraff', 'Retriever', 'Bello')
yourDog = Dog ('kef', 'Poodle', 'Nouchka')

print ('\n222')
myCat = Cat ('mraauw', 'Streetcat', 'Thomas')

print ('\n333')    
myDog.eat ('blikvoer')
myDog.wagTail ()
yourDog.eat ('droogvoer')
myDog.reproduce (4)
yourDog.move ()
yourDog.reproduce (5)
myDog.move ()
yourDog.wagTail ()

print ('\n444')
myCat.eat ('Fish')
myCat.move ()
myCat.reproduce ()
myCat.purr ()
  
print ('\n555')  
zoo = [
    Cat ('miauw', name = 'Felix'),
    Dog ('woooofff', 'Doberman', 'Nero'),
    Dog ('wrieff', 'Chihuahua', name = 'Fifi'),
]

print ('\n666')
for animal in zoo:
    animal.eat ()
    animal.move ()
    animal.reproduce ()
    
    try:
        animal.purr ()
    except:
        pass
        
    try:
        animal.wagTail ()
    except:
        pass
        
    print ()

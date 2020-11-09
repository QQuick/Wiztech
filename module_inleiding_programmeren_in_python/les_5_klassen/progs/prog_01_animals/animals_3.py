class Dog:
    def __init__ (self, sound, kind = None, name = 'naamloos'):
        self.sound = sound
        self.kind = kind
        self.name = name
        print (f'Een {self._getSpecies ()} is geinstantieerd, {self.name}')
        
    def eat (self, food = 'wat de pot schaft'):
        self._introduce ()
        print (f'en ik eet {food}')
        
    def move (self):
        self._introduce ()
        print (f'en ik loop')
    
    def reproduce (self, aantal = 3):
        self._introduce ()
        print (f'en ik krijg gemiddeld {aantal} jongen')
        
    def wagTail (self):
        self._introduce ()
        print ('en ik kwispel')

    def _introduce (self):
        print (
            f'Hallo, ik ben {self.name}, mijn soort is {self._getSpecies ()}',
            end = ' '
        )
        
    def _getSpecies (self):
        return self.kind if self.kind else self.__class__.__name__
                
myDog = Dog ('wraff', 'Retriever', 'Bello')
yourDog = Dog ('kef', 'Poodle', 'Nouchka')
   
myDog.eat ('blikvoer')
myDog.wagTail ()
yourDog.eat ('droogvoer')
myDog.reproduce (4)
yourDog.move ()
yourDog.reproduce (5)
myDog.move ()
yourDog.wagTail ()

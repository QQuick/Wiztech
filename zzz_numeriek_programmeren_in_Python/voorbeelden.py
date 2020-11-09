import collections.abc as ab
import random as rd
import types as tp


print ()

'''
Een boek met bladzijden is een iterable.
Een bladwijzer is een iterator.

Aan iterables, zoals een lijst, kun je een iterator vragen.
Een lijst kan niet zelf z'n iteration state bijhouden,
want dan kun je geen geneste loops maken die allebei onafhankelijk van elkaar door de lijst lopen.
Dus een lijst 'has' iterators in plaats van een lijst 'is an' iterator.

Elke iterator is ook een iterable.
Dit is zo om  praktische redenen.
Er zijn namelijk iterators die niet naar een plek in een iterable verwijzen, zoals class based iterators en generators.
Dit houdt in dat je deze iterators normaal gesproken niet in de kop van een for-lus kunt gebruiken,
want een for-lus verwacht een iterable, iets waarvan hij een iterator kan opvragen.

Door nu iterators zo te maken dat je er een iterator van kunt opvragen, namelijk zichzelf,
kunnen iterators die niet gekoppeld zijn aan een "echte" iterable, toch in de kop van een for-lus gebruiken.
Het feit dat iterators een iterator kunnen leveren maakt ze tevens iterables.
Merk op dat de class naam iterable hier wel op een beetje kromme manier wordt gebruikt:
een bladwijzer zonder boek, die zelf teksten genereert, afhankelijk van waar hij is.
Een soort Markov bladwijzer.

Technische details:

Een iterable heeft een __iter__ method, waarmee je hem om een iterator over zichzelf kunt vragen.
Een iterator heeft een __next__ method, waarmee je hem een element verder kunt laten wijzen.
Hij heeft echter ook een __iter__ method, omdat een iterator een speciaal soort iterable is.

Een generator is een implementatie van een iterator door middel van een suspendable function,
dus een specialisatie van iterator, niet qua interface maar qua implementation.
Bij een suspendable function wordt het frame van die function bevroren.
Omdat dit kan is 't geen STACK frame, het wordt namelijk niet vernietigd bij passeren van een yield,
in tegenstelling tot bij 't passeren van een return.
'''

print ('=== general ===')
print ('iterator is subclass of iterable:', issubclass (ab.Iterator, ab.Iterable))
print ('generator is subclass of iterator:', issubclass (ab.Generator, ab.Iterator))
print ()

print ('=== list === ')

aList = [1, 2, 3]

print ('is iterable:', isinstance (aList, ab.Iterable))
print ('is iterator:', isinstance (aList, ab.Iterator))
print ('has iterator:', isinstance (iter (aList), ab.Iterator))
print ('has iterable:', isinstance (iter (aList), ab.Iterable))
print ()

print ('=== iterator class ===')

class RandomFloats:
    def __init__ (self, maxCount):
        self.maxCount = maxCount
        self.count = 0

    def __iter__ (self):
        return self
        
    def __next__ (self):
        if self.count < self.maxCount:
            self.count += 1
            return rd.random ()
        else:
            raise StopIteration ()

randomFloats = RandomFloats (10)

print ('is iterable:', isinstance (randomFloats, ab.Iterable))
print ('is iterator:', isinstance (randomFloats, ab.Iterator))
print ('has iterator:', isinstance (iter (randomFloats), ab.Iterator))
print ('has iterable:', isinstance (iter (randomFloats), ab.Iterable))
print ('is generator:', isinstance (randomFloats, ab.Generator))

for aRandomFloat in randomFloats:
    print (aRandomFloat)
print ()

print ('=== generator function ===')

def randomFloatsFactory (maxCount):
    count = 0
    while count < maxCount:
        yield rd.random ()
        count += 1

randomFloats2 = randomFloatsFactory (10)

print ('is iterable:', isinstance (randomFloats2, ab.Iterable))
print ('is iterator:', isinstance (randomFloats2, ab.Iterator))
print ('is generator:', isinstance (randomFloats2, ab.Generator))
print ('has iterable:', isinstance (iter (randomFloats2), ab.Iterable))
print ('has iterator:', isinstance (iter (randomFloats2), ab.Iterator))
print ('has generator:', isinstance (iter (randomFloats2), ab.Generator))
for aRandomFloat in randomFloats2:
    print (aRandomFloat)
print ()

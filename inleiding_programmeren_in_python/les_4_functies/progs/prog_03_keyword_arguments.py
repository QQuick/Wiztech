import math as mt

def getPerimeter (radius = None, diameter = None):
    if radius != None:
        return 2 * mt.pi * radius
    elif diameter != None:
        return mt.pi * diameter

print ()
print ('Omtrek als straal = 5   :', getPerimeter (radius = 5))
print ('Omtrek als diameter = 10:', getPerimeter (diameter = 10))
print (getPerimeter ())
print ()


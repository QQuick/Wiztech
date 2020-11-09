import math as mt

def getPerimeter (radius, diameter):
    if radius != None:
        return 2 * mt.pi * radius
    elif diameter != None:
        return mt.pi * diameter

print ()
print ('Omtrek als straal = 5   :', getPerimeter (5, None))
print ('Omtrek als diameter = 10:', getPerimeter (None, 10))
print (getPerimeter (None, None))



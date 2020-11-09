def average2 (x0, x1):
    return (x0 + x1) / 2
    
a = average2 (3, 7)    
b = average2 (-3, -7)
c = average2 (a, b)
print ('Met average2 en variabelen    :', a, b, c)

print ('Met average2 zonder variabelen:', 
    average2 (3, 7),
    average2 (-3, -7),
    average2 (
        average2 (3, 7),
        average2 (-3, -7)
    )
)    



def average3 (x0, x1, x2):
    return (x0 + x1 + x2) / 3
    
print ('Met average3                  :', average3 (4,  5, -12)) 



def averageOfList (aList):
    total = 0
    for x in aList:
        total += x
    return total / len (aList)

print ('Met averageOfList             :', averageOfList ([3, 7]), averageOfList ([4, 8, 10]), averageOfList ([4, 6, 18, 20, -5, 10]))



def average (*args):
    total = 0
    for x in args:
        total += x
    return total / len (args)
     
print ('Met average                   :', average (3, 7), average (4, 8, 10), average (4, 6, 18, 20, -5, 10))

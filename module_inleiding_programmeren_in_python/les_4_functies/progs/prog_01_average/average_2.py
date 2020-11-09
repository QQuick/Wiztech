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


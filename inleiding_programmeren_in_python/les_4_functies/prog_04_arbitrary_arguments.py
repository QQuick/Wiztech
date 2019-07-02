def printLabeled (**kwargs):
    for key in sorted (kwargs):
        print (f'{key:10s}: {kwargs [key]}')
    print ()
        
printLabeled (
    artikel = 'sportschoen',
    maat = 7.5,
    aantal = 3
)

printLabeled (
    artikel = 'teenslipper',
    maat = 6,
    aantal = 5
)

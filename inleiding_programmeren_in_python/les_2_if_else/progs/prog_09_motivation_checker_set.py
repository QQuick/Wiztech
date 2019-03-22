likesComputers = input ('Vind je werken met de computer leuk? <j/n> ') in {'j', 'J', 'ja', 'Ja', 'y', 'Y', 'yes', 'Yes'} 
likesLearning = input ('Houd je ervan nieuwe dingen te leren? <j/n> ') in {'j', 'J', 'ja', 'Ja', 'y', 'Y', 'yes', 'Yes'}

print ()
print ('likesComputers:', likesComputers)
print ('likesLearning:', likesLearning)
print ()

if likesComputers:
    if likesLearning:
        print ('Als je dat allebei leuk vind, denk ik dat je veel plezier van Python kunt hebben!')
    else:
        print ('Tja, soms kom je er niet onder uit om nieuwe dingen te leren, maar in ieder geval werk je nu inderdaad met de computer.')
else:
    if likesLearning:
        print ('Als je werken met de computer niet leuk vindt maar leren wel, kun je misschien beter iets anders leren dan programmeren.')
    else:
        print ('Je houdt niet van werken met de computer en van nieuwe dingen leren? Bijzonder dat je dan toch deze cursus doet... ')
    
    
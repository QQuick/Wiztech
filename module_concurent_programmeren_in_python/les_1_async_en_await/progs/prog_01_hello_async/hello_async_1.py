import time as tm

def sayAfter (delay, what):
    tm.sleep (delay)
    print (tm.strftime ('%X'), what)

print ()
print (tm.strftime ('%X'), 'Begin programma')

sayAfter (1, 'Hallo')
sayAfter (2, 'Wereld')

print (tm.strftime ('%X'), 'Einde programma')
print ()

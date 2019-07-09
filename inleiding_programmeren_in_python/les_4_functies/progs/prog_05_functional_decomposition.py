def getAnswerOnce (tableNr, lineNr):
    return int (input (f'{lineNr} x {tableNr} = '))
    
def getAnswerUntilRight (tableNr, lineNr):
    while getAnswerOnce (tableNr, lineNr) != tableNr * lineNr:
        print ('Helaas, niet goed, probeer \'t nog eens...')
        
def practiceOneTable (tableNr):
    for lineNr in range (1, 11):
        getAnswerUntilRight (tableNr, lineNr)
    print ()
        
def practiceAllTables ():
    print ('\nDaar gaat ie...\n')
    for tableNr in range (1, 11):
        practiceOneTable (tableNr)
    print ('Klaar!\n')
        
practiceAllTables ()

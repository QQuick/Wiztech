startTableNr = 1
nrOfTables = 10

startLineNr = 1
nrOfLines = 10

for tableNr in range (startTableNr, startTableNr + nrOfTables):
    print (f'De tafel van {tableNr} is:')
    for lineNr in range (startLineNr, startLineNr + nrOfLines):
        print (f'{lineNr} x {tableNr} = {lineNr * tableNr}')
    print ()

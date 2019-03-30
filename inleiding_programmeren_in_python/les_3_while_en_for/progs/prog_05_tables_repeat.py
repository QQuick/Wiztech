startTableNr = 1
nrOfTables = 10

startLineNr = 1
nrOfLines = 10

for tableNr in range (startTableNr, startTableNr + nrOfTables):
    for lineNr in range (startLineNr, startLineNr + nrOfLines):
        while True:
            answer = int (input (f'Hoeveel is {lineNr} x {tableNr}? '))
            if answer == lineNr * tableNr:
                break;
            else:
                print (f'Helaas, {lineNr} x {tableNr} is geen {answer}...')
    print ()

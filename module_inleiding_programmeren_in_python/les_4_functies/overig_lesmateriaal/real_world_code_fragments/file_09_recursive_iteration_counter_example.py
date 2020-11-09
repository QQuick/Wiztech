def printNextInteger (i = 0):
    print (i)
    if i < 100:
        printNextInteger (i + 1)

printNextInteger ()

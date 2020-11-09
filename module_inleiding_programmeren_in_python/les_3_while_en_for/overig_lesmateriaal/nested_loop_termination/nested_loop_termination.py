try:
    for i in range (10):
        for j in range (10):
            print ((i, j), end = ' ')
            if i == 3 and j == 4:
                raise StopIteration
except StopIteration:
    pass

print ()

for i in range (10):
    for j in range (10):
        print ((i, j), end = ' ')
        if i == 3 and j == 4:
            break
    else:
        continue
    break

print ()

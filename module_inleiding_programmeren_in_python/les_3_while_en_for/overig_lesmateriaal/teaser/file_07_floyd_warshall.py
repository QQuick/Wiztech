connectivityMatrix = [
    [ 0, 30,  2,  7],
    [ 2,  0, 30, 90],
    [90,  2,  0,  4],
    [10,  5, 30,  0]
]

vertexIndices = range (len (connectivityMatrix))

for iStart in vertexIndices:
    for iEnd in vertexIndices:
        for iVia in vertexIndices:
            connectivityMatrix [iStart][iEnd] = min (
                connectivityMatrix [iStart][iEnd],
                connectivityMatrix [iStart][iVia] + connectivityMatrix [iVia][iEnd]
            )
            
for row in connectivityMatrix:
    print (row)

vec0 = (1, 2, 3)
vec1 = (4, 5, 6)

innerProd = sum (e0 * e1 for e0, e1 in zip (vec0, vec1))    # What EXACTLY happens here?

print (innerProd)
	
'''
innerProd = 0
for index in range (len (vec0)):
    innerProd += vec0 [index] * vec1 [index]
'''

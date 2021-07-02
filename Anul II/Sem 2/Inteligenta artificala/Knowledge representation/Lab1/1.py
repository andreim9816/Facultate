import numpy as np

n = int(input("n = ")) # cate numere sunt

vect = np.zeros((n , 1))

for index in range(n):
    vect[index] = int(input())
vect = np.ravel(vect)

inf = 2 ** 64
max1 = -inf
max2 = -inf

for elem in vect:
    if elem > max1:
        max2 = max1
        max1 = elem
    elif elem > max2 and elem != max1:
        max2 = elem

if max1 != inf and max2 != inf:
    print(max1 , ' ' , max2)
else: print('imposibil')

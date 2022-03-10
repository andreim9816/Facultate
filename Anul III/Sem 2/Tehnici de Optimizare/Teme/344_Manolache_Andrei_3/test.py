import math

def f(x):
    return x * math.exp(2*x/61-x*x/61)

v = (61 + math.sqrt(4209))/4

delta = 4/(61*61) + 8/61
x1=(2/61+math.sqrt(delta))*61/4
x2=(2/61-math.sqrt(delta))*61/4

print(f(1/2+math.sqrt(123)/2))
print(x2)
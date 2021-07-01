# Manolache Andrei
# 344
# Tema 1

import numpy as np
from scipy import optimize
import random

"""Am ales m = n = p = 2"""

##################################### Ex 2a)

"""Generam datele, folosindu-ne de o functie genRand() care genereaza un numar aleator intre -10 si 10"""


def genRand():
    startRandom = -10
    endRandom = 10
    return random.randrange(startRandom, endRandom)


A = np.array([
    [genRand(), genRand()],
    [genRand(), genRand()]
])
b = np.array([genRand(), genRand()])
C = np.array([
    [genRand(), genRand()],
    [genRand(), genRand()]
])
d = np.array([genRand(), genRand()])

"""Tinem minte punctele obtinute la fiecare iteratie"""
accumulator = list()

"""Functie care calculeaza ||Ax-b||^2(2)"""


def f(x, A, b):
    # Memoreaza sirul aproximarilor solutiilor
    accumulator.append(x)
    return 0.5 * x.T @ A.T @ A @ x - b.T @ A @ x - 0.5 * b.T @ b


"""Functia de constrangere definita Cx <= d"""


def constraint(x):
    global C
    global d
    return np.atleast_1d(d - C @ x)


"""Apelam functia de minimizare, respectand constrangerea, pornind din punctul (-3,-2)"""
optimize.minimize(fun=f, args=(A, b), x0=np.array([-3.0, -2.0]), method="SLSQP",
                  constraints={"fun": constraint, "type": "ineq"})
accumulated = np.array(accumulator)

print("A=", A)
print("b=", b)
print("C=", C)
print("d=", d)
print("Solutia este punctul", accumulated[-1])

##################################### Ex 2b) i)

"""Punctele de extrem neconstrans ale 1/2 ||Ax-b||_2^2 satisfac conditiile de ordin I: A.T@(Ax-b)=0. Astfel generam C, d
Desfacem si obtinem A.T @ A @ x = A.T @ b. Alegem C = A.T @ A si d = A.T @ b, deci Cx = d, deci este respectata Cx <= d"""
print("\n--------------------------------------------------------------------\n")

A = np.array([
    [genRand(), genRand()],
    [genRand(), genRand()]
])
b = np.array([genRand(), genRand()])

C = A.T @ A
d = A.T @ b

print("A=", A)
print("b=", b)
print("C=", C)
print("d=", d)

##################################### Ex 2b) ii)

"""Punctele de extrem neconstrans ale 1/2 ||Ax-b||_2^2 satisfac conditiile de ordin I: A.T@(Ax-b)=0. Astfel generam C, d
Desfacem si obtinem A.T @ A @ x = A.T @ b. Alegem C = A.T @ A si d = A.T @ b - 1. Astfel, relatia se transforma Cx = d + 1, x punct de extrem si nu va fi respectata relatia Cx <= d"""
print("\n--------------------------------------------------------------------\n")
A = np.array([
    [genRand(), genRand()],
    [genRand(), genRand()]
])
b = np.array([genRand(), genRand()])

C = A.T @ A
d = A.T @ b - 1

print("A=", A)
print("b=", b)
print("C=", C)
print("d=", d)

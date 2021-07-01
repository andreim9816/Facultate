# Manolache Andrei
# 344
# Tema 3

import matplotlib.pyplot as plt
import numpy as np
from numpy import linalg as la
import random
import cvxpy as cp

"""Generam datele, folosindu-ne de o functie genRand() care genereaza un numar aleator intre -5 si 5"""


def genRand():
    startRandom = -5
    endRandom = 5
    return random.randrange(startRandom, endRandom)


"""Definim functia pe care vrem sa o minimizam"""


def func(x):
    global a
    return 0.5 * x.T @ (a @ a.T + np.eye(a.size)) @ x


"""Functie care calculeaza gradientul"""


def gradient(x, Q):
    return Q @ x


"""Functie care calculeaza eroarea absoluta """


def cond_oprire_err_absolut(x_k, f_x_minim):
    return func(x_k) - f_x_minim


"""Functie care calculeaza norma gradientului intr-un punct"""


def cond_oprire_norma(x_new, x_old):
    return la.norm(x_new - x_old)


"""Functie care il calculeaza pe Q"""


def calcul_Q(a):
    return a @ a.T + np.eye(a.size)


"""Functie care il calculeaza pe alpha """


def calcul_alpha(Q):
    Lips = np.max(la.eigvals(Q))
    alpha = 1 / Lips
    return alpha


"""Functie care calculeaza proiectia unui punct pe multimea fezabila"""


def proiectie(x, a, b=1):
    return x - ((a.T @ x - b) / (la.norm(a) ** 2)) * a


"""Functie care calculeaza alpha la pasul curent, pentru varianta cu backtracking"""


def alege_alpha(x_k_old, a, b, Q):
    """Setam alpha_k_0 initial"""
    alpha = 0.25
    grad = gradient(x_k_old, Q)
    x_new = proiectie(x_k_old - alpha * grad, a, b)
    """Alegem c si p"""
    c = 0.1
    p = 0.1
    """Se calculeaza "x_k+1" cu un alpha ales de noi, dupa care se updateaza pana il gasim pe x_k+1"""
    while (func(proiectie(x_k_old - alpha * grad, a, b)) > func(x_k_old) - c / alpha * (la.norm(x_new - x_k_old) ** 2)):
        alpha *= p
        x_new = proiectie(x_k_old - alpha * grad, a, b)

    return alpha, x_new


"""Functie care minimizeaza functia respectiva, folosind metoda gradientului proiectat cu pas constant"""


def gradient_pas_constant(Q, x, cond_oprire, val_min):
    """Array cu sirul solutiilor obtinute"""
    sol = []
    x_old = x
    """Pt calculul cu norma, pt x0, nu putem aplica x_k+1 - x_k"""
    if cond_oprire != "norma":
        sol = [cond_oprire_err_absolut(x, val_min)]

    alpha = calcul_alpha(Q)
    """Numarul de iteratii"""
    k = 0
    while True:
        """Calculeaza alpha, face update lui x, adauga noua eroare obtinuta"""
        grad = gradient(x_old, Q)
        x_new = proiectie(x_old - alpha * grad, np.ones(n), 1)
        if cond_oprire == "norma":
            criteriu_stop = cond_oprire_norma(x_new, x_old)
        else:
            criteriu_stop = cond_oprire_err_absolut(x_new, val_min)
        """Adauga in sirul solutiilor"""
        sol.append(criteriu_stop)
        k += 1
        """Verifica conditie de oprire"""
        if criteriu_stop < eps:
            break
        """Update"""
        x_old = x_new
    return x, sol, k


def gradient_pas_bkt(Q, x, cond_oprire, x_min, a, b):
    """Array cu sirul solutiilor obtinute"""
    sol = []
    x_old = x
    """Pt calculul cu norma, pt x0, nu putem aplica x_k+1 - x_k"""
    if cond_oprire != "norma":
        sol = [cond_oprire_err_absolut(x, x_min)]

    """Numarul de iteratii"""
    k = 0

    while True:
        """Calculeaza alpha, face update lui x, adauga noua eroare obtinuta"""
        alpha, x_new = alege_alpha(x_old, a, b, Q)
        if cond_oprire == "norma":
            criteriu_stop = cond_oprire_norma(x_new, x_old)
        else:
            criteriu_stop = cond_oprire_err_absolut(x_new, x_min)
        """Adauga in sirul solutiilor"""
        sol.append(criteriu_stop)
        k += 1
        """Verifica conditie de oprire"""
        if criteriu_stop < eps:
            break
        """Update"""
        x_old = x_new
    return x, sol, k


"""Alegem dimensiunea lui n si il generam pe a"""
n = 2
a = np.array([genRand() for i in range(n)])
"""Setam eroarea, calculam pe Q si setam punctul de start"""
eps = 1e-3
Q = calcul_Q(a)
x0 = np.array([2, -1])

"""Calculeaza valoarea minima a functiei folosind CVXPY"""
z = cp.Variable(n)
b = 1
objective = cp.Minimize(0.5 * cp.quad_form(z, Q))
constraints = [np.ones(n) @ z == b]
prob = cp.Problem(objective, constraints)
result = prob.solve(solver='CVXOPT')
sol = prob.value

"""Calculeaza sirul solutiilor pt fiecare metoda si tipul erorii"""
x_sol_constant_norma = gradient_pas_constant(Q, x0, "norma", sol)
x_sol_bkt_norma = gradient_pas_bkt(Q, x0, "norma", sol, np.ones(n), 1)

x_sol_constant_err_abs = gradient_pas_constant(Q, x0, "eroare", sol)
x_sol_bkt_err_abs = gradient_pas_bkt(Q, x0, "eroare", sol, np.ones(n), 1)

"""Cele 2 gragice"""

"""Graficul cu eroarea fata de eroarea absoluta"""
plt.figure(0)
plt.xlabel("k")
plt.ylabel("f(x_k) - f*")
plt.title("Figura 1")
plt.plot([i for i in range(0, x_sol_constant_err_abs[2])], x_sol_constant_err_abs[1][1:], c="orange",
         label="Pas constant")
plt.plot([i for i in range(0, x_sol_bkt_err_abs[2])], x_sol_bkt_err_abs[1][1:],
         c="blue",
         label="Pas backtracking")
plt.legend()
plt.show()

"""Graficul cu eroarea fata de norma"""
plt.figure(1)
plt.xlabel("k")
plt.ylabel("||x_k+1 - x_k||")
plt.title("Figura 2")
plt.plot([i for i in range(1, x_sol_constant_norma[2])], x_sol_constant_norma[1][1:], c="orange",
         label="Pas constant")
plt.plot([i for i in range(0, x_sol_bkt_norma[2])], x_sol_bkt_norma[1][:], c="blue",
         label="Pas backtracking")
plt.legend()
plt.show()

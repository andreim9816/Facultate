# Manolache Andrei
# 344
# Tema 2

import matplotlib.pyplot as plt
import numpy as np
from numpy import linalg as la
import random
from scipy import optimize

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


def gradient(x):
    global a
    return (a @ a.T + np.eye(a.size)) @ x


"""Functie care minimizeaza functia respectiva, folosind metoda gradientului cu pas ideal"""


def gradient_pas_ideal(Q, x, cond_oprire, x_min):
    """Array cu sirul solutiilor obtinute"""
    if cond_oprire == "norma":
        sol = [cond_oprire_norma(x)]
    else:
        sol = [cond_oprire_err_absolut(x, x_min)]

    """Numarul de iteratii"""
    k = 0
    while True:
        """Calculeaza alpha, face update lui x, adauga noua eroare obtinuta"""
        grad = gradient(x)
        alpha = (la.norm(grad) ** 2) / (grad.T @ Q @ grad)
        x = x - alpha * grad

        if cond_oprire == "norma":
            criteriu_stop = cond_oprire_norma(x)
        else:
            criteriu_stop = cond_oprire_err_absolut(x, x_min)
        sol.append(criteriu_stop)
        k += 1

        if criteriu_stop < eps:
            break
    return x, sol, k


"""Functie care calculeaza eroarea absoluta """


def cond_oprire_err_absolut(x_k, f_x_minim):
    return func(x_k) - f_x_minim


"""Functie care calculeaza norma gradientului intr-un punct"""


def cond_oprire_norma(x_k):
    return la.norm(gradient(x_k))


"""Functie care calculeaza alpha la pasul curent, pentru varianta cu backtracking"""


def alege_alpha(x_k):
    """Setam alpha_k_0 initial"""
    alpha = 1
    """Alegem c si p"""
    c = 0.5
    p = 0.5
    while func(x_k - alpha * gradient(x_k)) > func(x_k) - c * alpha * la.norm(gradient(x_k)) ** 2:
        alpha *= p

    return alpha


def gradient_backtracking(x, cond_oprire, x_min):
    """Array cu sirul solutiilor obtinute"""
    if cond_oprire == "norma":
        sol = [cond_oprire_norma(x)]
    else:
        sol = [cond_oprire_err_absolut(x, x_min)]

    """Numarul de iteratii"""
    k = 0
    while True:
        """Calculeaza alpha, face update lui x, adauga in array-ul cu solutiile noua eroare"""
        grad = gradient(x)
        alpha = alege_alpha(x)
        x = x - alpha * grad

        if cond_oprire == "norma":
            criteriu_stop = cond_oprire_norma(x)
        else:
            criteriu_stop = cond_oprire_err_absolut(x, x_min)

        sol.append(criteriu_stop)
        k += 1

        if criteriu_stop < eps:
            break
    return x, sol, k


"""Alegem dimensiunea lui n si il generam pe a"""
n = 2
a = np.array([genRand() for i in range(n)])
"""Setam eroarea, calculam pe Q si setam punctul de start"""
eps = 1e-5
Q = a @ a.T + np.eye(n)
x0 = np.array([-1, 2])

"""Calculeaza valoarea minima a functiei"""
x_sol_min = optimize.minimize(func, np.array([2, 3]), method="SLSQP").jac[0]

""" Calculeaza sirul solutilor pentru fiecare metoda si tipul erorii"""
x_sol_ideal_norma = gradient_pas_ideal(Q, x0, "norma", x_sol_min)
x_sol_ideal_err_abs = gradient_pas_ideal(Q, x0, "eroare", x_sol_min)

x_sol_bt_norma = gradient_backtracking(x0, "norma", x_sol_min)
x_sol_bt_err_abs = gradient_backtracking(x0, "eroare", x_sol_min)

"""Afisarea celor 2 grafice"""

"""Graficul cu eroarea fata de eroarea absoluta"""
plt.figure(0)
plt.xlabel("k")
plt.ylabel("f(x_k) - f*")
plt.title("Figura 1")
plt.plot([i for i in range(0, x_sol_ideal_err_abs[2] + 1)], x_sol_ideal_err_abs[1][:], c="orange", label="Pas ideal")
plt.plot([i for i in range(0, x_sol_bt_err_abs[2] + 1)], x_sol_bt_err_abs[1][:], c="blue", label="Pas backtracking")
plt.legend()
plt.show()

"""Graficul cu eroarea fata de norma"""
plt.figure(1)
plt.xlabel("k")
plt.ylabel("||∇f(x_k)||")
plt.title("Figura 2")
plt.plot([i for i in range(0, x_sol_ideal_norma[2] + 1)], x_sol_ideal_norma[1][:], c="orange", label="Pas ideal")
plt.plot([i for i in range(0, x_sol_bt_norma[2] + 1)], x_sol_bt_norma[1][:], c="blue", label="Pas backtracking")
plt.legend()
plt.show()

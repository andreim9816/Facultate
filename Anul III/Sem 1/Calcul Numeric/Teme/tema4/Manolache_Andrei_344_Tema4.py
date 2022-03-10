import numpy as np
import matplotlib.pyplot as plt
import sympy as sp
import scipy.stats as st
from scipy.integrate import quad

########################################################################################################################
# Exercitiul 1
########################################################################################################################

"""Afisare eroare de trunchiere"""
def plot_eroare_trunchiere(x_domain, values, label, xlabel, ylabel):
    plt.figure()
    plt.plot(x_domain, values, c='k', linewidth=2, label=label)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid()
    plt.legend()
    plt.show()


"""Calculul erorii maxime de trunchiere"""
def eroare_trunchiere(f_x, f_x_aprox):
    return np.max(np.abs(f_x - f_x_aprox))


"""" Metoda care primeste ca input o expresie simbolica si variabila simbolica si care returneaza expresia
    si a 2a derivata acesteia convertite astfel incat sa returneze float-uri."""
def f_df_df_to_float(expresie, x):
    dfdf = expresie.diff().diff()
    expresie = sp.lambdify(x, expresie)
    dfdf = sp.lambdify(x, dfdf)
    return expresie, dfdf


""" Functie care aproximeaza cea de-a 2-a derivata folosind metoda diferentelor finite """
def diferente_finite(X, Y):
    """Initializari"""
    dfdf = np.zeros(len(X))
    dfdf[0] = dfdf[-1] = np.nan

    """Calculeaza valoarea celei de-a doua derivate in fiecare punct"""
    for i in range(1, len(X) - 1):
        dfdf[i] = (Y[i + 1] - 2 * Y[i] + Y[i - 1]) / np.power((X[i + 1] - X[i]), 2)

    return dfdf


""" Foloseste metoda de mai sus pentru a calcula f(x) si f"(x) pe domeniul [-pi/2, pi] pentru functia
    f(x) = cos(0.7x)
    Disecritizzam intervalul
"""
x = sp.symbols('x')

interval = [-np.pi/2, np.pi]
domeniu = np.linspace(interval[0], interval[1], 300)
functie1 = sp.cos(0.7 * x)

f, dfdf = f_df_df_to_float(functie1, x)

""" Eroarea si N-ul """
err = 1e-5
N = 2

while True:
    """Updatam N-ul"""
    N += 1

    """Disecritizare, construieste punctele din capete"""
    x_discret = np.zeros(N + 2)
    x_discret[1: -1] = np.linspace(interval[0], interval[1], N)
    h = x_discret[2] - x_discret[1]  # Distanta (echidistanta) dintre 2 puncte consecutive a disecritizarii
    x_discret[0] = x_discret[1] - h
    x_discret[-1] = x_discret[-2] + h

    """Calculam valorile functiei in care a avut loc disecritizarea"""
    y_discret = f(x_discret)

    """ Calculeaza aproximarea celei de-a 2a derivate"""
    dfdf_finite_aprox = diferente_finite(x_discret, y_discret)

    """ Calculeaza valorile exacte ale celei de-a 2a derivate strict in punctele in care a avut loc desicretizarea"""
    y_dfdf = dfdf(x_discret)

    """ Eroarea curenta (diferenta ditre a 2-a derivata si aproximarea ei). Punctele din capete nu se iau in considerare"""
    err_curr = eroare_trunchiere(dfdf_finite_aprox[1: -1], y_dfdf[1: -1])

    if err_curr <= err:
        err_min = err_curr
        sol_min_aproximare = dfdf_finite_aprox[1: -1]
        N_min = N
        break

print("Pentru N =", N_min, " s-a obtinut eroarea ", err_min)

"""Afisare grafic"""
plt.figure()
"""Afiseaza aproximarea derivatei 2"""
plt.plot(x_discret[1: -1], sol_min_aproximare, c='green', linewidth=3, label='Aproximarea celei de-a 2a derivate')
"""Afiseaza valorile exacte ale derivatei 2"""
plt.plot(domeniu, dfdf(domeniu), c='red', linewidth=1, label='Cea de-a 2-a derivata a functiei')
plt.xlabel('x')
plt.ylabel('values')
plt.grid()
plt.title('Aproximarea celei de-a 2-a derivate, N= ' + str(N_min))
plt.legend()
plt.show()

"""Afiseaza grafic eroare de trunchiere"""
absv = np.abs(dfdf_finite_aprox[1: -1] - y_dfdf[1: -1])
plot_eroare_trunchiere(x_discret[1: -1], np.abs(sol_min_aproximare - y_dfdf[1: -1]), 'Eroare trunchiere N =' + str(N_min), 'x', 'abs(y_aprox - y_exact)')

########################################################################################################################
# Exercitiul 2
########################################################################################################################

""" Defineste datele """
interval = [-12, 12]
a = interval[0]
b = interval[1]
sigma = 1.2

""" Functia care trebuie integrata """
def functie2(x):
    return np.e ** ((- np.power(x, 2))/(2 * np.power(sigma, 2))) / (sigma * np.sqrt(2 * np.pi))

""" Functia care calculeaza valoarea aproximativa a integralei conform formulelor de cuadratura sumate"""
def integrare(f, x, metoda="dreptunghi"):

    """ Distanta (echidistanta intre 2 puncte consecutive a disecritizarii)"""
    h = x[1] - x[0]

    """ Dimensiunea array-ului de puncte"""
    m = len(x)

    """m trebuie sa fie impar!!!!"""
    assert m % 2 == 1, 'Vectorul trebuie sa aiba un numar impar de elemente!'

    """ Verifica metoda aleasa"""
    if metoda.lower() == "dreptunghi":
        return 2 * h * sum(map(f, x[1: m: 2]))
    elif metoda.lower() == "trapez":
        return h / 2 * (f(x[0]) + f(x[-1]) + 2 * sum(map(f, x[1: -1])))
    elif metoda.lower() == "simpson":
        return h / 3 * (f(x[0]) + f(x[-1]) + 4 * sum(map(f, x[1: m: 2])) + 2 * sum(map(f, x[2: m - 1: 2])))
    else:
        raise ValueError("Introduceti o metoda cunoscuta!")

""" Disecritizam intervalul (nr impar de puncte!!)"""
x = np.linspace(a, b, 101)

aprox_dreptunghi = integrare(functie2, x, 'dreptunghi')
aprox_trapez = integrare(functie2, x, 'trapez')
aprox_simpson = integrare(functie2, x, 'simpson')

print("Valorea integralei este: ", quad(functie2, a, b)[0])
print("Valorea integralei aplicand formula de cuadratura sumata a dreptunghiului: ", aprox_dreptunghi)
print("Valorea integralei aplicand formula de cuadratura sumata a trapezeului: ", aprox_trapez)
print("Valorea integralei aplicand formula de cuadratura sumata Simpson: ", aprox_simpson)


"""Exercitiul bonus"""

"""
Observam ca functia din integrala este o densitate a unei variabile aleatoare continue X repartizata Normal
- X ~ N(0, sigma^2) - deci, prin definitie, functia sa de repartitie = 1 pe tot spatiul de probabilitate. Cu alte cuvinte,
integrala respectiva <=> P(-inf < X < inf) = 1, lucru evident din moment ce x∈R. Mai mult, daca aplicam Z = (X - med) / sigma
=> Z = X / sigma variabila standardizata Z ~ N(0, 1), deci P(-inf < X < inf) = P(-inf/sigma < X/sigma < inf/sigma) 
= P(-inf < Z < inf) = phi(inf) - phi(-inf). phi(inf) -> 1, phi(-inf) = 1 - phi(inf), deci P(-inf < X < inf) = 1, deci integrala = 1.
"""

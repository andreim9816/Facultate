import numpy as np
import matplotlib.pyplot as plt

########################################################################################################################
# Exercitiul 1
########################################################################################################################

def grid_discret(A, b, size=50):
    """
    Construieste un grid discret si evaleaza f in fiecare punct al gridului
    """

    # size ->  Numar de puncte pe fiecare axa
    x1 = np.linspace(-6, 6, size)  # Axa x1
    x2 = np.linspace(-6, 6, size)  # Axa x2
    X1, X2 = np.meshgrid(x1, x2)  # Creeaza un grid pe planul determinat de axele x1 si x2

    X3 = np.zeros((size, size))
    for i in range(size):
        for j in range(size):
            x = np.array(
                [X1[i, j], X2[i, j]])  # x e vectorul ce contine coordonatele unui punct din gridul definit mai sus
            X3[i, j] = .5 * x @ A @ x - x @ b  # Evaluam functia in punctul x

    return X1, X2, X3


def linii_nivel(A, b, sol_x, sol_y, levels=10, titlu="Titlu", labelPlot="label", marker=".", labelPuncte="label"):
    """
    Construieste liniile de nivel ale functiei f
    """

    # Construieste gridul asociat functiei
    (X1, X2, X3) = grid_discret(A, b)

    # Ploteaza liniile de nivel ale functiei f
    fig2 = plt.figure()
    plt.contour(X1, X2, X3, levels=levels)  # levels = numarul de linii de nivel

    # Etichete pe axe
    plt.xlabel('x1')
    plt.ylabel('x2')

    # Titlu
    plt.title(titlu)

    # Legenda
    plt.plot(sol_x, sol_y, linewidth=2, label=labelPlot)
    plt.scatter(sol_x, sol_y, marker=marker, s=20, label=labelPuncte)
    plt.legend()
    # Afiseaza figura
    fig2.show()


print("-------------------------------------------------------------------------------------------")
print("Exercitiul 1")
print("-------------------------------------------------------------------------------------------")

"""Pentru ca f(x,y) sa admita punct de minim, matricea A asociata trebuie sa fie pozitiv definita si simetrica.
f(x,y) = 40.5x^2 - 54xy + 30.5y^2 + x + 4y, deci matricea A asociata va fi:
A = (81 -54)
    (-54 61)
iar b = [-1, -4]. Cum A este simetrica, verificam sa fie pozitiv definita prin calculul subminorilor:
|81| > 0 Adev

|81 -54|
|-54 61| = 81 * 61 - (-54) * (-54) = 2025 > 0 Adev
Deci functia respecta conditiile, admite punct de minim unic"""

A = np.array([
    [81, -54],
    [-54, 61]
])

b = np.array([-1, -4])

"""Metoda pasului descendent"""
def met_pas_desc(A, b):
    """Alegem punctul initial"""
    x = np.array([4.0, 4.0])
    """Solutiile obtinute la fiecare iteratie"""
    solX = [x[0]]
    solY = [x[1]]
    """Calculam r (reziduul)"""
    r = b - np.matmul(A, x)

    """Cat timp nu obtinem o solutie suficient de buna"""
    while np.sqrt(np.dot(r, r)) > 10 ** (-10):
        """Calculam r transpus"""
        r_trans = np.transpose(r)
        """Calculam alfa"""
        alfa = np.matmul(r_trans, r) / np.matmul(np.matmul(r_trans, A), r)
        """Updatam x cu noul alfa calculat"""
        x += alfa * r
        solX.append(x[0])
        solY.append(x[1])
        """Updatam 'reziduul'"""
        r = b - np.matmul(A, x)
    """Returneaza sirurile cu toate "solutiile" obtinute"""
    return solX, solY

"""Metoda gradientilor conjugati"""
def met_grad_conj(A, b):
    """Alegem punctul initial"""
    x = np.array([4.0, 4.0])
    """ "Solutiile" obtinute la fiecare iteratie"""
    solX = [x[0]]
    solY = [x[1]]
    """Calculam prima directie, care este egala cu reziduul"""
    d = r_old = r_new = b - np.matmul(A, x)

    """Cat timp nu obtinem o solutie suficient de buna"""
    while np.sqrt(np.dot(d, d)) > 10 ** (-10):
        """Calculam r transpus si d transpus"""
        r_old_trans = np.transpose(r_old)
        d_trans = np.transpose(d)
        """Calculam alfa"""
        alfa = np.matmul(r_old_trans, r_old) / np.matmul(np.matmul(d_trans, A), d)
        """Updatam x cu noul alfa calculat si directia curenta"""
        x += alfa * d
        """Updatam reziduul"""
        r_new = r_old - np.matmul(alfa * A, d)
        """Calculam beta. Calculam r_new transpus"""
        r_new_trans = np.transpose(r_new)
        beta = np.matmul(r_new_trans, r_new) / np.matmul(r_old_trans, r_old)
        """Calculam noua directie"""
        d = r_new + beta * d
        """Actualizam"""
        r_old = r_new
        """Solutia"""
        solX.append(x[0])
        solY.append(x[1])

    """Returneaza sirurile cu toate "solutiile" obtinute"""
    return solX, solY


"""Metoda pasului descendent """
x_sol, y_sol = met_pas_desc(A, b)
print("Solutia este x = ", x_sol[len(x_sol) - 1], " si y = ", y_sol[len(y_sol) - 1], " pentru metoda pasului descendent")

"""Afisam liniile de nivel"""
linii_nivel(A, b, x_sol, y_sol, levels=15, titlu="Metoda pasului descdendent", labelPlot="Drumul", marker=".", labelPuncte="Puncte")

"""Metoda gradientilor conjugati """
x_sol, y_sol = met_grad_conj(A, b)
print("Solutia este x = ", x_sol[len(x_sol) - 1], " si y = ", y_sol[len(y_sol) - 1], " pentru metoda gradientilor conjugati")

"""Liniile de nivel"""
linii_nivel(A, b, x_sol, y_sol, levels=15, titlu="Metoda gradientilor conjugati", labelPlot="Drumul", marker="*", labelPuncte="Puncte")

########################################################################################################################
# Exercitiul 2
########################################################################################################################

print("-------------------------------------------------------------------------------------------")
print("Exercitiul 2")
print("-------------------------------------------------------------------------------------------")

""" Metoda substitutiei ascendente. Are un sistem inferior si calculeaza pe rand fiecare solutie. La pasul k, stie deja
primele k - 1 variabile (x1, x2 ... xk-1), cunoaste bk, deci poate afla si xk. La pasul de baza, avem a00 * x0 = b0, 
a00 si b0 fiind cunoscute """
def subs_asc_fast(a, b):
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    """ Initalizeaza vectorul solutiei numerice. """
    n = b.shape[0]
    x_num = np.zeros(shape=n)

    """ Determina solutia numerica, pas cu pas. """
    x_num[0] = b[0] / a[0, 0]  # Scrie prima componenta a solutiei numerice
    for k in range(1, n):
        s = np.dot(a[k, :k], x_num[:k])
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num

"""Functia data"""
def f2(x):
    return np.sin(3 * x) + 6 * np.cos(4 * x) - 4.15 * x

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


def interp_metoda_newton(X, Y, pointX):
    """Dimensiunea domeniului disecritizat"""
    n = X.shape[0]
    """Construim matricea A asociata"""
    A = np.zeros((n, n))
    """Marcheaza cu 1 pe prima coloana"""
    A[:, 0] = 1
    """Construieste restul matricei"""
    for i in range(1, n):
        p = 1
        for j in range(1, i + 1):
            p = p * (X[i] - X[j - 1])
            A[i][j] = p

    """Rezolva matricea (metoda subst asc). Solutiile (x_sol) reprezinta elementele c1,c2,c3 etc"""
    x_sol = subs_asc_fast(A, Y)

    """Calculeaza aproximarea"""
    aprox_value = x_sol[0]
    p = 1
    for i in range(n - 1):
        p = p * (pointX - X[i])
        aprox_value += x_sol[i + 1] * p

    return aprox_value


# ======================================================================================================================
# Date exacte
# ======================================================================================================================
"""Intervalul dat"""
interval = [-np.pi, np.pi]
"""Construim domeniul si valorile exacte"""
x_domain = np.linspace(interval[0], interval[1], 100)  # Discretizare domeniu (folosit pentru plotare)
y_values = f2(x_domain)  # Valorile functiei exacte in punctele din discretizare

"""gradul maxim al polinomului, eroarea minima gasita"""
N = 0
err = 1e-5
err_min = np.inf

while True:
    N += 1
    x_client = np.linspace(interval[0], interval[1], N + 1)  # Discretizare interval (nodurile date de client)
    y_client = f2(x_client)  # Valorile functiei in nodurile date de client

    """Calculare discretizare polinom"""
    y_interp_met_newton = np.zeros(len(x_domain))
    """Calculeaza aproximarea in punctul respectiv (pentru fiecare punct al disecritizarii)"""
    for i in range(len(x_domain)):
        y_interp_met_newton[i] = interp_metoda_newton(x_client, y_client, x_domain[i])

    """Calculeaza eroare curenta si verifica daca s-a obtinut o eroare suficient de buna"""
    eroare_curenta = eroare_trunchiere(y_interp_met_newton, y_values)

    if eroare_curenta < err_min:
        err_min = eroare_curenta
        sol_min_interpolare = y_interp_met_newton
        N_min = N

    if eroare_curenta <= err:
        break

    """Ne oprim, prea multe puncte te interpolare care in curand vor coincide cu disecritizarea domeniului 
     in cele 100 de puncte"""
    if N == 90:
        break

print("Pentru N = ", N_min, " s-a obtinut eroarea minima", err_min)

"""Afisare grafic"""
plt.figure()
plt.plot(x_domain, y_values, c='k', linewidth=2, label='Functia f2')
plt.xlabel('x')
plt.ylabel('y = f(x)')
plt.grid()
plt.plot(x_domain, sol_min_interpolare, c='r', linewidth=1, linestyle='solid', label='Aproximare cu metoda Newton')
plt.title('Interpolare Langrange cu metoda Newton, N= ' + str(N_min))

"""Afiseaza punctele de interpolare"""
plt.scatter(x_client, y_client, marker='.', c='green', s=100, label='Nodurile de interpolare')
plt.legend()
plt.show()

"""Afiseaza grafic eroare de trunchiere"""
plot_eroare_trunchiere(x_domain, np.abs(y_values - sol_min_interpolare), 'Eroare trunchiere N =' + str(N_min), 'x', 'abs(y_aprox - y_exact)')

########################################################################################################################
# Exercitiul 3
########################################################################################################################

print("-------------------------------------------------------------------------------------------")
print("Exercitiul 3")
print("-------------------------------------------------------------------------------------------")

""" Metoda de factorizare LU. Se pleaca de la U = A initial care va fi prelucrata. L se construieste pas cu pas. """
def factorizare_LU(A):
    assert A.shape[0] == A.shape[1], 'Matricea sistemului nu  este patratica!'

    """P - matricea de permutari in loc de vector ce memoreaza permutarile liniilor. Matricea U este initial matricea A.
    In forma ei finala, este obtinuta din matricea A prin aplicarea MEG pivotare partiala"""
    n = A.shape[0] - 1
    L = np.zeros((n + 1, n + 1))
    P = np.identity(n + 1)

    for k in range(n):
        """Verificare compatib sistem, Aflam pozitia pivotului de pe coloana k"""
        p = np.argmax(np.abs(A[k:, k]))  # gasirea pozitiei pt pivot
        p += k
        if A[p, k] == 0:
            raise AssertionError('A nu admite factorizare LU')

        """Daca pivotul nu este pe aceeasi linie, are loc interschimbarea de linii in P, L, A """
        if p != k:
            P[[p, k], :] = P[[k, p], :]
            L[[p, k], :] = L[[k, p], :]
            A[[p, k], :] = A[[k, p], :]

        """Updatam valorile pt matricile A si L. In A obtinem 0 pe coloana pivotului, sub acesta"""
        for i in range(k + 1, n + 1):
            L[i, k] = A[i, k] / A[k, k]
            A[i] = A[i] - L[i, k] * A[k]

        """Adaugam 1 pe diagonala principala a matricei L"""
        L[k, k] = 1

    L[n, n] = 1
    """Verificare compatibilitate la final"""
    if A[n, n] == 0:
        raise AssertionError('Sistem nedeterminat sau incompatibil!')

    """Returnam L, A(in punctul acesta este U) si matricea ce reprezinta permutarile"""
    return L, A, P

""" Metoda substitutiei descendente. Are un sistem triunghiular superior si calculeaza pe rand fiecare solutie. La pasul
 k, stie deja solutiile xk+1, xk+2 .. xn, cunoaste bk, deci poate afla si xk. La pasul de baza, avem ann * xn = bn, 
ann si bn fiind cunoscute """

def subs_desc_fast(a, b):
    """ (Optionala) Verfica daca matricea 'a' este patratica + compatibitatea cu vectorul 'b' """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    """ Initalizeaza vectorul solutiei numerice. """
    n = b.shape[0] - 1
    x_num = np.zeros(shape=n+1)

    """ Determina solutia numerica. """
    x_num[n] = b[n] / a[n, n]  # Scrie ultima componenta a solutiei numerice
    for k in range(n-1, -1, -1):
        """ Suma produselor dintre coeficienti si solutiile deja calculate """
        s = np.dot(a[k, k+1:], x_num[k+1:])
        """ Calculeaza solutia xk """
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num

"""Functia ceruta"""
def f3(x):
    return -5 * np.sin(-x) + 5 * np.cos(x) + 23.64 * x

def f3_deriv(x):
    return 5 * np.cos(x) - 5 * np.sin(x) + 23.64

def spline_cubica(X, Y, pointX):
    """Construim matricea B cu coeficienti"""
    n = X.shape[0]
    B = np.zeros((n, n))

    for i in range(1, n - 1):
        B[i, i] = 4
        B[i, i - 1] = B[i, i + 1] = 1
    B[0, 0] = B[n - 1, n - 1] = 1

    """Calculeaza h - echidistant pt toate punctele"""
    h = X[1] - X[0]

    """Vectorul b"""
    b = np.zeros(n)
    """Vectorul rezultat"""
    rez = np.zeros(n)
    """Pentru punctele din capete, calculam derivata in acel punct"""
    rez[0] = f3_deriv(X[0])
    rez[n - 1] = f3_deriv(X[n - 1])

    for i in range(1, n - 1):
        rez[i] = (3 / h) * (f3(X[i + 1]) - f3(X[i - 1]))

    "Rezolvam sistemul B*b=rez aplicand metoda LU"
    """ Se verifica daca este solutia unica si conditia aplicarii LU - Gauss cu pivotare partiala(det este diferit de 0) """
    if np.linalg.det(B) != 0:
        L, U, P = factorizare_LU(B)
        """Aplicam permutarile pe vectorul b"""
        _b = np.dot(P, rez)
        """Se aplica cele 2 substitutii: stim ca Ly=_b, L inferior triunghiulara, aflam y prin substitutia asecendenta. 
        Stim ca Ux = y, U superior triunghiulara, aflam solutia x prin substitutia descendenta"""
        y = subs_asc_fast(L, _b)
        b = subs_desc_fast(U, y)

        """Construim vectorii cu coef c si d"""
        c = np.zeros(n)
        d = np.zeros(n)

        for i in range(n - 1):
            d[i] = (-2/(h ** 3)) * (f3(X[i + 1]) - f3(X[i])) + (b[i + 1] + b[i]) / (h ** 2)
            c[i] = (3/(h ** 2)) * (f3(X[i + 1]) - f3(X[i])) - (b[i + 1] + 2 * b[i]) / h

        """Calculeaza aproximarea in punctul respectiv"""
        for i in range(n - 1):
            if X[i] <= pointX <= X[i + 1]:
                a = Y[i]
                return a + b[i] * (pointX - X[i]) + c[i] * (pointX - X[i]) ** 2 + d[i] * (pointX - X[i]) ** 3

    else:
        raise AssertionError(
            'Sistemul nu admite solutie unica! Nu poate fi aplicata factorizarea LU cu pivotare partiala')

# ======================================================================================================================
# Date exacte
# ======================================================================================================================
"""Intervalul dat"""
interval = [-np.pi, np.pi]
"""Construim domeniul si valorile exacte"""
x_domain = np.linspace(interval[0], interval[1], 100)  # Discretizare domeniu (folosit pentru plotare)
y_values = f3(x_domain)  # Valorile functiei exacte in punctele din discretizare


"""Nodurile de interpolare, gradul maxim al polinomului, iteratia"""
N = 1
err = 1e-5
while True:
    N += 1
    x_client = np.linspace(interval[0], interval[1], N + 1)  # Discretizare interval (nodurile date de client)
    y_client = f3(x_client)  # Valorile functiei in nodurile date de client

    """Calculare discretizare polinom"""
    y_interp_spline_cubica = np.zeros(len(x_domain))
    """Calculeaza aproximarea in punctul respectiv (pentru fiecare punct al disecritizarii)"""
    for i in range(len(x_domain)):
        y_interp_spline_cubica[i] = spline_cubica(x_client, y_client, x_domain[i])

    """Calculeaza eroare curenta si verifica daca s-a obtinut o eroare suficient de buna"""
    eroare_curenta = eroare_trunchiere(y_interp_spline_cubica, y_values)
    if eroare_curenta <= err:
        break

"""Afisare grafic"""
plt.figure()
plt.plot(x_domain, y_values, c='k', linewidth=2, label='Functia f3')
plt.xlabel('x')
plt.ylabel('y = f(x)')
plt.grid()

print("Pentru N = ", N, " s-a obtinut eroarea ", eroare_curenta, " care indeplineste conditia")
plt.plot(x_domain, y_interp_spline_cubica, c='r', linewidth=1, linestyle='solid', label='Aproximare cu met spline cubica')
plt.title('Interpolare cu functie spline cubica, N= ' + str(N))

"""Afiseaza punctele de interpolare"""
plt.scatter(x_client, y_client, marker='.', c='green', s=100, label='Nodurile de interpolare')
plt.legend()
plt.show()

"""Afiseaza grafic eroare de trunchiere"""
plot_eroare_trunchiere(x_domain, np.abs(y_values - y_interp_spline_cubica), 'Eroare trunchiere N =' + str(N), 'x', 'abs(y_aprox - y_exact)')

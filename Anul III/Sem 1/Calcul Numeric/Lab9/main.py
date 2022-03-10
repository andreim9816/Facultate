import numpy as np
import matplotlib.pyplot as plt


def subs_desc_fast(a, b):
    """ (Optionala) Verfica daca matricea 'a' este patratica + compatibitatea cu vectorul 'b' """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    """ Initalizeaza vectorul solutiei numerice. """
    n = b.shape[0] - 1
    x_num = np.zeros(shape=n + 1)

    """ Determina solutia numerica. """
    x_num[n] = b[n] / a[n, n]  # Scrie ultima componenta a solutiei numerice
    for k in range(n - 1, -1, -1):
        """ Suma produselor dintre coeficienti si solutiile deja calculate """
        s = np.dot(a[k, k + 1:], x_num[k + 1:])
        """ Calculeaza solutia xk """
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num


# ======================================================================================================================
# Metoda de eliminare Gauss cu pivotare totala
# ======================================================================================================================

def meg_pivotare_totala(a, b):
    """ (Optionala) Verfica daca matricea 'a' este patratica + compatibitatea cu vectorul 'b' """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    """ Matricea extinsa"""
    a_ext = np.concatenate((a, b[:, None]), axis=1)
    n = b.shape[0]

    """ Indecsii variabilelor. Folositi in cazul in care au loc permutari pe coloana (se schimba ordinea variabilelor)"""
    indexes = np.arange(n)

    for k in range(n - 1):
        """ Verificare compatibilitate sistem + aflam poztia pivotului (elementul din modul maxim) din submatricea 
            (aij) i,j= k->n. """
        if not a_ext[k:, k].any():
            raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat.')
        else:
            """ Aflam pivotul pt submatricea de la pasul curent. Nu sunt luate in calcul elementele corespunzatoare 
            vectorului b"""
            (x_piv, y_piv) = np.unravel_index(np.argmax(np.abs(a_ext[k:, k:n]), axis=None), a_ext[k:, k:n].shape)
            """ Calculam indicii pivotului, raportandu-ne la matricea intreaga """
            x_piv += k
            y_piv += k

        """ Schimba linia 'k' cu 'x_piv' daca pivotul ales nu se afla pe aceeasi linie """
        if k != x_piv:
            a_ext[[x_piv, k], :] = a_ext[[k, x_piv], :]

        """ Schimba coloana 'k' cu 'y_piv' daca pivotul ales nu se afla pe aceeasi coloana. Se schimba si ordinea 
        variabilelor """
        if k != y_piv:
            a_ext[:, [y_piv, k]] = a_ext[:, [k, y_piv]]
            indexes[k], indexes[y_piv] = indexes[y_piv], indexes[k]

        """ Punem zero sub pozitia pivotului pe coloana. """
        for j in range(k + 1, n):
            m = a_ext[j, k] / a_ext[k, k]
            a_ext[j, :] -= m * a_ext[k, :]

    """ Verifica compatibilitate """
    if a_ext[n - 1, n - 1] == 0:
        raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat.')

    """ Gaseste solutia numerica folosind metoda substitutiei descendente. """
    x_num = subs_desc_fast(a_ext[:, :-1], a_ext[:, -1])

    """ Aplicam permutarile pe variabile """
    x_num_permutat = np.zeros(shape=n)
    for i in range(n):
        x_num_permutat[indexes[i]] = x_num[i]

    return x_num_permutat


"""
1. Creaza o metoda care returneaza un vector care contine elementul 'x' ridicat la puteri consecutive
pornind de la 0 si pana la n.
"""


def powers_of_x(x, n):
    array = np.zeros(n + 1)
    array[0] = 1
    for i in range(1, n + 1):
        array[i] = array[i - 1] * x

    return array


"""
2. Folosindu-te de metoda de mai sus, scrie elementele matricei folosite in metoda directa de aflare a polinomului 
de interpolare Lagrange.
"""


def create_matrix(x_var, n):
    matrix = np.zeros((n + 1, n + 1))
    for i in range(n + 1):
        matrix[i] = powers_of_x(x_var[i], n)

    return matrix


"""
3. Gaseste coeficientii polinomului rezolvand sistemul rezultat (matricea de la punctul 2 si valorile Y).
"""


def rezolva_sistem(matrix, b):
    x_sol = meg_pivotare_totala(matrix, b)
    return x_sol


# Implementeaza metoda directa de interpolare Lagrange
def interpolare_directa(X, Y, pointx):
    """ Metoda directa de calculare a polinomului de interpolare Lagrange.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param pointx: Punct in care doresti o valoare aproximata a functiei
    :return: aprox_value: Valoarea aproximata calculata folosind polinomul Lagrange in pointx
    """

    n = X.shape[0] - 1
    """Creeaza matricea"""
    a = create_matrix(X, n)

    """Rezolva sistemul"""
    sol = rezolva_sistem(a, Y)

    """
    4. Foloseste metoda de la pasul 1 pentru ca crea un vector ce contine punctul in care doresti aproximarea ridicat la 
    puteri consecutive pornind de la 0 si pana la n.
    """
    point_x_array = powers_of_x(pointx, n)

    """
    5. Folosindu-te de vectorul de la pasul 4 si coeficientii de la pasul 3, afla valoarea aproximata i.e. P(x_aprox),
    unde P este polinomul de interpolare Lagrange rezultat din metoda directa.
    """
    aprox_value = np.dot(point_x_array, sol)
    return aprox_value


def L_k(k, x, x_array):
    prod1 = np.product(x - x_array[:k]) * np.product(x - x_array[k + 1:])
    prod2 = np.product(x_array[k] - x_array[:k]) * np.product(x_array[k] - x_array[k + 1:])
    return prod1 / prod2


def metoda_lagrange(X, Y, pointx):
    """ Metoda Lagrange de calcularea a polinomului de interpolare Lagrange.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param pointx: Punct in care doresti o valoare aproximata a functiei
    :return: aprox_value: Valoarea aproximata calculata folosind polinomul Lagrange in pointx
    """

    n = X.shape[0]
    aprox_value = 0

    for i in range(n):
        aprox_value += Y[i] * L_k(i, pointx, X)

    return aprox_value


# ======================================================================================================================
# Date exacte
# ======================================================================================================================
# Functie cunoscuta
def aplication_function(x):
    """ Functia din exercitiu. """
    # y = """np.sin(2*x) - 2*np.cos(3*x) + """ x ** (x ** (1.2)) * (2 - x ** 2)
    y = x ** 3 - np.sin(2 * x / 7) + np.cos(x ** 2) * (x ** (4 ))
    return y


toy_function = aplication_function  # Al doilea exemplu

# Intervalul dat
interval = [-np.pi, np.pi]  # [a, b]

x_domain = np.linspace(interval[0], interval[1], 100)  # Discretizare domeniu (folosit pentru plotare)
y_values = toy_function(x_domain)  # Valorile functiei exacte in punctele din discretizare

# Afisare grafic figure
plt.figure(0)
plt.plot(x_domain, y_values, c='k', linewidth=2, label='Functie exacta')
plt.xlabel('x')
plt.ylabel('y = f(x)')
plt.grid()

# ======================================================================================================================
# Datele clientului
# ======================================================================================================================

# Nodurile de interpolare
N = 5  # Gradul maxim al polinomului

x_client = np.linspace(interval[0], interval[1], N + 1)  # Discretizare interval (nodurile date de client)
y_client = toy_function(x_client)  # Valorile functiei in nodurile date de client

# Afisare date client pe grafic
plt.scatter(x_client, y_client, marker='*', c='red', s=200, label='Date client')

# Calculare discretizare polinom
y_interp_direct = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
y_interp_lagrange = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
for i in range(len(x_domain)):
    y_interp_direct[i] = interpolare_directa(x_client, y_client, x_domain[i])  # TODO: Trebuie sa scrieti voi metoda
    y_interp_lagrange[i] = metoda_lagrange(x_client, y_client, x_domain[i])  # TODO: Trebuie sa scrieti voi metoda

# Afisare grafic aprixomare
plt.plot(x_domain, y_interp_direct, c='r', linewidth=1, linestyle='--', label='Metoda directa')
plt.plot(x_domain, y_interp_lagrange, c='b', linewidth=1, linestyle='-.', label='Metoda Lagrange')
plt.title('Interpolare Lagrange, N={}'.format(N))
plt.legend()
plt.show()

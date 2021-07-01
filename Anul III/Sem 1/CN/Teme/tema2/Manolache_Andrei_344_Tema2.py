import numpy as np

########################################################################################################################
# Exercitiul 1
########################################################################################################################

print("-------------------------------------------------------------------------------------------")
print("Exercitiul 1")
print("-------------------------------------------------------------------------------------------")

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

# A = np.array([
#     [0.0, 2.0, 3.0, 8.0],
#     [5.0, 4.0, -9.0, 5.0],
#     [8.0, -4.0, 8.0, -3.0],
#     [0.0, 1.0, 5.0, -6.0]
# ])
#
# b = np.array([45.0, 6.0, 12.0, -7.0])

A = np.array([
    [2.0, -2.0, 1.0],
    [1.0, 3.0, -2.0],
    [3.0, -1.0, -1.0]
])

b = np.array([-3.0, 1.0, 2.0])

""" Pentru a verifica daca sistemul admite solutie unica si aplica MEG cu pivotare totala, calculam determinantul
 matricei coeficientilor:
    
    det(A) = |0  2  3  8|
             |5  4 -9  5|
             |8 -4  8 -3|
             |0  1  5 -6|
         
    Aplicam L2 <- L2 - L3 * (5/8). Determinantul devine 
    
    det(A) = |0   2   3     8|
             |0 6.5 -14 6.875|
             |8  -4   8    -3|
             |0   1   5    -6| 
    
    Dezvoltam dupa linia 3 
    
    det(A) = 8 * (-1)^(1+3) * |2     3     8|
                              |6.5 -14 6.875|
                              |1     5    -6|
                              
    det(A) = 8 * [2 * (-14) * (-6) + 6.5 * 5 * 8 + 3 * 6.875 * 1 - 8 * (-14) * 1 - 6.875 * 5 * 2 - 6.5 * 3 * (-6)]
    det(A) = 4871 != 0
    Deci, sistemul are solutie unica, putem aplica MEG cu pivotare totala.
    """
if np.linalg.det(A) != 0:
    sol = meg_pivotare_totala(A, b)
    print('Solutia ecuatiei Ax = b este ', sol)
else:
    raise AssertionError('Determinantul este 0, sistemul nu are solutie unica!')


########################################################################################################################
# Exercitiul 2
########################################################################################################################

print("\n-------------------------------------------------------------------------------------------")
print("Exercitiul 2")
print("-------------------------------------------------------------------------------------------")

"""Functie care determina inversa unei matrice. Creeaza o 'matrice extinsa' prin concatenarea matricei identitate la 
matricea primita. Aplica Gauss cu pivotare totala pe noua matrice, dupa care se foloseste de metoda substitutiei 
descendente pentru a afla elementele inversei. Practic, a obtinut n sisteme superior triunghiulare pe care poate fi
aplicata metoda substitutiei descendente. O singura data face MEG cu pivotare totala, dupa care aplica de n ori metoda
subsitutiei descendente, fiind astfel mai eficient"""

def matrice_inversa(a):
    n = a.shape[0]
    identity_matrix = np.identity(n)

    """Matricea inversa"""
    inverse = np.zeros((n, n))

    """Aplicam Metoda Gauss cu pivotare totala pe matricea 'extinsa' obtinuta prin adaugarea matricei identitate In la 
    matricea data ca parametru. Am folosit MEG cu pivotare totala, chiar daca este mai putin eficienta (datorita cautarii
    pivotului in toata submatricea), dar este mai putin supusa erorii pe cazul general """
    a_ext = np.concatenate((a, identity_matrix), axis=1)

    """ Indecsii variabilelor. Variabila retine permutarile variabilelor"""
    indexes = np.arange(n)

    for k in range(n - 1):
        """ Verificare compatibilitate sistem + aflam poztia pivotului (elementul din modul maxim) din submatricea 
            (aij) i,j= k->n. """
        if not a_ext[k:, k].any():
            raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat.')
        else:
            (x_piv, y_piv) = np.unravel_index(np.argmax(np.abs(a_ext[k:, k:n]), axis=None), a_ext[k:, k:n].shape)
            """ Calculam indicii pivotului, raportandu-ne la matricea intreaga"""
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

    """ Rezolva n sisteme cu metoda descendenta """
    for k in range(n):
        sol_k = subs_desc_fast(a_ext[:, :n], a_ext[:, n + k])
        inverse[:, k] = sol_k

    """ Aplicam permutarile pe variabile """
    x_num_permutat = np.zeros((n, n))
    for i in range(n):
        x_num_permutat[indexes[i]] = inverse[i]

    return x_num_permutat

""""Pentru ca matricea B sa fie inversabila, trebuie verificat faptul ca determinantul este diferit de 0.
   Am calculat determinantul folosind functia predefinita din numpy. Acelasi lucru se putea face aplicand 
   Gauss cu pivotare totala, iar determinantul era produsul coeficientilor de pe diagonala principala dupa 
   ce se obtine un sistem triunghiular superior. Putem aplica MEG cu pivtoare totala (det diferit de 0)"""

B = np.array([
    [2.0, -1.0, 1.0],
    [1.0, 3.0, -2.0],
    [3.0, -1.0, -1.0]
])

""" Calculam deterinantul matricei. Daca nu este zero, matricea admite inversa si o putem calcula """
detB = np.linalg.det(B)
if detB != 0:
    invers_matrice = matrice_inversa(B)
    print('Inversa matricei date este ')
    print(invers_matrice)
else:
    raise AssertionError('Matricea nu admite inversa pentru ca nu e inversabila. Determinantul este 0!')

########################################################################################################################
# Exercitiul 3
########################################################################################################################

print("\n-------------------------------------------------------------------------------------------")
print("Exercitiul 3")
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

A = np.array([
    [ 0.0, -3.0,  4.0,  2.0],
    [-8.0,  1.0,  7.0, -3.0],
    [-4.0,  3.0, -5.0, -9.0],
    [ 9.0, -1.0,  9.0,  3.0]
])

b = np.array([23.0, -6.0, -94.0, 106.0])

""" Se verifica daca este solutia unica si conditia aplicarii LU - Gauss cu pivotare partiala(det este diferit de 0) """
if np.linalg.det(A) != 0:
    L, U, P = factorizare_LU(A)
    """Aplicam permutarile pe vectorul b"""
    _b = np.dot(P, b)
    """Se aplica cele 2 substitutii: stim ca Ly=_b, L inferior triunghiulara, aflam y prin substitutia asecendenta. 
    Stim ca Ux = y, U superior triunghiulara, aflam solutia x prin substitutia descendenta"""
    y = subs_asc_fast(L, _b)
    x = subs_desc_fast(U, y)
    print('Solutia sistemului este ', x)
else:
    raise AssertionError('Sistemul nu admite solutie unica! Nu poate fi aplicata factorizarea LU cu pivotare partiala')

########################################################################################################################
# Exercitiul 4
########################################################################################################################

print("\n\n-------------------------------------------------------------------------------------------")
print("Exercitiul 4")
print("-------------------------------------------------------------------------------------------")

"""Functie care calculeaza factorizarea Cholesky a unei matrice"""
def factorizare_cholesky(a):
    """ (Optionala) Verfica daca matricea 'a' este patratica """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'

    n = a.shape[0]

    """Matricea L pe care trebuie sa o aflam a.i. L * Lt = a"""
    L = np.zeros((n, n))

    """ Initializam primul element al matricei """
    L[0, 0] = np.sqrt(a[0, 0])

    """ Initializam prima coloana """
    for i in range(1, n):
        L[i, 0] = a[i, 0] / L[0, 0]

    for k in range(1, n):
        """ Se determina solutia Lkk """
        L[k, k] = np.sqrt(a[k, k] - np.dot(L[k, :k], L[k, :k]))

        """ Se determina si restul elementelor de pe coloana k """
        for i in range(k + 1, n):
            L[i, k] = (a[i, k] - np.dot(L[i, :k], L[k, :k])) / L[k, k]

    """ Returneaza matricea """
    return L

"""Verificam ca matricea sa fie simetrica si pozitiv definita => admite factorizare Cholesky"""

C = np.array([
    [1.0, -6.0, -6.0, -1.0],
    [-6.0, 100.0, 68.0, -58.0],
    [-6.0, 68.0, 77.0, -1.0],
    [-1.0, -58.0, -1.0, 91.0]
])

"""Aplicam criteriul lui Sylvester ce verifica minorii de colt |Ck| > 0, k = 1,n"""
n = C.shape[0]

for i in range(1, n):
    if np.linalg.det(C[:i, :i]) <= 0:
        raise AssertionError('Matricea nu admite factorizare Cholesky pentru ca nu este pozitiv definita!')

"""Verifica ca matricea sa fie simetrica. Aveam probleme cu """
# for i in range(n):
#     if not np.array_equal(C[i, i + 1:], C[i + 1:, i]):
#         raise AssertionError('Matricea nu admite factorizare Cholesky pentru ca nu este simetrica!!')

if not np.array_equal(C, np.transpose(C)):
    raise AssertionError('Matricea nu admite factorizare Cholesky pentru ca nu este simetrica!!')

"""Daca ajunge in punctul asta, inseamna ca matricea admite descompunere Cholesky"""
matrice_cholesky = factorizare_cholesky(C)
print('Matricea L este \n',matrice_cholesky, ' astfel incat L * Lt = C')
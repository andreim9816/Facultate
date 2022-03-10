import numpy as np


# ======================================================================================================================
# Metoda substitutiei descendente, functionala, dar nu rapida.
# ======================================================================================================================
def subs_desc_slow(a, b):
    """ (Optionala) Verfica daca matricea 'a' este patratica + compatibitatea cu vectorul 'b' """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    """ Initalizeaza vectorul solutiei numerice. """
    n = b.shape[0] - 1
    x_num = np.zeros(shape=n+1)

    """ Determina solutia numerica. """
    x_num[n] = b[n] / a[n, n]  # Scrie ultima componenta a solutiei numerice
    for k in range(n-1, -1, -1):
        s = 0.
        for j in range(k+1, n+1, 1):
            s += a[k, j] * x_num[j]

        x_num[k] = (b[k] - s) / a[k, k]

    return x_num


# ======================================================================================================================
# Metoda substitutiei descendente, functionala, dar rapida.
# ======================================================================================================================
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
        # TODO: Scapa de al doilea for
        # s = 0.
        # for j in range(k+1, n+1, 1):
        #     s += a[k, j] * x_num[j]

        s = np.dot(a[k, k+1:], x_num[k+1:])
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num

# ======================================================================================================================
# Metoda de eliminare Gauss cu pivotare partiala
# ======================================================================================================================
def meg_pivotare_partiala(a, b):
    """ (Optionala) Verfica daca matricea 'a' este patratica + compatibitatea cu vectorul 'b' """
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    a_ext = np.concatenate((a, b[:, None]), axis=1)
    n = b.shape[0] - 1
    for k in range(n):
        """ Verificare compatibilitate sistem + aflam poztia pivotului de pe coloana k. """
        if not a_ext[k:, k].any():
            raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat.')
        else:
            p = np.argmax(np.abs(a[k:, k]))


        """ Schimba linia 'k' cu 'p' daca pivotul nu se afla pe diagonala principala. """
        if k != p:
            a_ext[[p, k], :] = a_ext[[k, p], :]

        """ Zero sub pozitia pivotului pe coloana. """
        for j in range(k+1, n+1):
            m = a_ext[j, k] / a_ext[k, k]
            a_ext[j, :] -= m * a_ext[k, :]

    """ Verifica compatibilitate again. """
    if a_ext[n,n] == 0:
        raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat.')

    """ Gaseste solutia numerica folosind metoda substitutiei descendente. """
    x_num = subs_desc_fast(a_ext[:, :-1], a_ext[:, -1])

    return x_num

def meg_fara_pivot(a, b):
    """Verific daca matricea 'a' este patratica + compatibila cu vectorul 'b'"""

    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu este patratica'

    a_ext = np.concatenate((a, b[:,None]), axis=1)
    n = b.shape[0] - 1
    for k in range(n):
        """Aflam pozitia pivotului de pe coloana k + compatibilitate sistem"""

        if not a_ext[k:, k].any():
            raise AssertionError('Sistem incompatibil sau sistem comp nedeterminat')
        else:
            p = np.argmin(a_ext[k:, k] == 0)
            p += k

        """ SCHIMBA linia 'k' cu 'p' daca pivotul nu se afla pe diagonala principala"""
        if k != p:
            a_ext[[p, k], :] = a_ext[[k, p], :]

        """Zero sub pozitia pivotului pe coloana"""

        for j in range(k + 1, n + 1):
            m = a_ext[j, k] / a_ext[k, k]
            a_ext[j, :] -= m * a_ext[k, :]

    """ Verifica compatibilitatea again."""
    if a_ext[n, n] == 0:
        raise AssertionError('Sistem incompatibil sau sistem comp nedeterminat')

    """Gaseste solutia numerica folosind metoda substitutiei descendente"""

    x_num = subs_desc_slow(a_ext[:, :-1], a_ext[:, -1])

    return x_num

# ======================================================================================================================
# Date
# ======================================================================================================================
A = np.array([
    [5., 1., -6.],
    [2., 1., -1],
    [6., 12., 1.]
])

b = np.array([7., 8., 9.])
sol = meg_pivotare_partiala(A, b)
print(sol)
print("\n------------------\n\n")
# ====================================================================================================
# Calcul inversa
# ====================================================================================================
def calculeaza_inversa(mat):
    """ Initializeaza o matrice pentru stocarea solutiei """
    dim = mat.shape[0]
    id = np.identity(dim)
    inversa = np.zeros((dim, dim))

    for l in range(dim):
        inversa[:, l] = meg_fara_pivot(mat, id[:, l])

    return inversa

sol = calculeaza_inversa(A)
# identity = np.matmul(A, sol)
print(sol)
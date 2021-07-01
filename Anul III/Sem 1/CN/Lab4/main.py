import numpy as np

# =====================================================================
# Metoda substitutiei descendente, functional, dar nu rapida
# =====================================================================

def subs_desc_fast(a, b):
    """(Optionala) Verific daca matricea 'a' este patratica + compatibilitatea cu vectorul 'b'"""
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    """Initializeaza vectorul solutiei numerice."""
    n = b.shape[0] - 1
    x_num = np.zeros(shape=n+1)

    """Determina solutia numerica."""
    x_num[n] = b[n] / a[n, n]  # Scrie ultima componenta a solutiei numerice
    for k in range(n - 1, -1, -1):  # de la n-1 la 0
        # s = 0
        # for j in range(k + 1, n +1):
        #     s += a[k, j] * x_num[j]
        s = np.dot(a[k, k + 1 : ] * x_num[k + 1 :])  # suma. np.dot merge mai rpd

        x_num[k] = (b[k] - s) / a[k, k]

    return x_num


# =====================================================================
# Metoda de eliminare Gauss fara pivotare
# =====================================================================

def meg_fara_pivotare(a, b):
    """(Optionala) Verific daca matricea 'a' este patratica + compatibilitatea cu vectorul 'b'"""
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    a_ext = np.concatenate((a, b[: None]), axis = 1)
    n = b.shape[0] - 1

    for k in range(n):
        """ Verificare compatibilitate sistem + aflam pozitia pivotului de pe coloana k. """
        if not a_ext[k :, k].any():
            raise AssertionError('Sistem incompatibil sau ')
        else:
            # TODO Cum alegi pivotul ca sa obtii MEG cu pivotare partiala?? Se schimba mai jos conditia, alegand pe cel cu val absoluta maxima
            p = np.argmin(a_ext[k:, k] == 0)
            p += k  # Q: Ce dimensiunea are vectorul in care cautam?

        """ Schimba linia k cu p daca pivotul nu se afla pe diagonala principala. """
        if k != p:
            a_ext[[p, k], :] = a_ext[[k, p], :]

        """ Zero sub pozitia pivotului pe coloana. """
        for j in range(k + 1, n + 1):
            m = a_ext[j, k] / a_ext[k, k]
            a_ext[j, :] -= m * a_ext[k, :]

    """ Verifica compatibilitate sistem din nou. """
        if a_ext[n, n] == 0:
            raise AssertionError('Sistem incompatibil sau sistem compatibil nedeterminat!')


    """ Gaseste metoda numerica folosind metoda substitutiei descendente. """
    # x_num = subs_desc_fast(a_ext[:])


# =====================================================================
# Date
# =====================================================================

A = np.array([
    [1., 2., 3.],
    [0., 1., 2.],
    [0., 0., 2.]
])

x_sol = np.array([1., 1., 1.])
b_ = np.matmul(A, x_sol)

# x_numeric = subs_descendenta(A, b_)

A_gauss = np.array([
    [2., 3., 0.],
    [3., 4., 2.],
    [1., 4., 3.]
])


eps = 10 ** (-20)
a_limitare = np.array([
    [eps, 1.],
    [1., 1.]
])
b_limitare = np.array([1., 2.])
# x_sol_limitare = [1., 2.]

x_sol_limitare = meg_fara_pivotare(a_limitare, b_limitare)


import numpy as np


def subs_asc_fast(a, b):
    assert a.shape[0] == a.shape[1], 'Matricea sistemului nu este patratica!'
    assert a.shape[0] == b.shape[0], 'Matricea sistemului si vectorul b nu se potrivesc!'

    """ Initalizeaza vectorul solutiei numerice. """
    n = b.shape[0] - 1
    x_num = np.zeros(shape=n + 1)

    """ Determina solutia numerica. """
    x_num[0] = b[0] / a[0, 0]  # Scrie ultima componenta a solutiei numerice
    for k in range(1, n):
        s = np.dot(a[k, :k], x_num[:k])
        x_num[k] = (b[k] - s) / a[k, k]

    return x_num

#TODO
def LU_pivotare(A):
    """ (Optionala) Verifica daca matricea 'A' este patratica + compatibila cu vect 'b' """
    assert A.shape[0] == A.shape[1], 'Matricea sistemului nu  este patratica!'
    assert A.shape[0] == b.shape[0], 'Vectorul nu este compatibil'

    n = b.shape[0] - 1
    L = np.zeros([n + 1, n + 1])  # matricea L
    P = np.identity(n + 1)  # matricea permutarilor

    for k in range(n):
        """Verificare compatib sistem, Aflam pozitia pivotului de pe coloana k"""
        # TODO de adaugat verificare sistem incomp
        p = np.argmax(np.abs(A[k:, k]))  # gasirea pozitiei pt pivot
        p += k

        # k <-> p daca piv nu e pe diag
        if k != p:
            #TODO interschimbat liniile

        # Pasul 3 din alg
        for i in range(k + 1, n + 1, 1):
            m = A[i, k] / A[k, k]
            L[i, k] = m  # acel m
            A[i, :] = A[i, :] - m * A[k, :]

    L += np.identity(n + 1)  # pasul 4

    return P, A, L


A = np.array([
    [2, 0, 0],
    [1, -1, 0],
    [1, 1, 1]
])

b = np.array([2, 2, 3])
sol = subs_asc_fast(A, b)
print(sol)

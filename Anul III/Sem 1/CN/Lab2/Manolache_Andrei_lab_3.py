import numpy as np
import matplotlib.pyplot as plt

# functia
def f(x):
    return np.cos(x) - x

# derivata functiei
def df(x):
    return -1 * np.sin(x) - 1

# valorile
a = 0
b = np.pi /2
x = np.linspace(a, b, 100)
y = f(x)
x_0 = np.pi/4
eps = 10e-5

# plotam
plt.figure(0)
plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('y')
plt.show()

plt.title('Metoda N-R')
plt.legend('f(x)')
plt.axvline(0, c='black')
plt.axhline(0, c='black')
plt.grid()
plt.axis('scaled')
plt.show()

# metoda newton R
def metoda_NR(f, fd, a, b, eps, x_0, max_iter = 1000):

    # erori
    assert a < b, 'Eroare domeniu!'
    assert np.sign(f(a)) * np.sign(f(b)) < 0, 'Mesaj eroare!'
    assert eps > 0, 'Eroare'
    assert a < x_0 < b, 'Eroare'
    # Verifica ca se indeplinesc si celelalte
    # conditii din teorema respectiva
    # TODO

    x_old = x_0
    N = 0

    #Iteratiile algoritmului
    # while True:
    #     x_new = x_old - f(x_old) / df(x_old)
    #     N += 1
    #
    #     if np.abs(f(x_new)) < eps:
    #         break
    #
    #     x_old = x_new

    # v2
    for N in range(max_iter):
        x_new = x_old - f(x_old) / df(x_old)

        if np.abs(f(x_new)) < eps:
            break
        x_old = x_new

    if N == max_iter - 1:
        x_old = None
        N = -1

    return x_new, N

x_new, N = metoda_NR(f, df, a, b, eps, x_0)
print(x_new)

# Afisari
plt.figure(0)
plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('y')
plt.show()

plt.title('Metoda N-R')
plt.legend('f(x)')
plt.axvline(0, c='black')
plt.axhline(0, c='black')
plt.grid()

plt.scatter(x_new, 0, marker='o')
plt.legend('f x', 'xSum')
plt.axis('scaled')
plt.show()
import numpy as np
import matplotlib.pyplot as plt


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

def spline_liniara(X, Y, pointx):
    """ Metoda de interpolare spline liniara.
    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param pointx: Punct in care doresti o valoare aproximata a functiei
    :return: aprox_value: Valoarea aproximata calculata interpolarea spline liniara in pointx
    """
    n = len(X)

    for j in range(0, n - 1):
        if X[j] <= pointx <= X[j + 1]:
            a = Y[j]
            b = (Y[j + 1] - Y[j]) / (X[j + 1] - X[j])
            return a + b * (pointx - X[j])

# ======================================================================================================================
# Datele clientului
# ======================================================================================================================
# Nodurile de interpolare
x_client_all = [55., 69, 75, 81, 88, 91, 95, 96, 102, 108, 116, 126, 145, 156, 168, 179, 193, 205,
                222, 230, 235, 240, 242, 244, 253, 259]
y_client_all = [162., 176, 188, 209, 229, 238, 244, 256, 262, 259, 254, 260, 262, 265, 263, 260, 259,
                252, 244, 239, 233, 227, 226, 224, 224, 221]


# Date de simulare
select_from = 4  # TODO: Selecteaza alte valori ('1' ca sa afiseze toate datele)
                 # Extrage date client din 'select_from' in 'select_from' (simulari)
x_client = []
y_client = []
for i in range(len(x_client_all)):
    if i % select_from == 0:
        x_client.append(x_client_all[i])
        y_client.append(y_client_all[i])

x_client = np.array(x_client)
y_client = np.array(y_client)

N = len(x_client) - 1  # Gradul polinomului Lagrange / numar de subintervale

x_domain = np.linspace(x_client[0], x_client[-1], 100)  # Discretizare domeniu (folosit pentru plotare)


# Afisare grafic figura
plt.figure(0)
plt.xlabel('x')
plt.ylabel('y = f(x)')

# Afisare date client pe grafic
plt.scatter(x_client, y_client, marker='*', c='red', s=5, label='Date client')

# Calculare discretizare polinom
y_interp_lagrange = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
y_interp_spline_liniara = np.zeros(len(x_domain))  # Folosit pentru a stoca valorile aproximate
for i in range(len(x_domain)):
    y_interp_lagrange[i] = metoda_lagrange(x_client, y_client, x_domain[i])  # TODO: Trebuie sa scrieti voi metoda
    y_interp_spline_liniara[i] = spline_liniara(x_client, y_client, x_domain[i])  # TODO: Trebuie sa scrieti voi metoda


# Afisare doggo
image = np.load('./frida_doggo.npy')
plt.imshow(image, extent=[0, 300, 0, 300])

# Afisare grafic aproximare
plt.plot(x_domain, y_interp_lagrange, c='w', linewidth=2, linestyle='-.', label='Metoda Lagrange')
plt.plot(x_domain, y_interp_spline_liniara, c='g', linewidth=2, linestyle='-', label='Spline Liniara')
plt.title('Interpolare, N={}'.format(N))
plt.legend()
plt.xlim([-1, 305])  # Limiteaza domeniul de afisare
plt.ylim([-1, 305])  # Limiteaza co-domeniul de afisare
plt.show()
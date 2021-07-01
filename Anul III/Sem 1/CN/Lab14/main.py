import numpy as np
import matplotlib.pyplot as plt

"""
    1. Definim o functie exacta dupa care vom genera 
    2. Definim o metoda prin care vom genera data perturbate 
    3. Definim o metda prin care vizualizam datele
    4. Implementam o metoda de regresie liniara
    5. Definim o metda prin care sa vedem curba rezultata
"""

# 3
def view_data(f1_, f2_, show=True):
    plt.figure()
    plt.scatter(f1_, f2_, marker='o', c='green', label='known data')
    plt.legend()
    plt.xlabel('feature 1')
    plt.ylabel('feature 2')
    plt.grid()
    plt.title('Date de regrsie')

    if show:
        plt.show()

# 5
def view_regression(coef, method='linear', show=True):
    if method.lower() == 'linear':
        domain = np.linspace(1, 3, 100)
        # a * domain + b
        values = poli2(domain, coef[0], coef[1])
        plt.plot(domain, values, label='linear')

    elif method.lower() == 'patratic':
        domain = np.linspace(1, 3, 100)
        # a * domain * domain + b * domain + c
        values = poli2(domain, coef[0], coef[1], coef[2])  # coef[0] * domain * domain + coef[1] * domain + coef[2]
        plt.plot(domain, values, label='patratic')
    elif method.lower() == 'exponent':
        domain = np.linspace(1, 3, 100)
        values = exponent(domain, coef[0], coef[1])  # coef[0] * domain * domain + coef[1] * domain + coef[2]
        plt.plot(domain, values, label='exponentiala')
    else:
        assert 'NUUUUUUUUUU'
    plt.legend()

    if show:
        plt.show()


def poli1(x_, a=1, b=1):
    y = a * x_ + b
    return y

def poli2(x_, a=1, b=1, c=1):
    return a * x_ * x_ + b * x_ + c

def exponent(x_, a=1, b=1):
    return b * np.exp(a * x_)


def generate_toy_data(method='linear', num_samples=30, low=1, high=3):
    """Genreaza x-ii aleator, nu cu linespace, de la low la high"""
    feature_1 = np.random.uniform(low=low, high=high, size=num_samples)
    feature_1 = np.sort(feature_1)

    if method.lower() == 'linear':
        feature_2 = poli1(feature_1)
    elif method.lower() == 'patratic':
        feature_2 = poli2(feature_1, 2, -6, 4)
    elif method.lower() == 'exponent':
        feature_2 = exponent(feature_1, a=1, b=3)
    else:
        assert 'NUUU'

    # perturbari
    if method.lower() == 'linear':
        feature_2 += np.random.normal(size=len(feature_2), loc=0, scale=0.3)  # scale = deviatia standard, loc = media
    elif method.lower() == 'patratic':
        feature_2 += np.random.normal(size=len(feature_2), loc=0, scale=0.6)  # scale = deviatia standard, loc = media
    elif method.lower() == 'exponent':
        feature_2 += np.random.normal(size=len(feature_2), loc=0, scale=3.3)  # scale = deviatia standard, loc = media

    return feature_1, feature_2

# 4
def regresie_liniara(f1_, f2_):
    a11 = f1_ @ f1_

    a12 = np.sum(f1_)
    a22 = len(f1_)

    matrix = np.array([
        [a11, a12],
        [a12, a22]
    ])

    w = np.array([
        [f1_ @ f2_],
        [np.sum(f2_)]
    ])

    """coef adica vectorul [a,b] pe care vrem sa l aflam"""
    """Solve matrix * coef = w"""
    coef = np.linalg.solve(matrix, w)

    return coef

def regresie_patratica(f1_, f2_):
    a11 = np.sum(f1_ * f1_ * f1_ * f1_)
    a12 = np.sum(f1_ * f1_ * f1_)
    a13 = f1_ @ f1_
    a33 = len(f1_)
    a23 = np.sum(f1_)

    matrix = np.array([
        [a11, a12, a13],
        [a12, a13, a23],
        [a13, a23, a33]
    ])

    w = np.array([
        [np.sum(f2_ * f1_ * f1_)],
        [f1_ @ f2_],
        [np.sum(f2_)]
    ])

    """coef adica vectorul [a,b, c] pe care vrem sa l aflam"""
    """Solve matrix * coef = w"""
    coef = np.linalg.solve(matrix, w)

    return coef

def regresie_exponentiala(f1_, f2_):
    a11 = f1_ @ f1_
    a12 = np.sum(f1_)
    a22 = len(f1_)

    matrix = np.array([
        [a11, a12],
        [a12, a22]
    ])

    log_array = np.log(f2_)
    w1 = np.dot(log_array, f1_)
    w2 = np.sum(log_array)

    w = np.array([
        [w1],
        [w2]
    ])

    coef = np.linalg.solve(matrix, w)

    coef[1] = np.exp(coef[1])
    return coef


# f1, f2 = generate_toy_data(method='patratic')
# view_data(f1, f2, show=False)
#
# coef = regresie_patratica(f1, f2)
# view_regression(coef, method='patratic', show=True)


# f1, f2 = generate_toy_data(method='linear')
# view_data(f1, f2, show=False)
#
# coef = regresie_liniara(f1, f2)
# view_regression(coef, method='linear', show=True)

f1, f2 = generate_toy_data(method='exponent')
view_data(f1, f2, show=False)

coef = regresie_exponentiala(f1, f2)
view_regression(coef, method='exponent', show=True)


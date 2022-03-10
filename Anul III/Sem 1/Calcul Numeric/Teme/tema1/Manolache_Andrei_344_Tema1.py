# Manolache Andrei
# grupa 344

import numpy as np
import matplotlib.pyplot as plt

# ex 1
print("\n**********************************************************************************\n\nExercitiul 1:")
""" Aflarea radacinii unui numar y poate fi scrisa ca ecuatia y = x^2,x numar real pozitiv radacina patrata a numarului.
    Deci, trebuie aflat x a.i. 5 = x^2. Se aplica metoda bisectiei pt functia f(x) : [0, inf) -> R. f(x) = 5 -x^2
    Stim ca functia f este continua (compunere de functii elementare). Cu siguranta aceasta are solutie in intervalul
    [0, 5] (orice numar real pozitiv admite o unica radacina patrata(pozitiva). Cum numarul este mai mare ca 1, atunci
    radacina patrata este sigur mai mica ca numarul respectiv). Considerand intervalul [0, 5] pe care 
    se aplica metoda bisectiei, este verificata conditia ca f(a) * f(b) < 0 ( f(0) = 5 > 0 si f(5) = -20 < 0 ). Deci,
    se va obtine radacina patrata aplicand acest procedeu.
    """
def aproximareRadical(nr, epsilon, st, dr ):
    """
     Injumatatim intervalul curent [st, dr] in 2 subintervale egale in care se poate afla solutia (luat initial [0, 5]
     => [st, m] si [m, dr]), cu m = (st+dr) /2. Se verifica daca jumtatea intervalului mare ("solutia de mijloc"),
     ridicat la patrat (m * m) este egal cu numarul initial(5). Daca da, ne-am oprit, am gasit solutia.
     Altfel, verificam daca ridicarea la patrat depaseste numarul initial (5), atunci trebuie sa gasim o solutie mai
     mica, deci solutia se afla in partea stanga a intervalului, deci pe [st, m). Altfel, daca m * m < numarul initial,
     atunci solutia cautata este mai mare, deci o cautam in intervalul (m, dr].Actualizam capetele si repetam algoritmul
     cat timp nu obtinem o solutie suficient de buna.
    """

    # Calculam prima solutie posibila (jumatatea intervalului)
    assert nr >= 0, 'Numarul trebuie sa fie pozitiv!'
    assert st < dr, 'Intervalul nu este valid!'
    m = (st + dr) / 2

    while abs(m * m - nr) > epsilon:  # Cat timp nu am obtinut o solutie suficient de buna
        if m * m == nr:  # Am gasit solutia exacta
            break
        elif m * m > nr:  # Daca numarul ridicat la patrat este prea mare, capatul din dreapta este micsorat caci solutia este este sigur mai mica ca m
            dr = m
        else:  # Daca numarul ridicat la patrat este prea mic, capatul din stanga este marit caci solutia este sigur mai mare ca m
            st = m
        m = (st + dr)/2  # Actualizam actuala posibila solutie

    return m  # Returnam solutia

rez = aproximareRadical(nr=5, epsilon=10 ** (-8), st=0, dr=5)
print(f"Sqrt({5}) = {round(rez, 7)} cu eroare de {7} zecimale")

# ex 2
print("\n\n********************************************************************************** \n\nExercitiul 2:")
"""
Consideram functia f(x) = e^(x-2) - cos(e^(x-2)) - 1 = 0. f'(x) = e^(x-2) + sin(e^(x-2))  * e^(x-2). f'(x) = 0 => 
e^(x-2)[1 + sin(e^(x-2))] = 0. Cum e^(x-2) este pozitiva => 1 + sin(e^(x-2)) = 0 => sin(e^(x-2)) = -1. Deci, e^(x-2) =
2k*pi - pi/2 ,k ={1, 2, 3 ...} => x = 2 + ln(2k *pi - pi/2). Deci, f'(x) = 0 pt x = {2 + ln(2k*pi - pi/2) |k ={1, 2, 3 ..}
=> x ={2 + ln(3pi/2), 2 + ln(7pi/2), 2 + ln(11pi/2)  ...} a.i. f'(x) = 0. Pt acesti x, f'(x) = 0, in rest f'(x) > 0, deci
f(x) este str crescatoare pe (-inf, 2+ln(3pi/2)) U (2 +ln(3pi/2), 2 + ln(7pi/2)) U (2 + ln(7pi/2), 2 + ln(11pi/2)) U ...
f(2+ln(3pi/2)) ~ 3.7123 > 0. Cum pe intervalul (2+ln(3pi/2), inf), functia f este crescatoare si f(2+ln(3pi/2)) > 0,
inseamna ca pe intervalul [a,b] unde vom cauta solutia, putem considera b = 2+ln(3pi/2) si solutia este unica. Calculam 
f(1) ~ -1.5652 < 0. Deci, cum f(a) * f(b) < 0 si f functia continua (compunere de functii elementare), putem aplica 
metoda bisectiei pe intervalul [1, 2+ln(3pi/2)] pentru a gasi solutia ecuatiei. Unicitatea solutiei pe R este data de 
faptul ca f(x) > 0 pt x > 2+ln(3pi/2), f str cresc pe (-inf, 2+ln(3pi/2)) si f crescatoare pe R.
"""

def bisectie(f, a, b, eps):

    assert a < b, 'Intervalul trebuie sa fie valid!'
    N = int(np.floor(np.log2((b - a) / eps)))  # numarul de iteratii ale algoritmului pana cand gasim solutia

    for i in range(N):
        m = (a + b) / 2  # Aproximarea solutiei la pasul curent. In prezent, intervalul este 'divizat' in 2 subintervale: [a,m] si [m,b]
        if f(m) == 0:  # Daca am gasit solutia ecuatiei
            break
        elif f(a) * f(m) > 0:  # Daca capatul curent din stanga si aproximarea curenta a solutiei sunt de acelasi semn, atunci solutia se afla in partea dreapta a intervalului, deci in [m,b]
            a = m
        else:  # Daca capatul curent din stanga si aproximarea curenta a solutiei sunt de semne diferite, atunci solutia se afla in partea stanga a intervalului, deci in [a, m]
            b = m

    return m  # Solutia

def func1(x):
    # Definim prima functie
    return np.e ** (x - 2)

def func2(x):
    # Definim cea de-a 2a functie
    return np.cos(np.e**(x-2)) + 1

def funcEx2(x):
    return func1(x) - func2(x)

x = np.linspace(0, 4, 100)  # Discretizarea intervalului [0, 4]. Am ales acest interval restrans pentru a se putea interpreta si verifica solutia pe grafic.

plt.plot(x, func1(x), linestyle='solid', linewidth=1, c='green')  # Plotam prima functie
plt.plot(x, func2(x), linestyle='solid', linewidth=1, c='red')  # Plotam a doua functie functie

sol = bisectie(funcEx2, 0, 4, 10 ** (-5))
plt.scatter(sol, func1(sol), s=50, c='blue', marker='8')
print(f"Solutia ecuatiei este x = {sol}")

plt.legend(['e^(x-2)', 'cos(e^(x-2))'])  # Legenda graficului

plt.axvline(0, c='black')  # Adauga axa OY
plt.axhline(0, c='black')  # Adauga axa OX

plt.xlabel('x')  # adauga titlul axei OX
plt.ylabel('f(x)')  # adauga titlul axei OY

plt.grid(b=True)
plt.show()

# ex 3
print("\n\n********************************************************************************** \n\nExercitiul 3:")
def pozitie_falsa(f, a, b, eps):
    """
    Algoritmul pozitiei false. Se construiesc sirurile corespunzatoare capetelor intervalului in care se gaseste solutia
    respectiv sirul solutiei aproximative a.i. f(x) = 0. Initial, intervalul in care se cauta solutia este chiar [a,b],
    iar prima posibila solutie este intersectia dreptei AB (data prin punctele (a, f(a)) (b,f(b))) cu axa OX. Verificam
    daca punctul de intersectie se afla pe OX, iar in caz afirmativ, algoritmul se opreste, am gasit solutia. Altfel,
    se verifica daca f(ultima solutie gasita - f(X k-1)) este de acelasi semn cu f(capatul din stanga), atunci solutia trebuie
    cautata in partea dreapta, deci in [X k-1, b k-1], iar daca sunt de semne diferite, cautam solutia in capatul din
    stanga, deci in [a k-1, X k-1]. De fiecare data se updateaza sirurile pentru capetele intervalului curent.Algoritmul
    se repeta pana cand eroarea relativa este suficient de buna.
    """
    assert a < b, 'Intervalul nu este valid!'
    assert f(a) * f(b) < 0, 'Nu este indeplinita conditia f(a) * f(b) < 0'  # Se presupune ca derivata si a 2a derivata nu se anuleaza pe [a,b] in momentul in care se apeleaza functia
    # Initial intervalul in care se cauta solutia este [a,b]. Primul element din sirul in care se va gasi solutia este
    # intersectia dintre AB cu OX (AB data prin punctele (a, f(a)) (b,f(b))))
    N = 0
    st = [a]
    dr = [b]
    x = []
    x.append((a * f(b) - b * f(a)) / (f(b) - f(a)))

    while True:
        N += 1  # Incrementam pasul

        if f(x[N - 1]) == 0:  # Verificam daca ultimul x obtinut este solutie, atunci oprim algoritmul
            x.append(x[N - 1])
            break
        elif f(st[N - 1] * f(x[N - 1])) < 0:  # Daca f(ultima solutie gasita - f(X N-1)) este de semn diferit cu f(capatul din stanga), cautam in partea stanga [st N - 1, X N - 1], updatam sirurile pt pasul curent (inclusiv cele pt capete)
            st.append(st[N - 1])
            dr.append(x[N - 1])
            x.append((st[N] * f(dr[N]) - dr[N] * f(st[N])) / (f(dr[N]) - f(st[N])))
        elif f(st[N - 1] * f(x[N - 1])) > 0:  # Daca f(ultima solutie gasita - f(X N-1)) este de acelasi semn cu f(capatul din stanga), cautam in partea dreapta [X N - 1, dr N - 1], updatam sirurile pt pasul curent (inclusiv cele pt capete)
            st.append(x[N - 1])
            dr.append(dr[N - 1])
            x.append((st[N] * f(dr[N]) - dr[N] * f(st[N])) / (f(dr[N]) - f(st[N])))

        """Verific daca am gasit o solutie suficient de buna.In mod normal, apare o problema la calculul erorii relative
           daca penultima aproximare a solutiei (X N-1) este 0 si verificarea ar trebui inlocuita cu eroarea absoluta
           ( abs(x[N] - x[N-1]) < eps ). In cazul nostru, pe functia aleasa, nu apar probleme. 
        """
        if abs(x[N] - x[N - 1]) / abs(x[N - 1]) < eps:  # Daca am obtinut o solutie suficient de buna, atunci ne oprim
            break

    return x[N], N  # returneaza solutia si numarul de pasi


def f1(x):
    # Definim functia x^3 + x^2 - 16x - 16
    return x ** 3 + x ** 2 - 16 * x - 16

x = np.linspace(-5, 5, 100)  # Discretizarea intervalului [a, b]
y = f1(x)  # Valorile functiei

plt.plot(x, y, linestyle='solid', linewidth=1, c='green')  # Plotam functia
"""
Plotam solutiile de pe fiecare interval ales. Alegerea intervalelor:
Am ales intervalele astfel incat sa fie respectate conditiie:
f1(a) * f1(b) < 0
f1'(x) != 0
f1"(x) ! = 0
f1 derivabila pe [a,b] ( cum f functie elementara continua (compunere de functii elementare) => f1 derivabila pe [-5,5])
f1(x) = x^3 + x^2 - 16x - 16 => f1'(x) = 3x^2 + 2x - 16. f'(x) = 0 <=> 3x^2 + 2x - 16 = 0. Fct de gr II =>
delta = 4 + 4 * 3 * 16 = 196 => x0 = (-2-14)/6 = -8/3 x1 = (-2 + 14)/6 = 2. Deci, f1'(x) = 0 in
punctele x0 si x1. Calulam f1"(x) = 6x + 2. f1"(x) = 0 <=> x = -1/3. Deci f1"(x) se anuleaza doar in -1/3.
Deci subintervalele trebuie sa nu contina punctele x0 = -8/3, x1 = 2 (pt a respecta conditia f1'(x) != 0) si x = -1/3
(pentru conditia f1"(x) != 0). Pe intervalul (x0, x1) f1 este str desc iar in [-5, x0) si (x1, 5] str cresc (f1'(x) >0)
Calculam f2(-5) = -36 < 0. Luam un punct x < x0. Fie acesta -3. f2(-3) = 14 > 0, deci f2(-5) * f2(-3) < 0. Cum subintervalul
nu contine punctele {-8/3, -1/3 , 2} acesta indeplineste conditiile, deci putem aplica metoda pozitiei false pe el.
Pt al 2-lea interval: Alegem un subinterval din (x0, x1) pt ca f1'(x) si f1"(x)!= 0. Alegem a = -3 si b = -0.5. f1(a)=14
f1(b) = -7.875, deci f1(a) * f1(b) < 0. Cum -1/3 ∉ [a,b], deci f1"(x) != 0 si putem aplica metoda secantei.
Pt al 3-lea interval: Alegem un subinterval din (x1, 5] deoarece f1'(x) != 0 pe intervalul respectiv. Alegem a = 1.5 (a > x1)
si b = 5. Calculam f1(a) = -34.375 < 0, f1(b) = 52 > 0, deci f1(a) *f1(b) < 0. Stim ca f1'(x) != 0 pe [a,b] si f1"(x)!=0
(-1/3 ∉ [a,b]) deci putem aplica metoda secantei
"""
for (st, dr) in [(-5, -3), (-3, -0.5), (1.5, 5)]:
    x_sol, _ = pozitie_falsa(f1, st, dr, 10 ** (-5))
    plt.scatter(x_sol, 0, s=50, c='red', marker='8')
    print(f"Solutia pe intervalul {[st, dr]} este x = {x_sol}")

plt.legend(['f(x)', 'sol'])  # Legenda graficului

plt.axvline(0, c='black')  # Adauga axa OY
plt.axhline(0, c='black')  # Adauga axa OX

plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Graficul functiei f = x^3 + x^2 - 16x - 16')  # Titlul graficului

plt.grid(b=True)
plt.show()

#ex 4
print("\n\n********************************************************************************** \n\nExercitiul 4:")

def secanta(f, a, b, x0, x1, eps):
    """
    Metoda secantei. Se construieste sirul Xk corespunzator aproximarii solutiei f(x) = 0. Se aleg punctele de start x0 si x1
    cu care incepe algoritmul. Construim dreapta determinata de punctele (x0, f(x0)) si (x1, f(x1)). Determinam punctul
    de intersectie cu OX, adica termenul X2, dupa care facem intersectia dintre dreapta determinata de (X1, f(X1)) si
    (X2, f(X2)). Gasim punctul X3 samd. La pasul k, se construieste dreapta determinata de punctele (Xk-2, f(Xk-2)) si
    (Xk-1, f(Xk-1)) si intersectia cu OX da aproximarea solutiei Xk. Se verifica daca este o solutie suficient de buna,
    iar la fiecare pas,se verifica, in plus, ca noua solutie sa nu fi depasit domeniul de definitie al functiei.
    """
    assert a < b, 'Intervalul nu e valid!'
    assert a <= x0 <= b, 'X0 nu e valid!'
    assert a <= x1 <= b, 'X1 nu e valid!'
    assert f(a) * f(b) < 0, 'Nu este indeplinita conidita f(a) * f(b) < 0'  # Se presupune ca derivata nu se anuleaza in [a,b] cand este apelata metoda pt functia respetiva
    N = 1  # Pasul
    x = [x0, x1]  # sirul 'solutiilor'

    while True:
        """Verific daca am gasit o solutie suficient de buna.In mod normal, apare o problema la calculul erorii relative
         daca penultima aproximare a solutiei (X N-1) este 0 si verificarea ar trebui inlocuita cu eroarea absoluta
         ( abs(x[N] - x[N-1]) < eps ). In cazul nostru, pe functia aleasa, nu apar probleme. 
        """
        if abs(x[N] - x[N - 1]) / abs(x[N - 1]) < eps:
            break
        N += 1  # Incrementarea pasului
        x.append((x[N - 1] * f(x[N - 2]) - x[N - 2] * f(x[N - 1])) / (f(x[N - 2]) - f(x[N - 1])))  # noua solutie
        assert a <= x[N] <= b, 'Valorile x0 si x1 au fost alese gresit!'

    return x[N], N

def f2(x):
    # Definim functia x^3 + 2x^2 - x- 2
    return x ** 3 + 2 * (x ** 2) - x - 2

x = np.linspace(-3, 3, 100)  # Discretizarea intervalului [-3 ,3]
y = f2(x)  # Valorile functiei

plt.plot(x, y, linestyle='solid', linewidth=1, c='green')  # Plotam functia
"""
Plotam solutiile de pe fiecare interval ales. Alegerea intervalelor:
Am ales intervalele astfel incat sa fie respectate conditiie:
f2(a) * f2(b) < 0
f2'(x) != 0
f2 derivabila pe [a,b] ( cum f2 functie elementara continua => f2 derivabila pe [-3,3])
f2(x) = x^3 + 2x^2 - x - 2 => f2'(x) = 3x^2 + 4x - 1. f2'(x) = 0 <=> 3x^2 + 4x - 1 = 0. Fct de gr II =>
delta = 16 + 12 = 28 => x0 = (-4 - sqrt(28))/6 ~ -1.54 x1 = (-4 + sqrt(28))/6 ~ 0.21. Deci, f2'(x) = 0 in
punctele x0 si x1. Pe intervalul (x0, x1) f2 este str desc iar in [-3, x0) si (x1, 3] str cresc ( f2'(x) > 0)
Calculam f2(-3) = -8 < 0. Luam un punct x < x0. Fie acesta -1.8. f2(-1.8) = 0.4479 > 0, deci f2(3) * f2(-1.8) < 0.
Deci subintervalul [-3, -1.8] indeplineste conditiile, putem aplica metoda secantei pe acesta.
Pt al 2-lea interval: Alegem un subinterval din (x0, x1) pt ca f2'(x) != 0. Alegem a = -1.5 si b = 0.1. f2(a) = 0.625
f2(b) = -2.079, deci f2(a) * f2(b) < 0. Putem aplica metoda secantei
Pt al 3-lea interval: Alegem un subinterval din (x1, 3] deoarece f2'(x) != 0. Alegem a = 0.5 (a > x1) si b = 3.
Calculam f2(a) = -1.875 < 0, f2(b) = 40 > 0, deci f2(a) * f2(b) < 0. Stim ca f2'(x) != 0 pe [a,b], deci putem aplica
metoda secantei.Am ales x0 =a si x1 = b capetele intervalului, interval pe care f e definita si nu-si schimba monotonia
cu f2(a) * f2(b) <0
"""

for (st, dr) in [(-3, -1.8), (-1.5, 0.1), (0.5, 3)]:
    x_sol, _ = secanta(f2, a=st, b=dr, x0=st, x1=dr, eps=10 ** (-5))
    plt.scatter(x_sol, 0, s=50, c='red', marker='8')
    print(f"Solutia pe intervalul {[st, dr]} este x = {x_sol}")

plt.legend(['f(x)', 'sol'])  # Legenda graficului

plt.axvline(0, c='black')  # Adauga axa OY
plt.axhline(0, c='black')  # Adauga axa OX

plt.xlabel('x')  # Adauga titlul axei OX
plt.ylabel('f(x)')  # Adauga titlul axei OY
plt.title('Graficul functiei f = x^3 + 2x^2 - x - 2')  # Titlul graficului

plt.grid(b=True)
plt.show()

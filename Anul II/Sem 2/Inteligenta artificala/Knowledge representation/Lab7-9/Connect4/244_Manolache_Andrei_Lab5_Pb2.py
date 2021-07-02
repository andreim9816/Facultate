import time


def elem_identice(lista):
    """ Primeste o lista si returneaza
	-> simbolul jucatorului castigator (daca lista contine doar acel simbol repetat)
	-> sau False (daca a fost remiza sau daca nu s-a terminat jocul)
	"""
    mt = set(lista)
    if len(mt) == 1:
        castigator = list(mt)[0]
        if castigator != Joc.GOL:
            return castigator
        else:
            return False
    else:
        return False


def interior(lin, col):
    """Functie care verifica daca coordonatele (lin,col) se afla in interiorul matricei"""
    return 0 <= lin < Joc.NR_LINII and 0 <= col < Joc.NR_COLOANE


def afla_pozitia(list1, list2):
    """Functie care primeste 2 matrici(sub forma de liste) si returneaza pozitia cu continut diferit"""
    for i in range(len(list1)):
        if list1[i] != list2[i]:
            return i
    return False


class Joc:
    """
    Clasa care defineste jocul. Se va schimba de la un joc la altul.
    """
    NR_COLOANE = 9
    NR_LINII = 6
    NR_CONNECT = 4  # cu cate simboluri adiacente se castiga
    SIMBOLURI_JUC = ['X', '0']  # ['G', 'R'] sau ['X', '0']
    JMIN = None  # 'R'
    JMAX = None  # 'G'
    GOL = '.'

    def __init__(self, tabla=None):
        self.matr = tabla or [Joc.GOL] * (Joc.NR_COLOANE * Joc.NR_LINII)


    def final(self, pozitie=None):
        # returnam simbolul jucatorului castigator daca are 4 piese adiacente
        #	pe linie, coloana, diagonala \ sau diagonala /
        # sau returnam 'remiza'
        # sau 'False' daca nu s-a terminat jocul

        rez = False
        if pozitie is None:  # Pentru JMAX
            # verificam linii
            # TO DO ..........
            for lin in range(Joc.NR_LINII):
                for col in range(Joc.NR_COLOANE - Joc.NR_CONNECT + 1):
                    start = lin * Joc.NR_COLOANE + col
                    stop = start + Joc.NR_CONNECT
                    # print(lin, col, start, stop)
                    rez = elem_identice(self.matr[start: stop])
                    # print(rez)
                    if rez is not False:
                        return rez

            # verificam coloane
            # T0 DO ..........
            for lin in range(Joc.NR_LINII - Joc.NR_CONNECT + 1):
                for col in range(Joc.NR_COLOANE):
                    start = lin * Joc.NR_COLOANE + col
                    stop = start + (Joc.NR_CONNECT - 1) * Joc.NR_COLOANE + 1
                    pas = Joc.NR_COLOANE
                    rez = elem_identice(self.matr[start: stop: pas])
                    if rez is not False:
                        return rez

            # verificam diagonale \
            # TO DO..........
            max = Joc.NR_COLOANE * Joc.NR_LINII - 1
            for lin in range(Joc.NR_LINII - Joc.NR_CONNECT + 1):
                for col in range(Joc.NR_COLOANE - Joc.NR_CONNECT + 1):
                    start = lin * Joc.NR_COLOANE + col
                    stop = start + (Joc.NR_CONNECT - 1) * (Joc.NR_COLOANE + 1) + 1
                    pas = Joc.NR_COLOANE + 1
                    if stop <= max + 1:
                        rez = elem_identice(self.matr[start: stop: pas])
                        if rez is not False:
                            return rez

            # verificam diagonale /
            for lin in range(Joc.NR_LINII - Joc.NR_CONNECT + 1):
                for col in range(Joc.NR_COLOANE - Joc.NR_CONNECT + 1):
                    start = lin * Joc.NR_COLOANE + col + Joc.NR_CONNECT - 1
                    stop = start + (Joc.NR_CONNECT - 1) * (Joc.NR_COLOANE - 1) + 1
                    pas = Joc.NR_COLOANE - 1
                    rez = elem_identice(self.matr[start: stop: pas])
                    if rez is not False:
                        return rez
        else:  # Pentru JMIN, deoarece stim pozitia unde a avut loc mutarea

            # Transforma lista in matrice
            matr = [self.matr[i: i + Joc.NR_COLOANE] for i in range(0, len(self.matr), Joc.NR_COLOANE)]
            linie_poz = pozitie // Joc.NR_COLOANE
            coloana_poz = pozitie - linie_poz * Joc.NR_COLOANE

            # Pe linie
            start = 0 if 0 > coloana_poz - Joc.NR_CONNECT + 1 else coloana_poz - Joc.NR_CONNECT + 1
            stop = min(coloana_poz, Joc.NR_COLOANE - Joc.NR_CONNECT)
            for j in range(start - stop + 1):
                rez = elem_identice([matr[linie_poz][start + j + nr] for nr in range(Joc.NR_CONNECT)])
                if rez is not False:
                    return rez

            # Pe coloana
            start = 0 if 0 > linie_poz - Joc.NR_CONNECT + 1 else linie_poz - Joc.NR_CONNECT + 1
            stop = min(linie_poz, Joc.NR_LINII - Joc.NR_CONNECT)
            for i in range(stop - start + 1):
                rez = elem_identice([matr[start + i + nr][coloana_poz] for nr in range(Joc.NR_CONNECT)])
                if rez is not False:
                    return rez

            # Pe diagonala \
            for i in range(Joc.NR_CONNECT):
                start_lin = linie_poz - i
                start_col = coloana_poz - i
                stop_lin = linie_poz + Joc.NR_CONNECT - i - 1
                stop_col = coloana_poz + Joc.NR_CONNECT - i - 1
                if interior(start_lin, start_col) and interior(stop_lin, stop_col):  # Marginile sunt in interior, deci toate piesele sunt in interiorul tablei
                    start = start_lin * Joc.NR_COLOANE + start_col
                    stop = start + (Joc.NR_CONNECT - 1) * (Joc.NR_COLOANE + 1) + 1
                    pas = Joc.NR_COLOANE + 1
                    rez = elem_identice(self.matr[start: stop: pas])
                    if rez is not False:
                        return rez

            # Pe diagonala /
            for i in range(Joc.NR_CONNECT):
                start_lin = linie_poz - i
                start_col = coloana_poz + i
                stop_lin = linie_poz + Joc.NR_CONNECT - i - 1
                stop_col = start_col - Joc.NR_CONNECT + 1
                if interior(start_lin, start_col) and interior(stop_lin, stop_col):  # Marginile sunt in interior, deci toate piesele sunt in interiorul tablei
                    start = start_lin * Joc.NR_COLOANE + start_col
                    stop = start + (Joc.NR_CONNECT - 1) * (Joc.NR_COLOANE - 1) + 1
                    pas = Joc.NR_COLOANE - 1
                    rez = elem_identice(self.matr[start: stop: pas])
                    if rez is not False:
                        return rez

        if rez == False and Joc.GOL not in self.matr:
            return 'remiza'
        else:
            return False

    def mutari_joc(self, jucator_opus):
        l_mutari = []

        index_ultima_linie_start = (Joc.NR_LINII - 1) * Joc.NR_COLOANE
        index_ultima_linie_stop = Joc.NR_LINII * Joc.NR_COLOANE - 1

        lista_start = [i for i in range(index_ultima_linie_start, index_ultima_linie_stop + 1)]

        for index in lista_start:
            if self.matr[index] == Joc.GOL:
                tabla_noua = self.matr[0: self.NR_LINII * self.NR_COLOANE]
                tabla_noua[index] = jucator_opus
                l_mutari.append(Joc(tabla_noua))
            else:
                while index >= 0 and self.matr[index] != Joc.GOL:
                    index -= Joc.NR_COLOANE
                if index >= 0:
                    tabla_noua = self.matr[0: self.NR_LINII * self.NR_COLOANE]
                    tabla_noua[index] = jucator_opus
                    l_mutari.append(Joc(tabla_noua))

        return l_mutari

    def interval_deschis(self, lista, jucator):
        juc_opus = 'X' if jucator == '0' else '0'
        if juc_opus in lista:
            return 0
        return 1

    def nr_intervale_deschise(self, jucator):
        # un interval de 4 pozitii adiacente (pe linie, coloana, diag \ sau diag /)
        # este deschis pt "jucator" daca nu contine "juc_opus"

        juc_opus = Joc.JMIN if jucator == Joc.JMAX else Joc.JMAX
        rez = 0

        # linii
        # TO DO.....
        for lin in range(Joc.NR_LINII):
            for col in range(Joc.NR_COLOANE - Joc.NR_CONNECT + 1):
                start = lin * Joc.NR_COLOANE + col
                stop = start + Joc.NR_CONNECT
                rez += self.interval_deschis(self.matr[start: stop], jucator)

        # coloane
        # TO DO.....
        for lin in range(Joc.NR_LINII - Joc.NR_CONNECT + 1):
            for col in range(Joc.NR_COLOANE):
                start = lin * Joc.NR_COLOANE + col
                stop = start + (Joc.NR_CONNECT - 1) * Joc.NR_COLOANE + 1
                pas = Joc.NR_COLOANE
                rez += self.interval_deschis(self.matr[start: stop: pas], jucator)

        # diagonale \
        # TO DO.....
        max = Joc.NR_COLOANE * Joc.NR_LINII - 1
        for lin in range(Joc.NR_LINII - Joc.NR_CONNECT + 1):
            for col in range(Joc.NR_COLOANE - Joc.NR_CONNECT + 1):
                start = lin * Joc.NR_COLOANE + col
                stop = start + (Joc.NR_CONNECT - 1) * (Joc.NR_COLOANE + 1) + 1
                pas = Joc.NR_COLOANE + 1
                if stop <= max + 1:
                    rez += self.interval_deschis(self.matr[start: stop: pas], jucator)

        # diagonale /
        # TO DO.....
        for lin in range(Joc.NR_LINII - Joc.NR_CONNECT + 1):
            for col in range(Joc.NR_COLOANE - Joc.NR_CONNECT + 1):
                start = lin * Joc.NR_COLOANE + col + Joc.NR_CONNECT - 1
                stop = start + (Joc.NR_CONNECT - 1) * (Joc.NR_COLOANE - 1) + 1
                pas = Joc.NR_COLOANE - 1
                rez += self.interval_deschis(self.matr[start: stop: pas], jucator)

        return rez

    def fct_euristica(self):
        return self.nr_intervale_deschise(Joc.JMAX) - self.nr_intervale_deschise(Joc.JMIN)

    def estimeaza_scor(self, adancime):
        t_final = self.final()
        if t_final == Joc.JMAX:
            return (999 + adancime)
        elif t_final == Joc.JMIN:
            return (-999 - adancime)
        elif t_final == 'remiza':
            return 0
        else:
            return self.fct_euristica()

    def __str__(self):
        sir = ''
        for nr_col in range(self.NR_COLOANE):
            sir += str(nr_col) + ' '
        sir += '\n'

        for lin in range(self.NR_LINII):
            k = lin * self.NR_COLOANE
            sir += (" ".join([str(x) for x in self.matr[k: k + self.NR_COLOANE]]) + "\n")
        return sir


class Stare:
    """
    Clasa folosita de algoritmii minimax si alpha-beta
    Are ca proprietate tabla de joc
    Functioneaza cu conditia ca in cadrul clasei Joc sa fie definiti JMIN si JMAX (cei doi jucatori posibili)
    De asemenea cere ca in clasa Joc sa fie definita si o metoda numita mutari_joc() care ofera lista cu
    configuratiile posibile in urma mutarii unui jucator
    """

    ADANCIME_MAX = None

    def __init__(self, tabla_joc, j_curent, adancime, parinte=None, scor=None):
        self.tabla_joc = tabla_joc
        self.j_curent = j_curent

        # adancimea in arborele de stari
        self.adancime = adancime

        # scorul starii (daca e finala) sau al celei mai bune stari-fiice (pentru jucatorul curent)
        self.scor = scor

        # lista de mutari posibile din starea curenta
        self.mutari_posibile = []

        # cea mai buna mutare din lista de mutari posibile pentru jucatorul curent
        self.stare_aleasa = None

    def jucator_opus(self):
        if self.j_curent == Joc.JMIN:
            return Joc.JMAX
        else:
            return Joc.JMIN

    def mutari_stare(self):
        l_mutari = self.tabla_joc.mutari_joc(self.j_curent)
        juc_opus = self.jucator_opus()
        l_stari_mutari = [Stare(mutare, juc_opus, self.adancime - 1, parinte=self) for mutare in l_mutari]

        return l_stari_mutari

    def __str__(self):
        sir = str(self.tabla_joc) + "(Juc curent: " + self.j_curent + ")\n"
        return sir


""" Algoritmul MinMax """


def min_max(stare):
    if stare.adancime == 0 or stare.tabla_joc.final():
        stare.scor = stare.tabla_joc.estimeaza_scor(stare.adancime)
        return stare

    # calculez toate mutarile posibile din starea curenta
    stare.mutari_posibile = stare.mutari_stare()

    # aplic algoritmul minimax pe toate mutarile posibile (calculand astfel subarborii lor)
    mutari_scor = [min_max(mutare) for mutare in stare.mutari_posibile]

    if stare.j_curent == Joc.JMAX:
        # daca jucatorul e JMAX aleg starea-fiica cu scorul maxim
        stare.stare_aleasa = max(mutari_scor, key=lambda x: x.scor)
    else:
        # daca jucatorul e JMIN aleg starea-fiica cu scorul minim
        stare.stare_aleasa = min(mutari_scor, key=lambda x: x.scor)

    stare.scor = stare.stare_aleasa.scor
    return stare


def alpha_beta(alpha, beta, stare):
    if stare.adancime == 0 or stare.tabla_joc.final():
        stare.scor = stare.tabla_joc.estimeaza_scor(stare.adancime)
        return stare

    if alpha >= beta:
        return stare  # este intr-un interval invalid deci nu o mai procesez

    stare.mutari_posibile = stare.mutari_stare()

    if stare.j_curent == Joc.JMAX:
        scor_curent = float('-inf')

        for mutare in stare.mutari_posibile:
            # calculeaza scorul
            stare_noua = alpha_beta(alpha, beta, mutare)

            if (scor_curent < stare_noua.scor):
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor
            if (alpha < stare_noua.scor):
                alpha = stare_noua.scor
                if alpha >= beta:
                    break

    elif stare.j_curent == Joc.JMIN:
        scor_curent = float('inf')

        for mutare in stare.mutari_posibile:
            stare_noua = alpha_beta(alpha, beta, mutare)

            if (scor_curent > stare_noua.scor):
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor

            if (beta > stare_noua.scor):
                beta = stare_noua.scor
                if alpha >= beta:
                    break

    stare.scor = stare.stare_aleasa.scor

    return stare


def afis_daca_final(stare_curenta, pozitie=None):
    # ?? TO DO:
    # de adagat parametru "pozitie", ca sa nu verifice mereu toata tabla,
    # ci doar linia, coloana, 2 diagonale pt elementul nou, de pe "pozitie"

    if pozitie is None:
        final = stare_curenta.tabla_joc.final()
    else:
        final = stare_curenta.tabla_joc.final(pozitie)

    if (final):
        if (final == "remiza"):
            print("Remiza!")
        else:
            print("A castigat " + final)

        return True

    return False


def main():
    # initializare algoritm
    raspuns_valid = False
    while not raspuns_valid:
        tip_algoritm = input("Algorimul folosit? (raspundeti cu 1 sau 2)\n 1.Minimax\n 2.Alpha-beta\n ")
        if tip_algoritm in ['1', '2']:
            raspuns_valid = True
        else:
            print("Nu ati ales o varianta corecta.")

    # initializare ADANCIME_MAX
    raspuns_valid = False
    while not raspuns_valid:
        n = input("Adancime maxima a arborelui: ")
        if n.isdigit():
            Stare.ADANCIME_MAX = int(n)
            raspuns_valid = True
        else:
            print("Trebuie sa introduceti un numar natural nenul.")

    # initializare jucatori
    [s1, s2] = Joc.SIMBOLURI_JUC.copy()  # lista de simboluri posibile
    raspuns_valid = False
    while not raspuns_valid:
        Joc.JMIN = str(input("Doriti sa jucati cu {} sau cu {}? ".format(s1, s2))).upper()
        if (Joc.JMIN in Joc.SIMBOLURI_JUC):
            raspuns_valid = True
        else:
            print("Raspunsul trebuie sa fie {} sau {}.".format(s1, s2))
    Joc.JMAX = s1 if Joc.JMIN == s2 else s2

    # initializare tabla
    tabla_curenta = Joc()
    print("Tabla initiala")
    print(str(tabla_curenta))

    # creare stare initiala
    stare_curenta = Stare(tabla_curenta, Joc.SIMBOLURI_JUC[0], Stare.ADANCIME_MAX)

    linie = -1
    coloana = -1
    while True:
        if (stare_curenta.j_curent == Joc.JMIN):
            # muta jucatorul
            raspuns_valid = False
            while not raspuns_valid:
                try:
                    coloana = int(input("coloana = "))

                    # TO DO......
                    # de verificat daca "coloana" este in intervalul corect,
                    # apoi de gasit pe ce "linie" este cea mai de jos
                    # casuta goala de pe acea "coloana"

                    if 0 <= coloana < Joc.NR_COLOANE:  # Interval corect
                        if stare_curenta.tabla_joc.matr[coloana] != Joc.GOL:  # Daca patratica de sus e ocupata
                            print("Toata coloana este ocupata.")
                        else:  # Pot pune pe coloana respectiva, caut linia
                            # for linie in range(Joc.NR_LINII - 1):
                            #     if stare_curenta.tabla_joc.matr[linie * Joc.NR_COLOANE + coloana] != Joc.GOL:
                            #         break
                            linie = 1
                            while linie <= Joc.NR_LINII - 1:
                                if stare_curenta.tabla_joc.matr[linie * Joc.NR_COLOANE + coloana] != Joc.GOL:
                                    linie -= 1
                                    raspuns_valid = True
                                    break
                                else:
                                    linie += 1
                            if linie == Joc.NR_LINII:
                                linie = Joc.NR_LINII - 1
                                raspuns_valid = True

                    else:
                        print("Coloana invalida (trebuie sa fie un numar intre 0 si {}).".format(Joc.NR_COLOANE - 1))
                    print(linie, coloana)
                except ValueError:
                    print("Coloana trebuie sa fie un numar intreg.")

            # dupa iesirea din while sigur am valida coloana
            # deci pot plasa simbolul pe "tabla de joc"
            print("A IESIT")
            pozitie = linie * Joc.NR_COLOANE + coloana
            stare_curenta.tabla_joc.matr[pozitie] = Joc.JMIN

            # afisarea starii jocului in urma mutarii utilizatorului
            print("\nTabla dupa mutarea jucatorului")
            print(str(stare_curenta))

            # testez daca jocul a ajuns intr-o stare finala
            # si afisez un mesaj corespunzator in caz ca da
            if (afis_daca_final(stare_curenta, pozitie)):
                break

            # S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent = stare_curenta.jucator_opus()

        # --------------------------------
        else:  # jucatorul e JMAX (calculatorul)
            # Mutare calculator

            # preiau timpul in milisecunde de dinainte de mutare
            t_inainte = int(round(time.time() * 1000))
            if tip_algoritm == '1':
                stare_actualizata = min_max(stare_curenta)
            else:  # tip_algoritm==2
                stare_actualizata = alpha_beta(-5000, 5000, stare_curenta)


            stare_curenta.tabla_joc = stare_actualizata.stare_aleasa.tabla_joc
            print("Tabla dupa mutarea calculatorului")
            print(str(stare_curenta))

            # preiau timpul in milisecunde de dupa mutare
            t_dupa = int(round(time.time() * 1000))
            print("Calculatorul a \"gandit\" timp de " + str(t_dupa - t_inainte) + " milisecunde.")

            if (afis_daca_final(stare_curenta)):
                break

            # S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent = stare_curenta.jucator_opus()


if __name__ == "__main__":
    main()

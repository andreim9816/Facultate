import time


def interior(lin, col):
    """Functie care verifica daca coordonatele (lin,col) se afla in interiorul matricei"""
    return 0 <= lin < Joc.NR_LINII and 0 <= col < Joc.NR_COLOANE


def miscare_valida(matr, lin, col, jucator):
    """Functie care verifica daca pot muta o piesa pe pozitia (lin,col)"""
    dx = [-1, 0, 1, 1, 1, 0, -1, -1]
    dy = [-1, -1, -1, 0, 1, 1, 1, 0]

    if matr[lin][col] != Joc.GOL:
        return False

    for index in range(len(dx)):
        new_lin = dx[index] + lin
        new_col = dy[index] + col
        count = 0
        while interior(new_lin, new_col) and matr[new_lin][new_col] != Joc.GOL and matr[new_lin][
            new_col] != jucator:  # Daca pe pozitia respectiva se afla o piesa de-a adversarului, verific daca mergand in directia respectiva am o piesa de-a jucatorului
            new_lin += dx[index]
            new_col += dy[index]
            count += 1

        if interior(new_lin, new_col) and matr[new_lin][
            new_col] == jucator and count > 0:  # Ma aflu in interiorul tablei si am dat peste o piesa de-a jucatorului si am sarit peste cel putin o piesa de-a adversarului
            return True
    return False


def marcheaza_piese_jucator(matr, jucator, lin_start, col_start, lin_stop, col_stop):
    """Functie care transforma piesele adversarului in piesele jucatorului intre 2 pozitii date"""
    dx = 0
    dy = 0

    if lin_start > lin_stop:
        dx = -1
    elif lin_start < lin_stop:
        dx = 1
    if col_start < col_stop:
        dy = 1
    elif col_start > col_stop:
        dy = -1

    # print("lin_start = %d col_start = %d lin_stop = %d col_stop = %d dx = %d dy = %d" % (lin_start, col_start, lin_stop, col_stop, dx, dy))
    matr[lin_start][col_start] = jucator
    matr[lin_stop][col_stop] = jucator

    while lin_start != lin_stop or col_start != col_stop:  # Transform piesele adversarului in ale jucatorului
        lin_start += dx
        col_start += dy
        # print(lin_start, col_start)
        matr[lin_start][col_start] = jucator

    # print("Dupa update, tabla arata: ")
    # afis(matr)


def update_tabla(matr, jucator, lin_start, col_start):
    """Functie care primeste o pozitie de pe tabla(lin_start, col_start), semnificand unde va fi pusa noua piesa
       si updateaza tabla. Daca pun o piesa alba la pozitia (lin_start, col_start) = (3, 4), atunci tabla va arata:
       # # # # # #          # # # # # #
       # # a # # #          # # a # # #
       # # # n # #  -- >    # # # a # #
       # a n n # #          # a a a a #
       # # # n # #          # # # a # #
       # # a # # #          # # a # # #
          """
    dx = [-1, 0, 1, 1, 1, 0, -1, -1]
    dy = [-1, -1, -1, 0, 1, 1, 1, 0]
    count = 0
    matr[lin_start][col_start] = jucator
    # print("Lin start = %d, Col start = %d" %(lin_start, col_start))

    for index in range(len(dx)):
        lin_nou = lin_start + dx[index]
        col_nou = col_start + dy[index]
        # print("Incepe cu %d, %d" % (lin_nou, col_nou))

        while interior(lin_nou, col_nou) and matr[lin_nou][col_nou] != jucator and matr[lin_nou][col_nou] != Joc.GOL:
            count += 1
            lin_nou += dx[index]
            col_nou += dy[index]

        # print("S-a terminat cu %d, %d" % (lin_nou, col_nou))

        if interior(lin_nou, col_nou) and count > 0 and matr[lin_nou][
            col_nou] == jucator:  # Am ajuns pe o piesa de-a jucatorului
            # print("E ok, %d %d" % (lin_nou, col_nou))
            marcheaza_piese_jucator(matr, jucator, lin_start, col_start, lin_nou,
                                    col_nou)  # Updateaza tabla pe linia/coloana/diagonala respectiva
            # print("Dupa marcheza_piese_jucator, tabla arata: ")
            # afis(matr)


def afis(matr):
    print(matr[0])
    print(matr[1])
    print(matr[2])
    print(matr[3])
    print(matr[4])
    print(matr[5])
    print(matr[6])
    print(matr[7])
    print("\n")


class Joc:
    """
	Clasa care defineste jocul. Se va schimba de la un joc la altul.
	"""
    NR_LINII = 8
    NR_COLOANE = 8
    SIMBOLURI_JUC = ['n', 'a']
    JMIN = None
    JMAX = None
    GOL = '#'

    def __init__(self, tabla=None):
        self.matr = tabla or [[Joc.GOL for j in range(Joc.NR_COLOANE)] for i in range(Joc.NR_LINII)]

        if tabla is None:
            self.matr[int(self.NR_LINII / 2) - 1][int(self.NR_COLOANE / 2) - 1] = Joc.SIMBOLURI_JUC[1]
            self.matr[int(self.NR_LINII / 2)][int(self.NR_COLOANE / 2)] = Joc.SIMBOLURI_JUC[1]
            self.matr[int(self.NR_LINII / 2) - 1][int(self.NR_COLOANE / 2)] = Joc.SIMBOLURI_JUC[0]
            self.matr[int(self.NR_LINII / 2)][int(self.NR_COLOANE / 2) - 1] = Joc.SIMBOLURI_JUC[0]

    def scor_jucator(self, jucator):
        """Functie care returneaza numarul de piese ale lui jucator, calculand scorul curent"""
        nr = 0
        for i in range(Joc.NR_LINII):
            for j in range(Joc.NR_COLOANE):
                if self.matr[i][j] == jucator:
                    nr += 1
        return nr

    def mutare_posibila(self, lin, col, jucator):
        """Functie care verifica daca un jucator poate muta pe pozitia (lin,col)"""

        dx = [-1, 0, 1, 1, 1, 0, -1, -1]
        dy = [-1, -1, -1, 0, 1, 1, 1, 0]

        if self.matr[lin][col] != Joc.GOL:
            return False

        for index in range(len(dx)):
            new_lin = dx[index] + lin
            new_col = dy[index] + col
            count = 0
            while interior(new_lin, new_col) and self.matr[new_lin][new_col] != Joc.GOL and self.matr[new_lin][
                new_col] != jucator:  # Daca pe pozitia respectiva se afla o piesa de-a adversarului, verific daca mergand in directia respectiva am o piesa de-a jucatorului
                new_lin += dx[index]
                new_col += dy[index]
                count += 1

            if interior(new_lin, new_col) and self.matr[new_lin][
                new_col] == jucator and count > 0:  # Ma aflu in interiorul tablei si am dat peste o piesa de-a jucatorului si am sarit peste cel putin o piesa de-a adversarului
                return True
        return False

    def numar_mutari_posibile(self, jucator):
        """Functie care calculeaza numarul de mutari posibile ale unui jucator"""
        nr = 0
        for i in range(Joc.NR_LINII):
            for j in range(Joc.NR_COLOANE):
                if self.matr[i][j] == Joc.GOL:
                    res = self.mutare_posibila(i, j, jucator)
                    if res is True:
                        nr += 1
        return nr

    def final(self):

        jmax_mutari_posibile = self.numar_mutari_posibile(Joc.JMAX)
        jmin_mutari_posibile = self.numar_mutari_posibile(Joc.JMIN)

        jmax_scor = self.scor_jucator(Joc.JMAX)
        jmin_scor = self.scor_jucator(Joc.JMIN)

        if jmax_mutari_posibile == 0 and jmin_mutari_posibile == 0:  # Nu mai poate muta nimeni sau nu tabla este completa
            if jmax_scor > jmin_scor:
                return Joc.JMAX
            elif jmax_scor == jmin_scor:
                return "remiza"
            else:
                return Joc.JMIN
        else:
            return False

    def mutari_joc(self, jucator):

        """Functie care genereaza toate mutarile posibile"""

        l_mutari = []
        for lin in range(self.NR_LINII):
            for col in range(self.NR_COLOANE):
                res = self.mutare_posibila(lin, col, jucator)  # Daca jucatorul poate muta o piesa pe pozitia (lin,col)
                if res is True:  # Daca jucatorul poate muta pe pozitia respectiva
                    tabla_noua = [x[:] for x in self.matr]  # Copiez tabla
                    tabla_noua[lin][col] = jucator
                    update_tabla(tabla_noua, jucator, lin, col)
                    l_mutari.append(Joc(tabla_noua))

        return l_mutari

    def estimeaza_scor(self, adancime):
        t_final = self.final()
        if t_final == Joc.JMAX:
            return (999 + adancime)
        elif t_final == Joc.JMIN:
            return (-999 - adancime)
        elif t_final == 'remiza':
            return 0
        else:
            return self.scor_jucator(Joc.JMAX) - self.scor_jucator(Joc.JMIN)

    def __str__(self):

        sir = (
                "    a b c d e f g h " + "\n" +
                "  ------------------" + "\n" +
                "0 | " + " ".join([str(x) for x in self.matr[0]]) + "\n" +
                "1 | " + " ".join([str(x) for x in self.matr[1]]) + "\n" +
                "2 | " + " ".join([str(x) for x in self.matr[2]]) + "\n" +
                "3 | " + " ".join([str(x) for x in self.matr[3]]) + "\n" +
                "4 | " + " ".join([str(x) for x in self.matr[4]]) + "\n" +
                "5 | " + " ".join([str(x) for x in self.matr[5]]) + "\n" +
                "6 | " + " ".join([str(x) for x in self.matr[6]]) + "\n" +
                "7 | " + " ".join([str(x) for x in self.matr[7]]) + "\n"
        )

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
        self.tabla_joc = tabla_joc  # un obiect de tip Joc => „tabla_joc.matr”
        self.j_curent = j_curent  # simbolul jucatorului curent

        # adancimea in arborele de stari
        #	(scade cu cate o unitate din „tata” in „fiu”)
        self.adancime = adancime

        # scorul starii (daca e finala, adica frunza a arborelui)
        # sau scorul celei mai bune stari-fiice (pentru jucatorul curent)
        self.scor = scor

        # lista de mutari posibile din starea curenta
        self.mutari_posibile = []  # lista va contine obiecte de tip Stare

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
        sir = str(self.tabla_joc) + "(Juc curent:" + self.j_curent + ")\n"
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

    # for i in mutari_scor:
    #     print(str(i))
    # print("\n\n")


    if stare.j_curent == Joc.JMAX:
        if len(mutari_scor) == 0:
            stare.scor = float('-inf')
            return stare
        # daca jucatorul e JMAX aleg starea-fiica cu scorul maxim
        stare.stare_aleasa = max(mutari_scor, key=lambda x: x.scor)
    else:
        if len(mutari_scor) == 0:
            stare.scor = float('inf')
            return stare
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
        if not stare.mutari_posibile:
            stare.scor = float('-inf')
            return stare
        else:
            scor_curent = float('-inf')

            for mutare in stare.mutari_posibile:
                # calculeaza scorul
                stare_noua = alpha_beta(alpha, beta, mutare)

                if (scor_curent <= stare_noua.scor):
                    stare.stare_aleasa = stare_noua
                    scor_curent = stare_noua.scor

                if (alpha < stare_noua.scor):
                    alpha = stare_noua.scor
                    if alpha >= beta:
                        break

    elif stare.j_curent == Joc.JMIN:
        if not stare.mutari_posibile:
            stare.scor = float('inf')
            return stare
        else:
            scor_curent = float('inf')

            for mutare in stare.mutari_posibile:
                stare_noua = alpha_beta(alpha, beta, mutare)

                if (scor_curent >= stare_noua.scor):
                    stare.stare_aleasa = stare_noua
                    scor_curent = stare_noua.scor

                if (beta > stare_noua.scor):
                    beta = stare_noua.scor
                    if alpha >= beta:
                        break

    # print(stare.scor)
    # print(str(stare.stare_aleasa))
    # print("\n")
    stare.scor = stare.stare_aleasa.scor

    return stare


def afis_daca_final(stare_curenta):
    final = stare_curenta.tabla_joc.final()
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
    tip_algoritm = 0
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
        Joc.JMIN = str(input("Doriti sa jucati cu {} sau cu {}? ".format(s1, s2)))
        if (Joc.JMIN in Joc.SIMBOLURI_JUC):
            raspuns_valid = True
        else:
            print("Raspunsul trebuie sa fie {} sau {}.".format(s1, s2))
    Joc.JMAX = s1 if Joc.JMIN == s2 else s2

    # initializare tabla
    tabla_curenta = Joc(
                        )

    print("Tabla initiala")
    print(str(tabla_curenta))

    # creare stare initiala
    stare_curenta = Stare(tabla_curenta, Joc.SIMBOLURI_JUC[0], Stare.ADANCIME_MAX)
    linie = -1
    coloana = -1
    while True:
        if (stare_curenta.j_curent == Joc.JMIN):

            if tabla_curenta.numar_mutari_posibile(Joc.JMIN) == 0:  # Jucatorul nu poate muta
                print("\nPASS JUCATOR\n")
                stare_curenta.j_curent = stare_curenta.jucator_opus()
            else:

                # muta jucatorul
                raspuns_valid = False
                while not raspuns_valid:
                    try:
                        linie = int(input("linie = "))
                        coloana = ord(input("coloana = ")) - ord('a')

                        if 0 <= coloana < Joc.NR_COLOANE and 0 <= linie < Joc.NR_LINII:  # Interval corect
                            if miscare_valida(stare_curenta.tabla_joc.matr, linie, coloana, Joc.JMIN):
                                raspuns_valid = True
                            else:
                                print("Mutare nevalida!")
                        else:
                            print("Coloana sau linia invalida (trebuie sa fie un numar intre 0 si {} sau 0 si {}).".format(
                                Joc.NR_COLOANE - 1, Joc.NR_LINII - 1))
                        print(linie, coloana)
                    except ValueError:
                        print("Coloana sau linia trebuie sa fie un numar intreg.")

                # dupa iesirea din while sigur am valida coloana
                # deci pot plasa simbolul pe "tabla de joc"

                stare_curenta.tabla_joc.matr[linie][coloana] = Joc.JMIN
                update_tabla(stare_curenta.tabla_joc.matr, stare_curenta.j_curent, linie, coloana)  # Updateaza tabla

                # afisarea starii jocului in urma mutarii utilizatorului
                print("\nTabla dupa mutarea jucatorului")
                print(str(stare_curenta))

                # testez daca jocul a ajuns intr-o stare finala
                # si afisez un mesaj corespunzator in caz ca da
                if (afis_daca_final(stare_curenta)):
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

            # Daca nu mai poate fi facuta nicio mutare, se opreste. Conditie folosita in cazul in care initializez tabla
            # jocului ca fiind deja o "stare finala".

            if (afis_daca_final(stare_curenta)):
                break

            print("Randul calculatorului")
            if tabla_curenta.numar_mutari_posibile(Joc.JMAX) == 0:  # Daca nu mai poate fi facuta nicio mutare
                print("\nPASS CALCULATOR\n")
                t_dupa = int(round(time.time() * 1000))
                print("Calculatorul a \"gandit\" timp de " + str(t_dupa - t_inainte) + " milisecunde.")
                stare_curenta.j_curent = stare_curenta.jucator_opus()
            else:

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

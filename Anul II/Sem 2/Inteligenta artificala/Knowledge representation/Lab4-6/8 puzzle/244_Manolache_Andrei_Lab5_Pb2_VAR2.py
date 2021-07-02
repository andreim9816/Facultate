import copy
import time
import math

""" definirea problemei """
# Rezolvarea problemei 2 (8 puzzle), VAR2.
nr_euristica = 1  # Manhattan


# Functie care returneaza True daca o pozitie [lin][col] se afla in interiorul unei matrice patratice de dimensiuni L_matrice x L_matrice
def interior(lin, col, L_matrice):
    if L_matrice > lin >= 0 and L_matrice > col >= 0:
        return True
    return False


class Nod:
    def __init__(self, info, h):
        self.info = info  # Copiaza informatia
        self.h = h

    def __str__(self):
        return "({}, h={})".format(self.info, self.h)

    def __repr__(self):
        return f"({self.info}, h={self.h})"


class Problema:

    def __init__(self, start=[[2, 4, 3], [8, 7, 5], [1, 0, 6]], scop=[[1, 2, 3], [4, 5, 6], [7, 8, 9]]):

        self.nod_start = Nod(start, float('Inf'))
        self.nod_scop = scop
        self.N = len(start)


""" Sfarsit definire problema """

""" Clase folosite in algoritmul A* """


class NodParcurgere:
    """
    O clasa care cuprinde informatiile asociate unui nod din listele open/closed
    Cuprinde o referinta catre nodul in sine (din graf)
    dar are ca proprietati si valorile specifice algoritmului A* (f si g).
    Se presupune ca h este proprietate a nodului din graf
    """

    problema = None  # atribut al clasei

    def __init__(self, nod_graf, parinte=None, g=0, f=None):
        self.nod_graf = nod_graf  # obiect de tip Nod
        self.parinte = parinte  # obiect de tip Nod
        self.g = g  # costul drumului de la radacina pana la nodul curent
        if f is None:
            self.f = self.g + self.nod_graf.h
        else:
            self.f = f

    def euristica_1(self, info):
        sum = 0
        # Comparam continutul stivelor, incrementam cand este diferit
        for lin in range(self.problema.N):
            for col in range(self.problema.N):
                numar = info[lin][col]
                if numar != 0:  # Pentru toate placutele diferite de 0
                    for i in range(self.problema.N):
                        for j in range(self.problema.N):
                            if self.problema.nod_scop[i][j] == numar:
                                sum += abs(i - lin) + abs(j - col)
                                break
        return sum

    def euristica_2(self, info):
        sum = 0
        for lin in range(self.problema.N):
            for col in range(self.problema.N):
                if info[lin][col] != 0:
                    if info[lin][col] != self.problema.nod_scop[lin][col]:
                        sum += 1
        return sum

    def drum_arbore(self):
        """
        Functie care calculeaza drumul asociat unui nod din arborele de cautare.
        Functia merge din parinte in parinte pana ajunge la radacina
        """
        nod_c = self
        drum = [nod_c]
        while nod_c.parinte is not None:
            drum = [nod_c.parinte] + drum
            nod_c = nod_c.parinte
        return drum

    def contine_in_drum(self, nod):
        """
        Functie care verifica daca nodul "nod" se afla in drumul dintre radacina si nodul curent (self).
        Verificarea se face mergand din parinte in parinte pana la radacina
        Se compara doar informatiile nodurilor (proprietatea info)
        Returnati True sau False.

        "nod" este obiect de tip Nod (are atributul "nod.info")
        "self" este obiect de tip NodParcurgere (are "self.nod_graf.info")
        """
        # TO DO...
        nod_curent = self
        while nod_curent is not None:  # Cat timp nu am ajuns la radacina
            if nod.info == nod_curent.nod_graf.info:  # Daca au continutul egal
                return True
            else:
                nod_curent = nod_curent.parinte  # Merg mai departe
        return False

    # se modifica in functie de problema
    def expandeaza(self):
        """
        Pentru nodul curent (self) parinte, trebuie sa gasiti toti succesorii (fiii)
        si sa returnati o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
        sau lista vida, daca nu exista niciunul.
        (Fiecare tuplu contine un obiect de tip Nod si un numar.)
        """
        # TO DO...
        lista = []
        nod_curent = self
        dx = [-1, 0, 1, 0]  # Vector deplasare pozitii pe linii
        dy = [0, -1, 0, 1]  # Vector deplasare pozitii pe coloane

        # Afla coordonatele patratului liber, semnificat prin 0
        L_matrice = self.problema.N
        lin_zero = 0
        col_zero = 0

        for i in range(L_matrice):
            for j in range(L_matrice):
                if nod_curent.nod_graf.info[i][j] == 0:
                    lin_zero = i
                    col_zero = j
                    break

        global nr_euristica

        for index in range(len(dx)):

            poz_nou_lin = dx[index] + lin_zero  # Calculeaza noua pozitie(linia) a 0-ului
            poz_nou_col = dy[index] + col_zero  # Calculeaza noua pozitie(coloana) a 0-ului

            if interior(poz_nou_lin, poz_nou_col, L_matrice) is True:
                succesor = copy.deepcopy(nod_curent.nod_graf.info)  # Fac o copie a obiectul curent

                succesor[lin_zero][col_zero] = succesor[poz_nou_lin][poz_nou_col]
                succesor[poz_nou_lin][poz_nou_col] = 0

                if nr_euristica == 1:
                    lista.append((Nod(succesor, self.euristica_1(self.nod_graf.info)),
                                  1))  # Construieste un nou nod, cu noua configuratie obtinuta in urma swap-ului
                else:
                    lista.append((Nod(succesor, self.euristica_2(self.nod_graf.info)), 1))  # Am stabili ca g = 1
        return lista

    # se modifica in functie de problema
    def test_scop(self):
        return self.nod_graf.info == self.problema.nod_scop

    def __str__(self):
        parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
        return f"({self.nod_graf}, parinte={parinte}, f={self.f}, g={self.g})"


""" Algoritmul A* """


def str_info_noduri(l):
    """
    O functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = "["
    for x in l:
        sir += str(x) + "  "
    sir += "]"
    return sir


def afis_succesori_cost(l):
    """
    O functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = ""
    for (x, cost) in l:
        sir += "\nnod:  " + str(x) + ", cost arc: " + str(cost)

    return sir


def in_lista(l, nod):
    """
    lista "l" contine obiecte de tip NodParcurgere
    "nod" este de tip Nod
    """
    for i in range(len(l)):
        if l[i].nod_graf.info == nod.info:
            return l[i]
    return None


def afisare_simpla(L):
    for x in L:
        config = x.nod_graf.info
        afisare(config)


def afisare(info):
    for index in range(len(info)):
        print(info[index])
    print("\n")


def a_star():
    rad_arbore = NodParcurgere(NodParcurgere.problema.nod_start)
    open = [rad_arbore]  # open va contine elemente de tip NodParcurgere
    closed = []  # closed va contine elemente de tip NodParcurgere
    nr_pasi = 0
    gasit = False

    while len(open) > 0:  # cat timp lista nu e vida

        # print(str_info_noduri(open))  # afisam lista open
        # print(str_info_noduri(closed))
        # print("\n")

        nr_pasi += 1
        nod_curent = open.pop(0)  # scotem primul elem din open
        closed.append(nod_curent)  # adaugam in closed

        if nod_curent.test_scop() is True:  # daca nod_curent indeplineste conditia scop:
            # afisarea are loc la finalul algoritmului
            gasit = True
            break  # opresc algoritmul

        succesori = nod_curent.expandeaza()  # expandez
        for s in succesori:
            nod_nou = None
            # s[0] = nod succesor
            # s[1] = cost succesor
            if nod_curent.contine_in_drum(s[0]) is False:  # nu este continut in drum, merg mai departe in algoritm:

                if in_lista(open, s[0]) is not None:  # nod_succesor e in open

                    nod = in_lista(open, s[0])
                    g_succesor = nod_curent.g + s[1]  # adun g-ul nodului curent si costul succesorului
                    f_succesor = g_succesor + s[0].h  # adun la g_succesor h-ul nodului succesor

                    if f_succesor < nod.f:  # compar si updatez daca e cazul
                        open.remove(nod)  # scoate nodul vechi din open
                        nod.parinte = nod_curent  # seteaza noul parinte, updateaza f,g
                        nod_nou = nod
                        nod.f = f_succesor
                        nod.g = g_succesor

                elif in_lista(closed, s[0]) is not None:  # nod succesor e in closed

                    nod = in_lista(closed, s[0])
                    g_succesor = nod_curent.g + s[1]  # adun g-ul nodului curent si costul succesorului
                    f_succesor = g_succesor + s[0].h  # adun la g_succesor h-ul nodului succesor

                    if f_succesor < nod.f:  # compar f-urile, updatez in caz ca e nevoie
                        closed.remove(nod)  # scot nodul din lista closed
                        nod_nou = nod
                        nod.parinte = nod_curent  # actualizez parintele
                        nod.g = g_succesor  # actualizez g
                        nod.f = f_succesor  # actualizez f

                else:  # nod succesor nu e in niciuna
                    g_succesor = nod_curent.g + s[1]  # adun g-ul nodului curent si costul succesorului
                    nod_nou = NodParcurgere(s[0], nod_curent, g_succesor, None)

                if nod_nou:
                    # inserare in lista sortata crescator dupa f
                    # (si pentru f-uri egale descrescator dupa g)
                    i = 0
                    while i < len(open):
                        if open[i].f < nod_nou.f:
                            i += 1
                        else:
                            while i < len(open) and open[i].f == nod_nou.f and open[i].g > nod_nou.g:
                                i += 1
                            break

                    open.insert(i, nod_nou)

    print("\n------------------ Concluzie -----------------------")
    if len(open) == 0 and not gasit:
        print("Lista open e vida, nu avem drum de la nodul start la nodul scop")
    else:
        afisare_simpla(nod_curent.drum_arbore())
        print("In total au avut loc %d mutari" % (nod_curent.f))
        print("In total au fost %d pasi" % nr_pasi)


if __name__ == "__main__":
    problema = Problema(start=[[5, 8, 4], [1, 0, 6], [7, 3, 2]], scop=[[1, 2, 3], [4, 5, 6], [7, 8, 0]])

    NodParcurgere.problema = problema
    start_time = time.time()
    a_star()
    stop_time = time.time()
    print("Programul a rulat in %.15f secunde, folosind ca euristica distanta Manhattan" % (stop_time - start_time))

    nr_euristica = 2

    NodParcurgere.problema = problema
    start_time = time.time()
    a_star()
    stop_time = time.time()
    print("Programul a rulat in %.15f secunde, folosind ca euristica numarul de piese diferite" % (
                stop_time - start_time))

'''
Pentru exemplul cu euristica distanta Manhattan, programul ruleaza in ~0.45 secunde, face 231 de pasi.
Pentru exemplul cu euristica numarul de blocuri , programul ruleaza in ~1.6 secunde, face 1929 de pasi, deci aceasta
euristica este mai slaba. Principalul motiv este acela ca prima euristica ia in considerare "costul" pentru a muta
un patratel pe locul potrivit, pe cand a 2a euristica doar numara cate patrate nu sunt la locul lor.
'''

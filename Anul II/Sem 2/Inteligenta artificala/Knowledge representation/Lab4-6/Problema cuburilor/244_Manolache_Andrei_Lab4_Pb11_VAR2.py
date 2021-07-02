import copy
import time

""" definirea problemei """

# Rezolvarea problemei 1 (cuburi), VAR2. A fost denumita Pb11 intrucat am trimis varianta mea de A star
# complet numind fisierul 244_..._Pb1

nr_euristica = 1  # Variabila globala, euristica curenta


class Nod:
    def __init__(self, info, h):
        self.info = info  # Copiaza informatia
        self.h = h

    def __str__(self):
        return "({}, h={})".format(self.info, self.h)

    def __repr__(self):
        return f"({self.info}, h={self.h})"


class Problema:

    def __init__(self, start = [['a'], ['c', 'b'], ['d']], scop = [['b', 'c'], [], ['d', 'a']]):
        self.nod_start = Nod(start, float('inf'))
        self.nod_scop = scop
        self.N = len(start)  # Numarul de stive
        self.M = sum([len(stiva) for stiva in start])  # Numarul de cuburi


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

    def euristica_2(self, info):
        # Comparam continutul stivelor, cand este diferit, incrementam
        h = 0
        for index_stiva in range(self.problema.N):
            if info[index_stiva] != self.problema.nod_scop[index_stiva]:  # Compara stiva cu stiva
                h += 1
        return h

    def euristica_1(self, info):
        h = 0
        # Comparam continutul stivelor (fiecare cub), cand este diferit, incrementam
        for index_stiva in range(self.problema.N):

            stiva_curenta_info = info[index_stiva]
            stiva_curenta_configuratie_finala = self.problema.nod_scop[index_stiva]  # configuratie_finala[index_stiva]

            len_stiva_curenta_info = len(stiva_curenta_info)
            len_stiva_configuratie_finala = len(stiva_curenta_configuratie_finala)

            min_len = min(len_stiva_configuratie_finala,
                          len_stiva_curenta_info)  # Minimul inaltimilor celor 2 stive

            for indx in range(min_len):
                if stiva_curenta_info[indx] != stiva_curenta_configuratie_finala[indx]:  # Daca am caractere diferite, atunci incrementez
                    h += 1

            if min_len == len_stiva_configuratie_finala:  # Daca stiva din configuratia finala e mai scurta, adaugam cuburile din stiva curenta care nu au fost comparate (sigur nu sunt la locul lor)
                h += (len_stiva_configuratie_finala + len_stiva_curenta_info - 2 * min_len)

        return h

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
            if nod_curent.nod_graf.info == nod.info:  # Daca au continutul egal
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
        global nr_euristica

        for index_stiva_de_unde_se_muta, stiva in enumerate(nod_curent.nod_graf.info):
            if len(stiva) > 0:  # Stiva e nevida, voi putea lua un cub din varful acesteia
                cub_mutat = stiva[-1]
                for index_stiva_unde_se_muta in range(len(nod_curent.nod_graf.info)):
                    if index_stiva_de_unde_se_muta != index_stiva_unde_se_muta:  # Sa nu mut in aceeasi stiva

                        succesor = copy.deepcopy(nod_curent.nod_graf.info)  # Fac o copie a obiectul curent
                        succesor[index_stiva_unde_se_muta].append(cub_mutat)  # Adaug cubul
                        succesor[index_stiva_de_unde_se_muta].pop()  # Sterg cubul

                        if nr_euristica == 1:
                            lista.append((Nod(succesor, self.euristica_1(self.nod_graf.info)), 1))  # Costul este 1
                        else:
                            lista.append((Nod(succesor, self.euristica_2(self.nod_graf.info)), 1))  # Costul este 1
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
    for nr_stiva in range(len(info)):
        print(info[nr_stiva])
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

                if in_lista(closed, s[0]) is not None:  # nod_succesor e in closed
                    nod = in_lista(closed, s[0])
                    g_succesor = nod_curent.g + s[1]  # adun g-ul nodului curent si costul succesorului
                    f_succesor = g_succesor + s[0].h  # adun la g_succesor h-ul nodului succesor

                    if f_succesor < nod.f:  # compar f-urile, updatez in caz ca e nevoie
                        closed.remove(nod)  # scot nodul din lista closed
                        nod_nou = nod
                        nod.parinte = nod_curent  # actualizez parintele
                        nod.g = g_succesor  # actualizez g
                        nod.f = f_succesor  # actualizez f

                elif in_lista(open, s[0]) is not None:  # nod succesor e in open

                    nod = in_lista(open, s[0])
                    g_succesor = nod_curent.g + s[1]  # adun g-ul nodului curent si costul succesorului
                    f_succesor = g_succesor + s[0].h  # adun la g_succesor h-ul nodului succesor

                    if f_succesor < nod.f:  # compar si updatez daca e cazul
                        open.remove(nod)  # scoate nodul vechi din open
                        nod.parinte = nod_curent  # seteaza noul parinte, updateaza f,g
                        nod_nou = nod
                        nod.f = f_succesor
                        nod.g = g_succesor

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

    problema = Problema()#start=[['b', 'c'], ['d'], ['a', 'e']], scop=[['d', 'a'], [], ['b', 'c', 'e', ]])

    NodParcurgere.problema = problema
    start_time = time.time()
    a_star()
    stop_time = time.time()
    print("Programul a rulat in %.15f secunde, folosind ca euristica numarul de cuburi diferite" % (
                stop_time - start_time))

    nr_euristica = 2  # Schimbam euristica

    NodParcurgere.problema = problema
    start_time = time.time()
    a_star()
    stop_time = time.time()
    print("Programul a rulat in %.15f secunde, folosind ca euristica numarul de stive diferite" % (
                stop_time - start_time))
'''
Pentru exemplul cu euristica numarul de cuburi diferite, programul ruleaza in ~0.25 secunde, face 484 de pasi. 
Pentru exemplul cu euristica numarul de stive diferite, programul ruleaza in ~2.3 secunde, face 1980 de pasi, deci aceasta
euristica e mai slaba decat cealalta. Un motiv ar fi faptul ca daca o stiva e diferita in totalitate fata de 
configuratia scop, pe aceasta euristica se aduna doar 1, pe cand la celalata euristica, sunt adunate numarul de cuburi
care difera prin pozitie si continut, fiind mai apropiata de realitate.
Deci euristica mai "buna" este cea in care se compara cuburile, si nu stivele (ca intreg)
'''

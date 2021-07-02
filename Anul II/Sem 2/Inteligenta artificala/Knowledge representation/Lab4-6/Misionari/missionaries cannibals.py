import copy

""" definirea problemei """

# Rezolvarea problemei 3 (misionaro), VAR2.

class Nod:
    def __init__(self, info, h):
        self.info = info  # Copiaza informatia
        self.h = h

    def __str__(self):
        return "({}, h={})".format(self.info, self.h)

    def __repr__(self):
        return f"({self.info}, h={self.h})"


class Problema:

    def __init__(self, N = 3, M = 2, mal = 'EST'):

        nod_E = [0, 0, N, N, 'EST']
        nod_V = [N, N, 0, 0, 'VEST']

        start = nod_E if mal == 'EST' else nod_V
        scop = nod_V if mal == 'EST' else nod_E

        self.N = N
        self.M = M

        self.nod_start = Nod(start, float('inf'))
        self.nod_scop = scop


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
        ### TO DO ... DONE
        nod_c = self
        while nod_c is not None:
            if nod.info == nod_c.nod_graf.info:
                return True
            nod_c = nod_c.parinte
        return False

    def euristica(self, info):
        return (info[2] + info[3]) // (self.problema.M - 1)


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

        if nod_curent.nod_graf.info[4] == 'EST':  # In prezent, barca este pe malul de EST
            nr_canibali_start = nod_curent.nod_graf.info[2]
            nr_misionari_start = nod_curent.nod_graf.info[3]
            nr_canibali_final = nod_curent.nod_graf.info[0]
            nr_misionari_final = nod_curent.nod_graf.info[1]
        else:                                     # In prezent, barca este pe malul din VEST
            nr_canibali_start = nod_curent.nod_graf.info[0]
            nr_misionari_start = nod_curent.nod_graf.info[1]
            nr_canibali_final = nod_curent.nod_graf.info[2]
            nr_misionari_final = nod_curent.nod_graf.info[3]

        nr_misionari = 0  # Nr misionari care vor pleca cu barca
        nr_canibali = 0  # Nr canibali care vor pleca cu barca

        while nr_misionari <= nr_misionari_start:
            while nr_canibali <= nr_canibali_start:
                if 0 < nr_misionari + nr_canibali <= self.problema.M:  # Barca sa nu fie goala si sa nu ii fie depasit numarul de locuri
                    if nr_misionari == 0 or nr_misionari >= nr_canibali:  # Sa nu se manance in barca
                        if nr_canibali_start - nr_canibali <= nr_misionari_start - nr_misionari or nr_misionari_start - nr_misionari == 0:  # Daca pe malul din care am plecat, ori nu mai am misionari, ori numarul acestora e cel putin egal cu cel al canibalilor
                            if nr_misionari_final + nr_misionari == 0 or nr_misionari_final + nr_misionari >= nr_canibali + nr_canibali_final:  # Pe malul in care ajung sa am aceeasi conditie
                                succesor = copy.deepcopy(nod_curent.nod_graf.info)  # Fac o copie a obiectul curent

                                # Updatez numarul de misionari / canibali
                                if nod_curent.nod_graf.info[4] == 'EST':
                                    succesor[4] = 'VEST'
                                    succesor[0] += nr_canibali
                                    succesor[1] += nr_misionari
                                    succesor[2] -= nr_canibali
                                    succesor[3] -= nr_misionari
                                else:
                                    succesor[4] = 'EST'
                                    succesor[0] -= nr_canibali
                                    succesor[1] -= nr_misionari
                                    succesor[2] += nr_canibali
                                    succesor[3] += nr_misionari

                                lista.append((Nod(succesor, self.euristica(self.nod_graf.info)), 1))  # Costul muchiei e 1

                nr_canibali += 1  # Incrementam
            nr_canibali = 0  # Resetam contorul
            nr_misionari += 1  # Incrementam
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

def afisare_simpla(L):
    for x in L:
        config = x.nod_graf.info
        afisare(config)


def afisare(info):
    print("Pe malul de EST sunt %d misionari si %d canibali\n"
          "Pe malul de VEST sunt %d misionari si %d canibali\n"
          "Barca se afla pe malul de %s \n\n" % (info[3], info[2], info[1], info[0], info[4]))

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


def a_star():
    rad_arbore = NodParcurgere(NodParcurgere.problema.nod_start)
    open = [rad_arbore]  # open va contine elemente de tip NodParcurgere
    closed = []  # closed va contine elemente de tip NodParcurgere
    gasit = False

    while len(open) > 0:  # cat timp lista nu e vida

        # print(str_info_noduri(open))  # afisam lista open
        # print(str_info_noduri(closed))
        # print("\n")

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


if __name__ == "__main__":
    problema = Problema(N = 5, M =3, mal = 'EST')
    NodParcurgere.problema = problema
    a_star()
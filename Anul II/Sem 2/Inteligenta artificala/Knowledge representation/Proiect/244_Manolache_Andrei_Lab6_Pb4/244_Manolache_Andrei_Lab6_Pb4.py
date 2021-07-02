# Manolache Andrei
# Grupa 244
# Laborator 6 Problema 4 - Transmiterea mesajului

import time
import math
import os

EURISTICA = -1  # Numarul euristicii alese

def citire(file):
    """Functie care citeste datele din fisier.
       Returneaza matricea cu numele elevilor, asezati in banci, lista de perechi cu elevii certati, coordonatele de
       start si cele scop.
       Argumente:
       file - numele fisierului din care are loc citirea"""

    fopen = open(file, 'r', encoding="utf-8")
    matrice_nume = []
    suparati = []
    nr_randuri = 0

    if not fopen:
        print("Fisierul %s nu exista!" % file)
    else:
        matrix = []
        for line in fopen:
            nume = line.split()
            matrix.append(nume)

        start = matrix[len(matrix) - 1][1]  # Numele elevului care trimite mesjaul
        stop = matrix[len(matrix) - 1][3]  # Numele elevului care primeste mesajul

        for line in matrix:
            if line[0] == 'suparati':
                break
            else:
                nr_randuri += 1
                matrice_nume.append(line)

        for lin in range(len(matrice_nume)):
            for col in range(len(matrice_nume[0])):
                if matrice_nume[lin][col] == start:
                    start = (lin, col)  # Retine coordonatele elevului care transmite mesajul
                if matrice_nume[lin][col] == stop:
                    stop = (lin, col)  # Retine coordonatele elevului care trebuie sa transmita mesajul

        for index in range(nr_randuri + 1, len(matrix) - 1, 1):  # Construieste lista de perechi de elevi certati
            suparati.append((matrix[index][0], matrix[index][1]))
            suparati.append((matrix[index][1], matrix[index][0]))

        fopen.close()
        return matrice_nume, suparati, start, stop


class Nod:
    """Clasa Nod care tine informatia unui nod(coordonatele elevului) si costul estimat de euristica"""
    def __init__(self, info, h):
        self.info = info  # Coordonatele curente ale mesajului
        self.h = h  # Euristica


class Problema:
    """Clasa problema, defineste datele problemei. Are campurile:
       matrice_nume - numele elevilor asezati in clasa, pe banci
       latime - numarul de coloane (in problema sunt 6)
       lungime - adancimea clasei, numarul de randuri
       suparati - lista de perechi cu elevii certati
       start - coordonatele elevului care transmite mesajul
       scop - cordonatele elevlui care primeste mesajul
       nod_start - obiect de tip Nod, starea initiala
       locuri_libere - lista de perechi(coordonatele) cu bancile libere"""

    def __init__(self, matrice_nume, suparati, start, stop):
        self.matrice_nume = matrice_nume  # Matricea cu elevii
        self.latime = len(matrice_nume[0])  # Numarul de coloane de banci, in problema sunt 6
        self.lungime = len(matrice_nume)  # Numarul de randuri
        self.suparati = suparati  # Vector cu perechile de elevi certati
        self.start = start  # Coordonatele elevului care trimite mesajul
        self.scop = stop  # Coordonatele elevului la care trebuie sa ajunga mesajul
        self.nod_start = Nod(start, float('inf'))  # Memoreaza starea initiala, memorand coordonatele de unde pleaca mesajul
        self.locuri_libere = []  # Vector de coordonate care memoreaza bancile libere

        for i in range(self.lungime):
            for j in range(self.latime):
                if matrice_nume[i][j] == 'liber':
                    self.locuri_libere.append((i, j))


    def interior(self, linie, coloana):
        """Functie care verifica daca coordonatele pozitiei curente (linie,coloana) se afla in interioriul matricei ce
           reprezinta clasa"""
        return 0 <= linie < self.lungime and 0 <= coloana < self.latime

class NodParcurgere:
    """
    O clasa care cuprinde informatiile asociate unui nod din listele open/closed
    Cuprinde o referinta catre nodul in sine (din graf)
    dar are ca proprietati si valorile specifice algoritmului A* (f si g).
    Se presupune ca h este proprietate a nodului din graf
    """

    problema = None  # atribut al clasei

    def __init__(self, nod_graf, parinte=None, g=0, f=None):
        """
        Constructorul. Argumente:
        nod_graf - obiect de tip Nod
        parinte - obiect de tip Nod, "parintele" obiectului
        g - costul g
        f - costul f
        """
        self.nod_graf = nod_graf
        self.parinte = parinte
        self.g = g
        if f is None:
            self.f = self.g + self.nod_graf.h
        else:
            self.f = f


    def euristica(self, info):
        """Functie care returneaza costul estimat de euristica aleasa. Argumente:
           info - informatia retinuta de nod ( coordonatele curente )
        """

        global EURISTICA

        if EURISTICA == 1:
            return self.euristica_1(info)
        elif EURISTICA == 2:
            return self.euristica_2(info)
        else:
            return self.euristica_3(info)


    def euristica_1(self, info):  # Distanta Manhattan
        """Returneaza distanta Manhattan de la pozitia curenta la pozitia scop.
           Ea reprezinta numarul de banci prin care trebuie sa treaca mesajul pentru a ajunge la destinatie. Se foloseste
           atunci cand directiile de deplasare sunt sus, jos, stanga sau dreapta. Pentru a ajunge mesajul de la expeditor
           la destinatar, trebuie sa mearga mereu prin linie dreapta(deci ori pe linie sau coloana). Intrucat pe acest
           principiu se bazeaza si distanta Manhattan (in ambele cazuri este exclusa transmiterea pe diagonala), dar in
           problema pot aparea "obstacole"(ex banca libera prin care nu poate trece niciun mesaj sau 2 colegi certati),
           drumul prin care este transmis mesajul este putin deviat, deci in mod clar euristica subestimeaza costul real
           de trimitere al mesajului de la expeditor la destinatar"""

        return abs(self.problema.scop[0] - self.nod_graf.info[0]) + abs(self.problema.scop[1] - self.nod_graf.info[1])


    def euristica_2(self, info):
        """Returneaza distanta euclidiana de la pozitia curenta la pozitia scop. Aceasta euristica este admisibila
           intrucat calculeaza distanta in cazul in care mesajul s-ar putea trimite pe directia elev curent ->
           elev destinatie, (nu ar merge doar pe verticale si orizontala), astfel subestimand costul distantei Manhattan
           care la randul ei subestimeaza costul real al trimiterii mesajului. """

        return math.sqrt((self.problema.scop[0] - self.nod_graf.info[0]) ** 2 + (self.problema.scop[1] - self.nod_graf.info[1]) ** 2)


    def euristica_3(self, info):
       """Functie care estimeaza costul configuratiei curente, obligand mesajul sa treaca prin ultimul rand de banci
          al clasei, pentru a fi siguri ca a putut avea loc trecerea de pe o coloana pe alta. Euristica nu este
          admisibila intrucat supraestimeaza costul(De exemplu daca un elev trebuie sa-i transmita mesajul colegului sau
          de banca, costul real ar fi de 1, dar euristica ar returna (adancime_clasa - linie_elev_sursa) + 1 +
           (adancime_clasa- linie_elev_dest)."""

       return abs(self.nod_graf.info[0] - self.problema.lungime - 1) + abs(self.nod_graf.info[1] - self.problema.scop[1]) + abs(self.problema.lungime - 1 - self.problema.scop[0])


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

        nod_curent = self
        while nod_curent is not None:  # Cat timp nu am ajuns la radacina
            if nod.info == nod_curent.nod_graf.info:  # Daca au continutul egal
                return True
            else:
                nod_curent = nod_curent.parinte  # Merg mai departe
        return False


    def expandeaza(self):
        """
        Pentru nodul curent (self) parinte, trebuie sa gasiti toti succesorii (fiii)
        si sa returnati o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
        sau lista vida, daca nu exista niciunul.
        (Fiecare tuplu contine un obiect de tip Nod si un numar.)
        Pentru fiecare elev se calculeaza coordonatele urmatorului coleg care ar primi mesajul, se verifica daca acesta
        inca se afla in perimetrul clasei, daca cei 2 elevi nu sunt certati si directia de transmitere a mesajului este
        valida (doar in penultimele randuri se poate trimite un mesaj peste spatiul liber)
        """

        lista = []

        dx = [-1, 0, 1, 0]  # Vector deplasare pozitii pe linii
        dy = [0, -1, 0, 1]  # Vector deplasare pozitii pe coloane

        poz_lin = self.nod_graf.info[0]  # Pozitia actuala (linia)
        poz_col = self.nod_graf.info[1]  # Pozitia actuala (coloana)
        elev_curent = self.problema.matrice_nume[poz_lin][poz_col]  # Numele elevului curent unde se afla mesajul

        for index in range(len(dx)):

            poz_nou_lin = dx[index] + poz_lin  # Calculeaza noua pozitie(linia) unde ar putea ajunge mesajul
            poz_nou_col = dy[index] + poz_col  # Calculeaza noua pozitie(coloana) unde ar putea ajunge mesajul

            if self.problema.interior(poz_nou_lin, poz_nou_col) is True:  # Mesajul nu iese din perimetrul clasei
                urmatorul_elev = self.problema.matrice_nume[poz_nou_lin][poz_nou_col]  # Elevul care primeste mesajul
                if (poz_nou_lin, poz_nou_col) not in self.problema.locuri_libere:  # Mesajul ajunge la un elev si nu la o banca libera
                    if (elev_curent, urmatorul_elev) not in self.problema.suparati:  # Cei doi elevi nu sunt certati

                        if poz_lin <= self.problema.lungime - 3:  # Cazurile in care cel care trimite mesajul nu se afla in penultimele banci
                            if poz_col % 2 == 0:  # Cel care trimite mesajul se afla in banca stanga(din coloana de 2 banci respectiva)
                                if dy[index] != -1:  # Verific sa pot da mesajul doar in fata, spate sau in dreapta
                                    succesor = (poz_nou_lin, poz_nou_col)
                                    lista.append( (Nod(succesor, self.euristica(self.nod_graf.info)), 1) )
                            else:
                                if dy[index] != 1:  # Verific sa pot da mesajul doar in fata, spate sau in stanga
                                    succesor = (poz_nou_lin, poz_nou_col)
                                    lista.append((Nod(succesor, self.euristica(self.nod_graf.info)), 1))

                        else:  # Cel care transmite mesajul se afla in ultimele banci, poate da in toate directiile
                            succesor = (poz_nou_lin, poz_nou_col)
                            lista.append((Nod(succesor, self.euristica(self.nod_graf.info)), 1))
        return lista


    def test_scop(self):
        """Functia testeaza daca s-a ajuns la configuratia finala, adica mesajul a ajuns la elevul care trebuie.
           Compara coordonatele"""
        if self.nod_graf.info == self.problema.scop:
            return True
        return False


def in_lista(l, nod):
    """
    Verifica daca un nod se afla intr-o lista, comparand informatia (info)
    lista "l" contine obiecte de tip NodParcurgere
    "nod" este de tip Nod
    """
    for i in range(len(l)):
        if l[i].nod_graf.info == nod.info:
            return l[i]
    return None


def afisare(L, output_file):
    """Functia de afisare a datelor. Compara coordonatele curente cu cele ale nodului parinte, in functie de asta
       stabileste semnul(>, >>, ^, <, <<, v). Argumente:
       L - lista de noduri (drumul de la radacina la nodul scop)
       output_file - fisierul in care are loc afisarea"""

    sir = ""
    for nod in L:
        if nod.parinte is None:  # Nodul de start
            sir = nod.problema.matrice_nume[nod.nod_graf.info[0]][nod.nod_graf.info[1]] + " "  # Initializeaza sirul
        else:
            # Preia coordonatele curente si ale parinteului
            coordonate_curente = nod.nod_graf.info
            coodonate_parinte = nod.parinte.nod_graf.info

            lin_curent = coordonate_curente[0]
            col_curent = coordonate_curente[1]

            lin_parinte = coodonate_parinte[0]
            col_parinte = coodonate_parinte[1]

            if lin_curent != lin_parinte:  # Mesajul a fost trimis pe verticala
                if lin_curent + 1 == lin_parinte:  # Mesajul a fost trimis "in sus"
                    directie = "^"
                else:
                    directie = "v"  # Mesajul este trimis in "jos"
            else:
                if col_curent == col_parinte + 1:  # Mesajul a fost trimis in dreapta
                    if col_curent % 2 == 0:  # Daca mesajul a fost transmis peste spatiul gol dintre coloane
                        directie = ">>"
                    else:
                        directie = ">"  # Mesajul este trimis unui coleg de banca
                else:  # Mesajul a fost trimis in stanga
                    if col_curent % 2 == 1:  # Daca mesajul a fost transmis peste spatiul gol dintre coloane
                        directie = "<<"
                    else:
                        directie = "<"  # Mesajul este transmis colegului

            sir = sir + " " + directie + " " + nod.problema.matrice_nume[lin_curent][col_curent]
    output_file.write(sir + "\n")


def a_star(output_file):
    """Functia de a_star. Parametru:
       output_file - fisierul in care are loc afisarea concluziei"""

    rad_arbore = NodParcurgere(NodParcurgere.problema.nod_start)
    open = [rad_arbore]  # open va contine elemente de tip NodParcurgere
    closed = []  # closed va contine elemente de tip NodParcurgere
    gasit = False

    while len(open) > 0:  # cat timp lista nu e vida

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

    output_file.write("\n------------------ Concluzie -----------------------\n")
    if len(open) == 0 and not gasit:
        output_file.write("Lista open e vida, nu avem drum de la nodul start la nodul scop\n")
    else:
        afisare(nod_curent.drum_arbore(), output_file)


if __name__ == "__main__":

    input_names = ['input_1.txt', 'input_2.txt', 'input_3.txt', 'input_4.txt']
    output_names = ['output_1.txt', 'output_2.txt', 'output_3.txt', 'output_4.txt']

    # input_1.txt - nu are solutii
    # input_2.txt - starea initiala = starea finala
    # input_3.txt - drum de lungime minima 5, euristica inadmisibila nu gaseste drumul minim
    # input_4.txt - drum de lungime minima mai mare de 5

    for output_name in output_names:  # Daca fisierele de output exista deja, le sterge pentru a afisa noile concluzii in fisier
        if os.path.exists(output_name):
            os.remove(output_name)

    for i in range(len(input_names)):  # Pentru fiecare fisier
        input_name = input_names[i]
        output_name = output_names[i]
        file_write = open(output_name, 'a')  # Deschide fisierul de output in modul append

        matrice_nume, suparati, coord_start, coord_stop = citire(input_name)  # Are loc citirea
        problema = Problema(matrice_nume, suparati, coord_start, coord_stop)  # Se construieste un obiect de tip Problema cu datele citite din fisier

        for EURISTICA in range(1, 4, 1):  # Pentru fiecare din cele 3 euristici
            NodParcurgere.problema = problema  # Initializeaza campul problema
            start_time = time.time()
            a_star(file_write)  # Incepe algoritmul a_star
            stop_time = time.time()
            file_write.write("Pentru euristica %d, timpul total a fost de %.15f secunde pana s-a ajung la concluzie\n\n" % ( EURISTICA, stop_time - start_time))
        file_write.close()
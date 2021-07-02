# Manolache Andrei
# Grupa 244
# Lab 9 Pb 5 (Mancala)

import time
import copy
import pygame, sys

interfata_grafica = False
functie_aproximare = 2


def afisari_final(nr_miscari_jucator, nr_miscari_calculator, timp_start):
    """Functie care face o parte din afisarile finale"""
    timp_stop_joc = time.time()
    print("Timpul total de joc a fost de %d secunde" % (timp_stop_joc - timp_start))
    print("Jucatorul a avut %d miscari" % nr_miscari_jucator)
    print("Calculatorul a avut %d miscari" % nr_miscari_calculator)


def deseneaza_grid(display, configuratie):
    """Functie care deseneaza interfata grafica. Parametri:
       display - obiect de tip pygame.display
       configuratie - configuratia curenta
    """

    YELLOW = (255, 255, 0)
    WHITE = (255, 255, 255)
    BLACK = (0, 0, 0)
    w_gr = 50
    display.fill(BLACK)
    fontObject = pygame.font.Font('freesansbold.ttf', 20)

    textSurfaceCalculator = fontObject.render('Calculator: ', True, WHITE)
    textCalculator = textSurfaceCalculator.get_rect()
    textCalculator.topleft = (5, 8)

    scorSurfaceCalculator = fontObject.render(str(configuratie.scor_calculator), True, BLACK, YELLOW)
    scorCalculator = scorSurfaceCalculator.get_rect()
    scorCalculator.topleft = (120, 8)

    textSurfaceJucator = fontObject.render('Jucator: ', True, WHITE)
    textJucator = textSurfaceJucator.get_rect()
    textJucator.topleft = (550, 8)

    scorSurfaceJucator = fontObject.render(str(configuratie.scor_jucator), True, BLACK, YELLOW)
    scorJucator = scorSurfaceJucator.get_rect()
    scorJucator.topleft = (635, 8)

    display.blit(textSurfaceCalculator, textCalculator)
    display.blit(scorSurfaceCalculator, scorCalculator)
    display.blit(textSurfaceJucator, textJucator)
    display.blit(scorSurfaceJucator, scorJucator)

    drt = []

    margine_stanga = 30
    margine_sus_1 = 60
    margine_sus_2 = margine_sus_1 + 75
    fontPiese = pygame.font.Font('freesansbold.ttf', 54)

    # deseneaza piesele calculatorului
    for i in range(Joc.NR_HOLES):
        scorSurface = fontPiese.render(str(configuratie.holes_calculator[i]), True, BLACK, YELLOW)
        scor = scorSurface.get_rect()
        if configuratie.holes_calculator[i] > 9:
            scor.topleft = (margine_stanga + (Joc.NR_HOLES - i) * (w_gr + 24), margine_sus_1)
        else:
            scor.topleft = (margine_stanga + (Joc.NR_HOLES - i) * (w_gr + 30), margine_sus_1)
        display.blit(scorSurface, scor)

    # deseneaza piesele jucatorului
    for i in range(Joc.NR_HOLES):
        scorSurface = fontPiese.render(str(configuratie.holes_jucator[i]), True, BLACK, YELLOW)
        scor = scorSurface.get_rect()
        # if configuratie.holes_jucator[i] > 9:  # are 2 cifre
        scor.topleft = (margine_stanga + (i + 1) * (w_gr + 30), margine_sus_2)
        display.blit(scorSurface, scor)
        drt.append(scor)

    pygame.display.update()
    return drt


class Joc:
    """Clasa care defineste jocul. Se va schimba de la un joc la altul."""
    NR_HOLES = 6
    SIMBOLURI_JUC = ['X', '0']
    JMIN = None
    JMAX = None

    def update(self, poz, holes_eu, holes_adversar, scor_eu):
        """Functie care face update la piesele jucatorilor, stiind jucatorul care a facut ultima mutare si pozitia
           dupa care a inceput"""
        nr = holes_eu[poz]  # Numarul de piese care vor fi "imprastiate"
        current_list = holes_eu  # Lista curenta pe care se lucreaza
        current_list[poz] = 0
        randul_meu = False

        while nr != 0:
            poz += 1
            nr -= 1
            if poz == self.NR_HOLES:
                if current_list is holes_eu:
                    scor_eu += 1
                    poz = -1
                    current_list = holes_adversar
                    randul_meu = True
                elif current_list is holes_adversar:
                    poz = 0
                    current_list = holes_eu
                    current_list[poz] += 1
                    randul_meu = False
            else:
                current_list[poz] += 1
                randul_meu = False

        if current_list is holes_eu:  # Daca la ultima miscare am ajuns pe o pozitie goala si pe un hole de-al meu, atunci piesele jucatorului de pe pozitia simetrica vor fi adaugate la scorul meu
            if current_list[poz] == 1:
                scor_eu += holes_adversar[self.NR_HOLES - poz - 1] + 1
                holes_eu[poz] = 0
                holes_adversar[self.NR_HOLES - poz - 1] = 0

        return scor_eu, randul_meu

    def __init__(self, info=None):

        if info is None:  # In program, vom initializa un obiect de tipul Joc ori cu niciun argument, ori cu toate. Daca holes_jucator = None, atunci toate sunt None, deci initalizam jocul cu configuratia initiala
            self.holes_jucator = [4 for index in range(self.NR_HOLES)]
            self.holes_calculator = [4 for index in range(self.NR_HOLES)]
            self.scor_jucator = 0
            self.scor_calculator = 0
            self.randul_meu = False
            self.j_curent = Joc.JMAX
        else:
            self.holes_jucator = info[0]
            self.scor_jucator = info[1]
            self.holes_calculator = info[2]
            self.scor_calculator = info[3]
            self.randul_meu = info[4]
            self.j_curent = Joc.JMAX





    def calc_scor_3(self, jucator):
        """Functie de estimare a scorului. La scorul curent, aduna mai multe unitati pentru fiecare hole care ii permite
         inca o mutare.  """
        if jucator == Joc.JMIN:
            s = self.scor_jucator
            for index in range(self.NR_HOLES):
                if self.holes_jucator[index] + index == self.NR_HOLES:
                    s += 1
                elif (self.holes_jucator[index] - self.NR_HOLES + index) % (2 * self.NR_HOLES + 1) == 0:
                    s += 2
            return s
        else:
            s = self.scor_calculator
            for index in range(self.NR_HOLES):
                if self.holes_calculator[index] + index == self.NR_HOLES:
                    s += 1
                elif (self.holes_calculator[index] - self.NR_HOLES + index) % (2 * self.NR_HOLES + 1) == 0:
                    s += 2
            return s








    def calc_scor_2(self, jucator):
        """Functie de estimare a scorului. Daca jucatorul care trebuie sa-i fie estimat scorul este cel curent, verifica
           daca este randul acestuia din nou. Daca da, atunci adauga o unitate (sau 2) la scorul curent in cazul in care
           cand face o mutare de pe un anumit hole, aceasta s-ar termina in pocketul lui, deci ar avea o mutare in plus
           , altfel returneaza scorul curent"""

        if jucator == self.j_curent:
            if jucator == Joc.JMAX:
                s = self.scor_calculator
                for index in range(self.NR_HOLES):
                    if self.holes_calculator[index] + index == self.NR_HOLES:
                        return s + 1
                    elif (self.holes_calculator[index] - self.NR_HOLES + index) % (2 * self.NR_HOLES + 1) == 0:
                        return s + 2
                return s
            else:
                s = self.scor_jucator
                for index in range(self.NR_HOLES):
                    if self.holes_jucator[index] + index == self.NR_HOLES:
                        return s + 1
                    elif (self.holes_jucator[index] - self.NR_HOLES + index) % (2 * self.NR_HOLES + 1) == 0:
                        return s + 2
                return s
        elif jucator == Joc.JMAX:
            return self.scor_calculator
        else:
            return self.scor_jucator


    def calc_scor_1(self, jucator):
        """Functie de estimare a scorului """
        if jucator == Joc.JMIN:
            return self.scor_jucator
        else:
            return self.scor_calculator



    def numar_mutari_posibile(self, jucator):
        """Functie care returneaza numarul de miscari posibile pentru un anumit jucator"""
        nr = 0
        if jucator == self.JMAX:  # Calculatorul
            for elem in self.holes_calculator:
                if elem != 0:
                    nr += 1
        else:
            for elem in self.holes_jucator:
                if elem != 0:
                    nr += 1
        return nr

    def final(self):
        """Functie care returneaza simbolul jucatorului castigator, "remiza" sau False (depinde de caz). Verifica
           daca unul dintre jucatori nu mai poate face nicio mutare. In caz afirmativ, jocul este gata, insumeaza
            piesele fiecarui jucator, le aduna la scorul curent si obtine simbolul jucatorului castigator (daca nu este
            remiza)"""
        jmax_mutari_posibile = self.numar_mutari_posibile(Joc.JMAX)
        jmin_mutari_posibile = self.numar_mutari_posibile(Joc.JMIN)

        jmin_scor = self.scor_jucator
        jmax_scor = self.scor_calculator

        if jmin_mutari_posibile == 0 or jmax_mutari_posibile == 0:  # Daca unul din jucatori nu mai poate face mutari

            jmax_scor += sum(self.holes_calculator)  # Scorul final pentru calculator
            jmin_scor += sum(self.holes_jucator)  # Scorul final pentru jucator

            if jmax_scor > jmin_scor:
                return Joc.JMAX
            elif jmax_scor == jmin_scor:
                return "remiza"
            else:
                return Joc.JMIN
        else:
            return False

    def mutari_joc(self, jucator):

        """Functie care genereaza toate mutarile posibile. Pentru fiecare hole al jucatorului <<jucator>>, verifica daca
        este cel putin o  piesa. In caz afirmativ, are loc mutarea, se face update la configuratia respectiva (se
        updateaza toate hole-urile jucatorului curent, dar si ale adversarului. Se incrementeaza scorul jucatorului
        (daca este cazul)"""

        global interfata_grafica
        if interfata_grafica:
            pygame.event.get()
        l_mutari = []

        if jucator == Joc.JMAX:
            for poz in range(self.NR_HOLES):
                if self.holes_calculator[
                    poz] != 0:  # Daca hole-ul respectiv nu e gol, poate avea o mutare de pe pozitia aceea

                    # Facem copii la configuratiile curente
                    holes_calculator_copy = copy.deepcopy(self.holes_calculator)
                    holes_jucator_copy = copy.deepcopy(self.holes_jucator)
                    scor_jucator_copy = self.scor_jucator
                    scor_calculator_copy = self.scor_calculator

                    scor_calculator_copy, randul_meu = self.update(poz, holes_calculator_copy, holes_jucator_copy,
                                                                   scor_calculator_copy)  # Are loc update-ul configuratiei
                    l_mutari.append(Joc((holes_jucator_copy, scor_jucator_copy, holes_calculator_copy,
                                         scor_calculator_copy, randul_meu)))  # Se adauga urmatoarea mutare posibila
        else:
            for poz in range(self.NR_HOLES):
                if self.holes_jucator[
                    poz] != 0:  # Daca hole-ul respectiv nu e gol, poate avea o mutare de pe pozitia aceea

                    # Facem copii la configuratiile curente
                    holes_calculator_copy = copy.deepcopy(self.holes_calculator)
                    holes_jucator_copy = copy.deepcopy(self.holes_jucator)
                    scor_jucator_copy = self.scor_jucator
                    scor_calculator_copy = self.scor_calculator

                    scor_jucator_copy, randul_meu = self.update(poz, holes_jucator_copy, holes_calculator_copy,
                                                                scor_jucator_copy)  # Are loc update-ul configuratiei
                    l_mutari.append(Joc((holes_jucator_copy, scor_jucator_copy, holes_calculator_copy,
                                         scor_calculator_copy, randul_meu)))  # Se adauga urmatoarea mutare posibila
        return l_mutari

    def estimeaza_scor(self, adancime):
        """Functia de estimare a scorului"""
        t_final = self.final()
        if t_final == Joc.JMAX:
            return (999 + adancime)
        elif t_final == Joc.JMIN:
            return (-999 - adancime)
        elif t_final == 'remiza':
            return 0
        else:
            global functie_aproximare
            if functie_aproximare == 1:
                return self.calc_scor_1(Joc.JMAX) - self.calc_scor_1(Joc.JMIN)
            elif functie_aproximare == 2:
                return self.calc_scor_2(Joc.JMAX) - self.calc_scor_2(Joc.JMIN)
            elif functie_aproximare == 3:
                return self.calc_scor_3(Joc.JMAX) - self.calc_scor_3(Joc.JMIN)

    def __str__(self):

        calculator = ""
        jucator = ""

        for elem in reversed(self.holes_calculator):
            calculator += (str(elem) + " ")

        for elem in self.holes_jucator:
            jucator += (str(elem) + " ")

        sir = "Coloana:        "
        if self.scor_calculator > 9:
            sir += " "
        sir += "0 1 2 3 4 5" + "\n" + "-----------------------------------------" + "\n"

        sir += "Calculatorul:" + str(self.scor_calculator) + "  " + calculator + "  Jucatorul:" + str(
            self.scor_jucator) + "\n                "
        if self.scor_calculator > 9:  # Daca are mai multe de 2 cifre scorul calculatorului, adaugam un spatiu in plus pentru alinierea datelor
            sir += " "
        sir += (jucator + "\n")
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

    def __init__(self, configuratie, j_curent, adancime, parinte=None, scor=None):

        self.configuratie = configuratie  # un obiect de tip Joc, are campuri holes_jucator, holes_calculator, scor_jucator, scor_calculator
        self.j_curent = j_curent  # simbolul jucatorului curent
        self.configuratie.j_curent = j_curent

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
        l_mutari = self.configuratie.mutari_joc(self.j_curent)
        juc_opus = self.jucator_opus()
        l_stari_mutari = []

        # Verifica daca in continuare este randul aceluiasi jucator. Daca da, la urmatoarea "stare", nu se modifica
        # jucatorul curent

        for mutare in l_mutari:
            if mutare.randul_meu:
                l_stari_mutari.append(Stare(mutare, self.j_curent, self.adancime - 1, parinte=self))
            else:
                l_stari_mutari.append(Stare(mutare, juc_opus, self.adancime - 1, parinte=self))
        return l_stari_mutari

    def __str__(self):
        sir = str(self.configuratie) + "(Juc curent:" + self.j_curent + ")\n"
        return sir


def min_max(stare):
    # Daca am ajuns la o frunza a arborelui, adica:
    # - daca am expandat arborele pana la adancimea maxima permisa
    # - sau daca am ajuns intr-o configuratie finala de joc
    if stare.adancime == 0 or stare.configuratie.final():
        # calculam scorul frunzei apeland "estimeaza_scor"
        stare.scor = stare.configuratie.estimeaza_scor(stare.adancime)
        return stare

    # Altfel, calculez toate mutarile posibile din starea curenta
    stare.mutari_posibile = stare.mutari_stare()

    # aplic algoritmul minimax pe toate mutarile posibile (calculand astfel subarborii lor)
    mutari_scor = [min_max(mutare) for mutare in stare.mutari_posibile]

    if stare.j_curent == Joc.JMAX:
        # daca jucatorul e JMAX aleg starea-fiica cu scorul maxim
        stare.stare_aleasa = max(mutari_scor, key=lambda x: x.scor)
    else:
        # daca jucatorul e JMIN aleg starea-fiica cu scorul minim
        stare.stare_aleasa = min(mutari_scor, key=lambda x: x.scor)

    # actualizez scorul „tatalui” = scorul „fiului” ales
    stare.scor = stare.stare_aleasa.scor
    return stare


def alpha_beta(alpha, beta, stare):
    # Daca am ajuns la o frunza a arborelui, adica:
    # - daca am expandat arborele pana la adancimea maxima permisa
    # - sau daca am ajuns intr-o configuratie finala de joc
    if stare.adancime == 0 or stare.configuratie.final():
        # calculam scorul frunzei apeland "estimeaza_scor"
        stare.scor = stare.configuratie.estimeaza_scor(stare.adancime)
        return stare

    # Conditia de retezare:
    if alpha >= beta:
        return stare  # este intr-un interval invalid, deci nu o mai procesez

    # Calculez toate mutarile posibile din starea curenta (toti „fiii”)
    stare.mutari_posibile = stare.mutari_stare()

    if stare.j_curent == Joc.JMAX:
        scor_curent = float('-inf')  # scorul „tatalui” de tip MAX

        # pentru fiecare „fiu” de tip MIN:
        for mutare in stare.mutari_posibile:
            # calculeaza scorul fiului curent
            stare_noua = alpha_beta(alpha, beta, mutare)

            # incerc sa imbunatatesc (cresc) scorul si alfa
            # „tatalui” de tip MAX, folosind scorul fiului curent
            if scor_curent < stare_noua.scor:
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor

            if alpha < stare_noua.scor:
                alpha = stare_noua.scor
                if alpha >= beta:  # verific conditia de retezare
                    break  # NU se mai extind ceilalti fii de tip MIN


    elif stare.j_curent == Joc.JMIN:
        scor_curent = float('inf')  # scorul „tatalui” de tip MIN

        # pentru fiecare „fiu” de tip MAX:
        for mutare in stare.mutari_posibile:
            stare_noua = alpha_beta(alpha, beta, mutare)

            # incerc sa imbunatatesc (scad) scorul si beta
            # „tatalui” de tip MIN, folosind scorul fiului curent
            if scor_curent > stare_noua.scor:
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor

            if beta > stare_noua.scor:
                beta = stare_noua.scor
                if alpha >= beta:  # verific conditia de retezare
                    break  # NU se mai extind ceilalti fii de tip MAX

    # actualizez scorul „tatalui” = scorul „fiului” ales
    stare.scor = stare.stare_aleasa.scor

    return stare


def afis_daca_final(stare_curenta):
    """Functie care verifica daca s-a ajuns la finalul jocului. In caz afirmativ, au loc anumite afisari"""
    final = stare_curenta.configuratie.final()
    if final:
        if final == "remiza":
            print("Remiza!\nScorul a fost 24 - 24")
        else:
            print("CONCLUZIE\n-----------------------------------\nA castigat " + final)
            print("Scorul calculatorului: %d" % (
                    stare_curenta.configuratie.scor_calculator + sum(stare_curenta.configuratie.holes_calculator)))
            print("Scorul jucatorului: %d" % (
                    stare_curenta.configuratie.scor_jucator + sum(stare_curenta.configuratie.holes_jucator)))
        return True
    return False


def main():
    timp_start_joc = time.time()  # Retine timpul de start al jocului
    nr_miscari_jucator = 0  # Numarul de mutari ale jucatorului
    nr_miscari_calculator = 0  # Numarul de mutari ale calculatorului

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
        n = input("Alege nivelul de dificultate:\n1.Incepator \n2.Mediu \n3.Avansat\n")
        if n.isdigit() and 1 <= int(n) <= 3:
            if int(n) == 1:
                Stare.ADANCIME_MAX = 2
            elif int(n) == 2:
                Stare.ADANCIME_MAX = 4
            else:
                Stare.ADANCIME_MAX = 6
            raspuns_valid = True
        else:
            print("Trebuie sa introduceti un numar de la 1 la 3!")

    # initializare jucatori
    [s1, s2] = Joc.SIMBOLURI_JUC.copy()  # lista de simboluri posibile
    raspuns_valid = False
    while not raspuns_valid:
        Joc.JMIN = str(
            input("Doriti sa jucati cu {} sau cu {}?\nJucatorul {} incepe mereu primul \n".format(s1, s2, s1)))
        if Joc.JMIN in Joc.SIMBOLURI_JUC:
            raspuns_valid = True
        else:
            print("Raspunsul trebuie sa fie {} sau {}.".format(s1, s2))
    Joc.JMAX = s1 if Joc.JMIN == s2 else s2

    raspuns_valid = False
    interfata_grafica = False
    while not raspuns_valid:
        interfata_grafica = input("Alege modul de joc:\n1.Consola\n2.Interfata grafica\n")
        if interfata_grafica.isdigit() and 1 <= int(interfata_grafica) <= 2:
            raspuns_valid = True
            if interfata_grafica == "2":
                interfata_grafica = True
            else:
                interfata_grafica = False
        else:
            print("Raspunsul trebuie sa fie 1 sau 2!")

    raspuns_valid = False

    # initializare tabla
    configuratie = Joc()

    print("Tabla initiala")
    print(str(configuratie))

    # creare stare initiala
    stare_curenta = Stare(configuratie, Joc.SIMBOLURI_JUC[0], Stare.ADANCIME_MAX)
    coloana = -1
    stop = False

    GUI = []
    ecran = None

    # setari interf grafica, daca este cazul
    if interfata_grafica:
        pygame.init()
        pygame.display.set_caption('Mancala')
        ecran = pygame.display.set_mode(size=(670, 240))
        GUI = deseneaza_grid(ecran, stare_curenta.configuratie)
        pygame.display.flip()

    while not stop:
        if stare_curenta.j_curent == Joc.JMIN:
            print("\nRandul jucatorului")
            randul_meu = True
            timp_jucator = time.time()
            while randul_meu:

                if interfata_grafica:
                    for event in pygame.event.get():
                        if event.type == pygame.QUIT:
                            print(
                                "\n---------------------------------------------\n"
                                "Jocul a fost intrerupt\n"
                                "Scorul a fost: "
                                "\nCalculator: %d\nJucator: %d " % (
                                    stare_curenta.configuratie.scor_calculator,
                                    stare_curenta.configuratie.scor_jucator))
                            afisari_final(nr_miscari_jucator, nr_miscari_calculator, timp_start_joc)
                            pygame.quit()
                            sys.exit()

                        if event.type == pygame.MOUSEBUTTONDOWN:
                            pos = pygame.mouse.get_pos()

                            for np in range(len(GUI)):
                                if GUI[np].collidepoint(pos):
                                    # muta jucatorul
                                    if stare_curenta.configuratie.holes_jucator[
                                        np] != 0:  # Daca este valida miscarea (am piese pe pozitia respectiva)
                                        coloana = np
                                        print("Jucatorul a gandit timp de %d secunde" % (time.time() - timp_jucator))

                                        timp_jucator = time.time()
                                        nr_miscari_jucator += 1
                                        stare_curenta.configuratie.scor_jucator, randul_meu = stare_curenta.configuratie.update(
                                            coloana, stare_curenta.configuratie.holes_jucator,
                                            stare_curenta.configuratie.holes_calculator,
                                            stare_curenta.configuratie.scor_jucator)
                                        # afisarea starii jocului in urma mutarii utilizatorului
                                        print("\nTabla dupa mutarea jucatorului")
                                        print(str(stare_curenta))
                                        GUI = deseneaza_grid(ecran,
                                                             stare_curenta.configuratie)  # Deseneaza noua configuratie
                                        # testez daca jocul a ajuns intr-o stare finala
                                        # si afisez un mesaj corespunzator in caz ca da
                                        if afis_daca_final(stare_curenta):
                                            stop = True
                                            randul_meu = False
                                            break

                                        # S-a realizat o mutare. Daca nu este randul meu din nou, schimb jucatorul
                                        if randul_meu is False:
                                            stare_curenta.j_curent = stare_curenta.jucator_opus()
                                        break
                                    else:
                                        print("Miscare invalida!")
                    pygame.display.update()
                else:  # Nu sunt pe interfata grafica
                    raspuns_valid = False
                    while not raspuns_valid:
                        try:
                            coloana = input("coloana = ")
                            if coloana == 'exit':
                                # se termina jocul
                                print(
                                    "\n---------------------------------------------\n"
                                    "Jocul a fost intrerupt\n"
                                    "Scorul a fost: "
                                    "\nCalculator: %d\nJucator: %d " % (
                                        stare_curenta.configuratie.scor_calculator,
                                        stare_curenta.configuratie.scor_jucator)
                                )
                                afisari_final(nr_miscari_jucator, nr_miscari_calculator, timp_start_joc)
                                sys.exit()


                            elif coloana.isdigit() and 0 <= int(coloana) < Joc.NR_HOLES:  # Interval corect
                                coloana = int(coloana)
                                if stare_curenta.configuratie.holes_jucator[coloana] != 0:  # Am miscare valida
                                    raspuns_valid = True
                                else:
                                    print("Mutare invalida!")
                            else:
                                if not coloana.isdigit():
                                    print("Tastati << exit >> sau alegeti o coloana")
                                else:
                                    print(
                                        "Coloana invalida (trebuie sa fie un numar intre 0 si %d)" % (Joc.NR_HOLES - 1))
                        except ValueError:
                            print("Coloana   trebuie sa fie un numar intreg.")

                    nr_miscari_jucator += 1
                    print("Jucatorul a gandit timp de %d secunde" % (time.time() - timp_jucator))
                    timp_jucator = time.time()
                    stare_curenta.configuratie.scor_jucator, randul_meu = (coloana, stare_curenta.configuratie.holes_jucator, stare_curenta.configuratie.holes_calculator, stare_curenta.configuratie.scor_jucator)
                    # afisarea starii jocului in urma mutarii utilizatorului
                    print("\nTabla dupa mutarea jucatorului")
                    print(str(stare_curenta))
                    # testez daca jocul a ajuns intr-o stare finala
                    # si afisez un mesaj corespunzator in caz ca da
                    if afis_daca_final(stare_curenta):
                        stop = True
                        randul_meu = False
                        break

                    # S-a realizat o mutare. Daca nu este randul meu din nou, schimb jucatorul
                    if randul_meu is False:
                        stare_curenta.j_curent = stare_curenta.jucator_opus()

        # --------------------------------
        else:  # jucatorul e JMAX (calculatorul)
            # Mutare calculator

            while True:
                # preiau timpul in milisecunde de dinainte de mutare
                t_inainte = int(round(time.time() * 1000))


                if tip_algoritm == '1':
                    stare_actualizata = min_max(stare_curenta)
                    stare_curenta.configuratie = stare_actualizata.stare_aleasa.configuratie

                else:  # tip_algoritm==2
                    stare_actualizata = alpha_beta(-5000, 5000, stare_curenta)
                    stare_curenta.configuratie = stare_actualizata.stare_aleasa.configuratie

                # Daca nu mai poate fi facuta nicio mutare, se opreste. Conditie folosita in cazul in care initializez tabla
                # jocului ca fiind deja o "stare finala".

                print("Randul calculatorului")
                print("Tabla dupa mutarea calculatorului")
                print(str(stare_curenta))

                if interfata_grafica:
                    GUI = deseneaza_grid(ecran, stare_curenta.configuratie)

                t_dupa = int(round(time.time() * 1000))  # preiau timpul in milisecunde de dupa mutare
                nr_miscari_calculator += 1
                print("Calculatorul a \"gandit\" timp de " + str(t_dupa - t_inainte) + " milisecunde.")

                if afis_daca_final(stare_curenta):
                    stop = True
                    break

                # Daca nu este din nou randul calculatorului, atunci se schimba jucatorul
                if stare_curenta.configuratie.randul_meu == False:
                    stare_curenta.j_curent = stare_curenta.jucator_opus()
                    break
    afisari_final(nr_miscari_jucator, nr_miscari_calculator, timp_start_joc)


if __name__ == "__main__":
    main()

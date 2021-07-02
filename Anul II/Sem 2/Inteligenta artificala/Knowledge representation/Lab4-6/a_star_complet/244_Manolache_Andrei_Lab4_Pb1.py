
""" definirea problemei """
class Nod:
	def __init__(self, info, h):
		self.info = info
		self.h = h

	def __str__ (self):
		return "({}, h={})".format(self.info, self.h)
	def __repr__ (self):
		return f"({self.info}, h={self.h})"


class Arc:
	def __init__(self, capat, varf, cost):
		self.capat = capat
		self.varf = varf
		self.cost = cost

class Problema:
	def __init__(self):
		self.noduri = [
			Nod('a', float('inf')), Nod('b', 10),
			Nod('c', 3), Nod('d', 7),
			Nod('e', 8), Nod('f', 0),
			Nod('g', 14), Nod('i', 3),
			Nod('j', 1), Nod('k', 2)
		]
		self.arce = [
			Arc('a', 'b', 3),
			Arc('a', 'c', 9),
			Arc('a', 'd', 7),
			Arc('b', 'f', 100),
			Arc('b', 'e', 4),
			Arc('c', 'e', 10),
			Arc('c', 'g', 6),
			Arc('d', 'i', 4),
			Arc('e', 'f', 8),
			Arc('e', 'c', 1),
			Arc('g', 'e', 7),
			Arc('i', 'k', 1),
			Arc('i', 'j', 2)
		]
		self.nod_start = self.noduri[0]		# de tip Nod
		self.nod_scop = 'f'					# doar info (fara h)




	def cauta_nod_nume(self, info):
		"""Stiind doar informatia "info" a unui nod,
		trebuie sa returnati fie obiectul de tip Nod care are acea informatie,
		fie None, daca nu exista niciun nod cu acea informatie."""
		 # TO DO...
		for node in self.noduri:
			if info == node.info:
				return node
		return None



""" Sfarsit definire problema """



""" Clase folosite in algoritmul A* """

class NodParcurgere:
	"""O clasa care cuprinde informatiile asociate unui nod din listele open/closed
		Cuprinde o referinta catre nodul in sine (din graf)
		dar are ca proprietati si valorile specifice algoritmului A* (f si g).
		Se presupune ca h este proprietate a nodului din graf

	"""

	problema = None		# atribut al clasei


	def __init__(self, nod_graf, parinte=None, g=0, f=None):
		self.nod_graf = nod_graf	# obiect de tip Nod
		self.parinte = parinte		# obiect de tip Nod
		self.g = g					# costul drumului de la radacina pana la nodul curent
		if f is None :
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
		while nod_c.parinte is not None :
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
		while nod_curent.parinte is not None: # cat timp nu am ajuns la radacina
			if nod_curent.nod_graf.info ==  nod.info: # compar
				return True
			else:
				nod_curent = nod_curent.parinte # merg mai departe
		return False

	# se modifica in functie de problema
	def expandeaza(self):
		"""Pentru nodul curent (self) parinte, trebuie sa gasiti toti succesorii (fiii)
		si sa returnati o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
		sau lista vida, daca nu exista niciunul.
		(Fiecare tuplu contine un obiect de tip Nod si un numar.)
		"""
		# TO DO...
		lista = []
		nod_curent = self
		for much in nod_curent.problema.arce:
			if nod_curent.nod_graf.info == much.capat:
				lista.append( (nod_curent.problema.cauta_nod_nume(much.varf), much.cost) )
		return lista

	# se modifica in functie de problema
	def test_scop(self):
		return self.nod_graf.info == self.problema.nod_scop


	def __str__ (self):
		parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
		return f"({self.nod_graf}, parinte={parinte}, f={self.f}, g={self.g})"



""" Algoritmul A* """


def str_info_noduri(l):
	"""
		o functie folosita strict in afisari - poate fi modificata in functie de problema
	"""
	sir ="["
	for x in l:
		sir +=str(x ) +"  "
	sir +="]"
	return sir


def afis_succesori_cost(l):
	"""
		o functie folosita strict in afisari - poate fi modificata in functie de problema
	"""
	sir =""
	for (x, cost) in l:
		sir +="\nnod:  " +str(x ) +", cost arc: "+ str(cost)

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
	open = [rad_arbore]		# open va contine elemente de tip NodParcurgere
	closed = []				# closed va contine elemente de tip NodParcurgere

	# TO DO...
	while len(open) > 0: # cat timp lista nu e vida
		nod_curent = open.pop(0)  # scotem primul elem din open
		closed.append(nod_curent)  # adaugam in closed

		if nod_curent.test_scop() == True: # daca nod_curent indeplineste conditia scop:
			# afisarea are loc la finalul algoritmului
			break # opresc algoritmul

		succesori = nod_curent.expandeaza() # expandez
		for s in succesori:
			nod_nou = None
			# s[0] = nod succesor
			# s[1] = cost succesor
			if nod_curent.contine_in_drum(s[0]) == False: # nu este continut in drum, merg mai departe in algoritm:

				if in_lista(open, s[0]) is not None: # nod_succesor e in open

					nod = in_lista(open, s[0])
					g_succesor = nod_curent.g + s[1]  # adun g-ul nodului curent si costul succesorului
					f_succesor = g_succesor + s[0].h  # adun la g_succesor h-ul nodului succesor

					if f_succesor < nod.f: # compar si updatez daca e cazul
						open.remove(nod) # scoate nodul vechi din open
						nod.parinte = nod_curent # seteaza noul parinte, updateaza f,g
						nod_nou = nod
						nod.f = f_succesor
						nod.g = g_succesor

				elif in_lista(closed, s[0]) is not None: # nod succesor e in closed

					nod = in_lista(closed, s[0])
					g_succesor = nod_curent.g + s[1]  # adun g-ul nodului curent si costul succesorului
					f_succesor = g_succesor + s[0].h  # adun la g_succesor h-ul nodului succesor

					if f_succesor < nod.f: # compar f-urile, updatez in caz ca e nevoie
						closed.remove(nod)  # scot nodul din lista closed
						nod_nou = nod
						nod.parinte = nod_curent  # actualizez parintele
						nod.g = g_succesor  # actualizez g
						nod.f = f_succesor  # actualizez f

				else: # nod succesor nu e in niciuna, il creez? Nu cred ca am vazut varianta asta in pseudocod, dar cred ca ar trebui facut asa ceva
					g_succesor = nod_curent.g + s[1]  # adun g-ul nodului curent si costul succesorului
					nod_nou = NodParcurgere(s[0], nod_curent, g_succesor, None)

				if nod_nou: # updatez lista open, in functie de acel criteriu crescator dupa f, desc dupa g
					i = 0
					while i < len(open):
						elem_f = open[i].f
						elem_g = open[i].g
						if elem_f >= nod_nou.f:
							while elem_f == nod_nou.f and elem_g > nod_nou.g and i < len(open):
								i = i + 1 # parcurg cat timp indeplinesc acea conditie
							break
						else:
							i = i + 1
					open.insert(i, nod_nou)

	print("\n------------------ Concluzie -----------------------")
	if(len(open )==0):
		print("Lista open e vida, nu avem drum de la nodul start la nodul scop")
	else:
		print("Drum de cost minim: " + str_info_noduri(nod_curent.drum_arbore()))


if __name__ == "__main__":
	problema = Problema()
	NodParcurgere.problema = problema
	a_star()

/*S˘a se scrie ˆın Prolog un predicat binar adaugnrvar(T ermen, T ermenModif icat) definit ca
mai jos, precum ¸si toate predicatele auxiliare necesare pentru definirea acestuia:
adaugnrvar s˘a fie satisf˘acut ddac˘a ambele argumente ale sale sunt termeni Prolog, iar al doilea argument
al s˘au se obt¸ine din primul ˆın modul urm˘ator: pentru fiecare subtermen care nu e nici variabil˘a, nici
1
constant˘a, se va ad˘auga, ca prim argument al operatorului dominant al acelui subtermen, num˘arul de
variabile care apar ˆın acel subtermen, indiferent de numele acestora (a¸sadar, o variabil˘a cu acela¸si nume este
num˘arat˘a de ori de cˆate ori apare);
¸si, ˆıntr–o interogare ˆın Prolog, adaugnrvar s˘a funct¸ioneze sub forma: dac˘a prime¸ste un termen arbitrar
T ˆın primul argument, s˘a obt¸in˘a, ˆın al doilea argument, termenul construit din T ca mai sus;*/

eFunctie(H) :- nonvar(H), functor(H,_,Ar), Ar > 0.

numaraVar([],0).
numaraVar([H|T],Nr) :- (var(H);eFunctie(H)),
    numaraVar(T,Nr1), Nr is Nr1+1.
numaraVar([H|T],Nr) :- not(var(H)), not(eFunctie(H)),
    numaraVar(T,Nr).

adaugaLista([],[]).
adaugaLista([H|T],Rez) :- eFunctie(H),adaugaTermen(H, Fnou1), adaugaLista(T,Fnou2), append([Fnou1],Fnou2,Rez).
adaugaLista([H|T],Rez) :- not(eFunctie(H)), adaugaLista(T,Fnou),append([H],Fnou,Rez).

adaugaTermen(F,Fnou) :- eFunctie(F), F=..[Nume|Termeni], numaraVar(Termeni,Nr),
                        adaugaLista(Termeni,Fnou1),Fnou=..[Nume,Nr|Fnou1].

adauganrvar(F,F) :- not(eFunctie(F)). %adica e constanta
adaugnrvar(F,Rez) :- adaugaTermen(F,Rez).
























/*
transformaInLista(Termen, Op, Termeni) :- Termen =.. [Op|Termeni].
nrVar([],0).
nrVar([H|L],Nr) :- nrVar(L,Nr1), var(H), Nr is Nr1+1.
nrVar([H|L],Nr) :- nrVar(L,Nr1), functor(H,_,A), A > 0, Nr is Nr1+1.
nrVar([H|L],Nr1) :- nrVar(L,Nr1), not(var(H)), functor(H,_,A), A = 0.

nrVarTermen(Termen, Nr) :- nrVar(Termen,Nr).

adaugnrvar(Term, NouTerm) :- transformaInLista(Term,Op,Termeni), nrVarTermen(Termeni,Nr), NouTerm =.. [Op|[Nr|Termeni]].
*/

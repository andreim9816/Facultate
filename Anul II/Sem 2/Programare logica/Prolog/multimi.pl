% concatenarea a doua liste:

concat([],L,L).
concat([H|T],L,[H|M]) :- concat(T,L,M).

% stergerea tuturor aparitiilor unui element intr-o lista:

stergetot(_,[],[]).
stergetot(X,[X|L],M) :- stergetot(X,L,M).
stergetot(X,[H|L],[H|M]) :- X\=H,stergetot(X,L,M).

/*eliminarea duplicatelor dintr-o lista, transformand, astfel,
lista in multime:*/

elimdup([],[]).
elimdup([H|T],[H|L]) :- stergetot(H,T,M),elimdup(M,L).

% reuniunea de multimi, sau de liste, ca multimi:

reun(L,M,R) :- concat(L,M,C),elimdup(C,R).

% testarea aparitiei unui element intr-o lista:

apartine(X,[X|_]).
apartine(X,[_|L]) :- apartine(X,L).

% testam daca o lista e multime, adica nu are duplicate:

emult([]).
emult([H|T]) :- emult(T),not(apartine(H,T)).

% intersectia de multimi:

inters([],_,[]).
inters([H|T],L,[H|M]) :- apartine(H,L),inters(T,L,M).
inters([H|T],L,M) :- not(apartine(H,L)),inters(T,L,M).

% intersectia de liste ca multimi:

interslist(L,M,R) :- elimdup(L,L1),elimdup(M,M1),inters(L1,M1,R).

% diferenta de multimi:

dif([],_,[]).
dif([H|T],L,[H|M]) :- not(apartine(H,L)),dif(T,L,M).
dif([H|T],L,M) :- apartine(H,L),dif(T,L,M).

% varianta: scrierea diferentei recursiv dupa al doilea argument al sau, folosind predicatul stergetot:

dif2(M,[],M).
dif2(M,[H|T],R) :- stergetot(H,M,L),dif2(L,T,R).

% diferenta de liste ca multimi:

diflist(L,M,R) :- elimdup(L,L1),elimdup(M,M1),dif(L1,M1,R).

% puteam elimina duplicatele numai din L

% diferenta simetrica de multimi, sau de liste ca multimi:

difsim(L,M,R) :- dif(L,M,C),dif(M,L,D),reun(C,D,R).

/*
Ca mai sus se poate proceda pentru scrierea urmatoarelor operatii pentru liste ca multimi,
adica pentru liste arbitrare carora li se elimina, mai intai, duplicatele.
*/

% produsul cartezian a doua multimi:

prodcart([],_,[]).
prodcart(_,[],[]).
prodcart(L,M,P) :- setof((X,Y),(apartine(X,L),apartine(Y,M)),P),write(P).

% Sa generam produsul cartezian a doua multimi si recursiv, fara a ne folosi de predicatul setof.

% Produsul cartezian al unui singleton dat prin unicul sau element cu o multime sau lista oarecare:

sglorimult(_,[],[]).
sglorimult(X,[H|T],[K|V]) :- K=(X,H),sglorimult(X,T,V).

% Produsul cartezian a doua multimi sau liste, fara setof:

multorimult([],_,[]).
multorimult([H|T],L,M) :- sglorimult(H,L,R),multorimult(T,L,S),concat(R,S,M).

% Daca vrem si rezultatul produsului cartezian afisat pe ecran, dar fara produsele carteziene
% de la pasii intermediari ai recursiei, atunci avem nevoie de un predicat suplimentar:

produscartez(L,M,P) :- multorimult(L,M,P),write(P).

% Aplicat unei multimi, urmatorul predicat obtine submultimile acesteia:

sublista([],_).
sublista([_|_],[]) :- fail.
sublista([H|T],[H|L]) :- sublista(T,L).
sublista([H|T],[_|L]) :- sublista([H|T],L).

% Lista sublistelor unei liste sau (daca M e multime) multimea submultimilor unei multimi M:

parti(M,P) :- setof(S,sublista(S,M),P),write(P).

% Sa generam partile unei multimi si recursiv, fara a ne folosi de predicatul setof.

% Adaugarea unui element la fiecare lista dintr-o lista de liste, apoi concatenarea acesteia cu lista initiala:

addelem(_,[],[]).
addelem(X,[H|T],[[X|H]|V]) :- addelem(X,T,V).

concatadd(X,L,M) :- addelem(X,L,N),concat(L,N,M).

% Lista submultimilor unei multimi sau a sublistelor unei liste, fara setof:

submult([],[[]]).
submult([H|T],L) :- submult(T,M),concatadd(H,M,L).

partile(L,P) :- submult(L,P),write(P).

% Sublistele unei liste, cu elementele e pozitii consecutive in acea lista:

% Urmatoarele variante nu functioneaza, pentru ca argumentele nu sunt suficient instantiate:
%sublistconsec(S,L) :- concat(_,S,M),concat(M,_,L).
%slistconsec(S,L) :- prefix(P,S),concat(P,_,L).
%sublconsec(S,L) :- concat(M,S,P),prefix(P,L).

prefix(P,L) :- concat(P,_,L).

slconsec([],_).
slconsec([H|T],[X|L]) :- prefix([H|T],[X|L]);slconsec([H|T],L).

sublisteconsec(L,LS) :- setof(S,slconsec(S,L),LS),write(LS).

% Generarea sublistelor unei liste cu elementele pe pozitii consecutive in acea lista, fara setof:

sufixe([],L,L).
sufixe([H|T],L,LN) :- sufixe(T,L,LS),LN=[[H|T]|LS].

sufpref([],LC,[[]|LC]).
sufpref(L,LC,LN) :- concat(P,[_],L),sufpref(P,LC,LI),sufixe(L,LI,LN).

sublisteconsecutive(L,LS) :- sufpref(L,[],LS),write(LS).



%aici h reprezinta un element
apartineLista([H|_],X) :- functor(X,Nume,Ar), functor(H,Nume,Ar).

%aici h reprezinta o lista

cautaLista([],X,[[X]]).
cautaLista([H|L], X,[H|L1]) :- not(apartineLista(H,X)), cautaLista(L,X,L1).
cautaLista([H|L], X,[H1|L]) :- apartineLista(H,X), append(H,[X],H1).

acopdomElem(X,Lc,Lc,Lvin,Lvfin,Lf,Lf) :- var(X), Lvfin = [X|Lvin].
acopdomElem(X,Lcin,Lcf,Lv,Lv,Lf,Lf) :- nonvar(X),number(X), Lcf = [X|Lcin].
acopdomElem(X,Lc,Lc,Lv,Lv,Lin,Lfin) :- nonvar(X), not(number(X)),cautaLista(Lin,X,Lfin).

acopdomAux([],[],[],[]).  %lista data, lista de const numerice, lista de variabile, noua lista de functii, vechea lista de functii
acopdomAux([X|L],Lctf,Lvarf,Lfin) :- acopdomAux(L,Lct,Lvar,Lf), acopdomElem(X,Lct,Lctf,Lvar,Lvarf,Lf,Lfin).


acopdom(L,Lout) :- acopdomAux(L,Lct,Lvar,Lfin),
                 ((length(Lct,0),length(Lvar,0),Lout = Lfin);
                 (length(Lct,0),length(Lvar,Len),Len>0,append([Lvar],[Lfin],Lout));
                 (length(Lvar,0),length(Lct,Len),Len>0,append([Lct],[Lfin],Lout));
                 (length(Lct,Len1),Len1>0,length(Lvar,Len2),Len2>0,
                  append([Lct],[Lvar|Lfin],Lout))).

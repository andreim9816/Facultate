% Manolache Andrei, 244

% Cazul de baza
argtermcomp_list([], [], 0).

argtermcomp_list([Head | Tail], New, Nr) :-
    (var(Head); number(Head);atom(Head)), % Daca este variabila, numar, atom, sare peste, incremneteaza
    argtermcomp_list(Tail, New, Nr1),
    Nr is Nr1 + 1.

argtermcomp_list([Head | Tail], Out, 0) :-
    functor(Head, _, _), % Este termen(functie), apelez recursiv pentru el, merg mai departe
    argtermcomp(Head, New),
    argtermcomp_list(Tail, Rez, Nr), % Concatenez daca am ce (nu si listele vide)
    (   Nr > 0 ->   Out = [New , Nr | Rez] ;
	Nr < 1 ->  Out = [New | Rez]
    ).


argtermcomp(X,X) :- var(X), number(X), atom(X).

argtermcomp(Termen, TermenNou) :- % Pentru fiecare termen, apelez functia care imi modifica subtermenii, dupa il refac, eventual pun si numarul de elemente eliminate
    Termen =..[Op|Param],
    argtermcomp_list(Param, Out, Nr),
     (Nr > 0 ->  TermenNou =..[Op|[Nr|Out]];
	 TermenNou =..[Op|Out]
    ).

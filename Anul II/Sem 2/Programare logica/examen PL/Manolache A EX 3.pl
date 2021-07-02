% Manolache Andrei, 244

% Cazurile "de baza"
listintermnr([], []).

listintermnr([List], [[List]]) :- % Nu e numar, rezultatul e o lista ce contine o lista (Pun numarul intr-o lista)
    not(number(List)).

listintermnr([Element], [Element]) :- % E numar, rezultatul e o lista simpla
    number(Element).

listintermnr([Head | Tail], [[Head] | Output]) :-
    number(Head), % daca este numar, atunci merg in recursie, fac numarul o lista noua, rezultatul este concatenarea simpla
    listintermnr(Tail, Output).

listintermnr([ Head | Tail], Output) :-
    not(number(Head)), % Nu este numar, apelez sa mearga in recursie, la intoarcere verific
    listintermnr(Tail, [HeadOutput | TailOutput]), % Preiau primul element, il verific
    (
       not(is_list(HeadOutput)) -> Output = [ [[HeadOutput]] | [HeadOutput | TailOutput]]; % HeadOutput nu este o lista, atunci trebuie sa fac concatenarea de liste simple
       is_list(HeadOutput) -> Output = [ [Head | HeadOutput ]| TailOutput] % HeadOutput este o lista, atunci fac concatenarea ca HeadOutput de tip lista in lista
    ).


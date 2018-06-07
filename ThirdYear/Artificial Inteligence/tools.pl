escreve_lista(X) :-
    \+ is_list(X),!,
    write(' e '),
    write(X),
    write('.').
escreve_lista([]) :- !, write(' e vazio.').
escreve_lista([X]) :- !, escreve_lista(X).
escreve_lista([X | L]) :- 
    write(' sao '),
    write(X),
    escreve_itens(L),
    write('.').

escreve_itens([]) :- !.
escreve_itens([X]) :- 
    !,
    write(' e '),
    write(X).
escreve_itens([X | T]) :- 
    write(', '), write(X), !,
    escreve_itens(T).

escreveln(A) :- write(A), nl.

max(A, B, A) :- A > B, !.
max(_, B, B).

min(A, B, A) :- A < B, !.
min(_, B, B).
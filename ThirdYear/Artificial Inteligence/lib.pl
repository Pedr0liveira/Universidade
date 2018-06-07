/*
    Descrição formal de um problema:

    estado_inicial( ... ).
    estado_final( ... ).
    tr(E0, accao, E1, custo).

    Descricao de um nó de pesquisa:

    no(Estado, Pai, Operacao, Custo, Profundidade) SSE

        Obtém-se o estado "Estado",
        com custo "Custo" a profundidade "Profundidade",
        a partir do estado "Pai" fazendo "Operação". 
*/


pesquisa(Problema, Algoritmo, Solucao, Stat) :-
    consult(Problema),
    estado_inicial(E0),
    pesquisa_alg(
        Algoritmo,
        [no(E0, nenhum, nenhuma, 0, 0)],
        Solucao,
        Stat).

pesquisa_alg(largura, Lista, Solucao, Stat) :-
    pesquisa_largura(Lista, [], Solucao, Stat).
/*
    Pesquisa LARGURA
*/
%
%   Verificar se o topo da lista é um estado final.
%
pesquisa_largura(
    [ no(Ef, Pai, Op, C, P) | R],
    _,
    no(Ef, Pai, Op, C, P),
    stat(1, LL)) :-
    estado_final(Ef),
    length(R, L1),
    LL is L1 + 1.
%
%   Caso contrário, espandir em largura
%
pesquisa_largura( [N | R], V, S, Stats) :-
    N = no(E, _, _, _, _),
    member(E, V), !, % Não expandir estados visitados.
    pesquisa_largura(R, V, S, Stats).
pesquisa_largura([N | Resto], V, Solucao, stat(NN1, LL1)) :-
    N = no(E, _, _, _, _),
    expande_largura(N, Filhos),
    append(Resto, Filhos, Seguintes),
    pesquisa_largura(Seguintes, [E | V], Solucao, stat(NN, LL)),
    NN1 is NN + 1,
    length(Seguintes, LenSeguintes),
    max(LenSeguintes, LL, LL1).

%
%Expande a árvore
%
expande_largura(no(E, A, O, C, P), Filhos) :-
    findall(
        no(Enovo, no(E, A, O, C, P), Onovo, Cnovo, Pnovo),
        (   tr(E, Onovo, Enovo, Cop),
            Pnovo is P + 1,
            Cnovo is C + Cop ),
        Filhos).
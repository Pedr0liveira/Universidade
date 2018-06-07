/*
    Descrição de um Problema
    -------------------------------

    estado_inicial( ... ).
    estado_final( ... ).
    tr(Estado, Acção, Resultado, Custo).

    Descrição dos Nós da Pesquisa
    -----------------------------

    no(Estado, Pai, Acção, Custo, H + C, Profundidade).

*/
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Interface geral para pesquisar
%
%   Procura uma "Solução" do "Problema" usando "Algoritmo"
%   e avaliando os estado com "Heuristica".
%
pesquisa(Problema, Algoritmo, Heuristica, Solucao, Stat) :-
    consult(Problema),    % estado_inicial, estado_final, tr
    consult(Heuristica),  % heuristica
    estado_inicial(E0), 
    pesquisa(Algoritmo, [no(E0, nenhum, nenhum, 0, 1, 0)], Solucao, Stat).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Concretização das pesquisas
%
pesquisa(aestrela, Estado, Solucao, Stat) :- 
    p_aestrela(Estado, Solucao, Stat).

pesquisa(ansiosa, Estado, Solucao, Stat) :- 
    p_ansiosa(Estado, Solucao, Stat).

pesquisa(hillclimbing, [ Estado ], Solucao, Stat) :- 
    p_hillclimbing(Estado, Solucao, [], Stat).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Implementação da Pesquisa Ansiosa
%
%   NB: Implementação sub-optima porque o passo "expande"
%   calcula a heurística, que não é usada.
%
p_ansiosa(
    [no(E, Pai, Op, C, HC, P) | Restantes],
    no(E, Pai, Op, C, HC, P),
    stat(1, EM))
:-
    estado_final(E), !,
    length(Restantes, LR),
    EM is LR + 1.

p_ansiosa([No | Resto], Solucao, stat(EV, EM)) :-
    expande(No, Filhos),                    % Expande o primeiro nó
    append(Filhos, Resto, Seguintes),       % Nova lista de pesquisa
    ordena_a(Seguintes, S_ordenados),       % Ordenação ansiosa
    !,
    p_ansiosa(S_ordenados, Solucao, stat(EV0, EM0)), % Recursivamente, pesquisa na lista expandida
    EV is EV0 + 1,
    length(Seguintes, LenSeguintes),
    max(EM0, LenSeguintes, EM).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Implementação da Pesquisa A*
%
p_aestrela(
    [no(E, Pai, Op, C, HC, P) | Restantes],
    no(E, Pai, Op, C, HC, P),
    stat(1, EM))
:-
    estado_final(E), !,
    length(Restantes, LR),
    EM is LR + 1.

p_aestrela([No | Resto], Solucao, stat(EV, EM)) :-
    expande(No, Filhos),                    % Expande o primeiro nó
    append(Filhos, Resto, Seguintes),       % Nova lista de pesquisa
    ordena_h(Seguintes, S_ordenados),       % Ordenação por heuristica
    !,
    p_aestrela(S_ordenados, Solucao, stat(EV0, EM0)), % Recursivamente, pesquisa na lista expandida
    EV is EV0 + 1,
    length(Seguintes, LenSeguintes),
    max(EM0, LenSeguintes, EM).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
expande(no(E0, Pai, Tr0, C0, HC0, P0), Filhos) :-
    findall(
        no(E1, no(E0, Pai, Tr0, C0, HC0, P0), Tr1, C1, HC1, P1),
        (
            tr(E0, Tr1, E1, CTr1),
            P1 is P0 + 1,
            C1 is CTr1 + C0,
            heuristica(E1, H),
            HC1 is C1 + H
        ),
        Filhos
    ).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Ordenação Ansiosa
%
%   1. associar cada nó ao "custo",
%   2. usar o sort do prolog
%   3. recuperar os nós do "mapa" ordenado
%
ordena_a(Nos, Nos_ordenados) :-
    associa_custo(Nos, Mapa),
    sort(Mapa, Mapa_ordenado),
    projecta_custo(Mapa_ordenado, Nos_ordenados).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
associa_custo([], []).

associa_custo(
    [no(E, P, A, C, H, D) | Resto],
    [i(C, no(E, P, A, C, H, D)) | Resto1])
:-
    associa_custo(Resto, Resto1).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
projecta_custo([], []).

projecta_custo([ i(_, No) | Resto], [No | Resto1]) :-
    projecta_custo(Resto, Resto1).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Ordenação por Heurística
%
%   1. associar cada nó ao valor da heuristica,
%   2. usar o sort do prolog
%   3. recuperar os nós do "mapa" ordenado
%
ordena_h(Nos, Ordenados) :-
    associa_h(Nos, M),
    sort(M, M_ordenado),
    projecta_h(M_ordenado, Ordenados).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Passo 1: Associar cada nó ao valor da heuristica
%
associa_h([], []).

associa_h([no(E, P, A, C, H, D) | Resto], [i(H, no(E, P, A, C, H, D)) | Resto1]) :-
    associa_h(Resto, Resto1).
%
%   Passo 3: Projectar o nó
%
projecta_h([], []).

projecta_h([ i(_, No) | R0], [No | R1]) :-
    projecta_h(R0, R1).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Implementação de Hill-Climbing
%
%   Dado um estado E0, calcula um sucessor E1, espectavelmente mais próximo da solucao.
%
 p_hillclimbing(no(E, Pai, Op, C, HC, P), no(E, Pai, Op, C, HC, P), _, stat(1, 1)) :-
    estado_final(E).

p_hillclimbing(Estado, Solucao, Visitados, stat(EV1, 1)) :-
    % Obter o estado (propriamente)
    Estado = no(E0, _, _, _, _, _),
    % Filhos deste Nó/Estado
    expande(Estado, Filhos),
    % Filtrar os filhos com estados visitados :D
    findall(N, (
        member(N, Filhos),
        N = no(E, _, _, _, _, _),
        \+ member(E, Visitados)
        ), Proximos),
    % Obter o "melhor" filho
    ordena_h(Proximos, [Proximo | _]),
    % iterar.
    p_hillclimbing(Proximo, Solucao, [E0 | Visitados], stat(EV0, 1)),
    EV1 is EV0 + 1.
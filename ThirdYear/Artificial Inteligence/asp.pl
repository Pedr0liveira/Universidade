%estado(Bateria, Posição, Salas Sujas, Carregadores, Dimensões).
:-include('tools.pl').

%(0,0), (4,0), (0,2), (4,2) -> salas sujas
estado_inicial(e(7, (2,0), [(0,0), (4,0), (0,2), (4,2)], [(2,1)], (5,3) )).

estado_final(e(_, Pos, [], Carr, (5,3))):- 
		member(Pos, Carr).
 
%Ação limpar
tr(
	e(Bat, Pos, Sujas, Carr, Dim),
	limpar,
	e(Bat1, Pos, Sujas1, Carr, Dim),
	1
	):- Bat > 0,
		Bat1 is Bat - 1,
		member(Pos, Sujas),
		delete(Sujas, Pos, Sujas1).

%Ação carregar
tr(
	e(_, Pos, Sujas, Carr, Dim),
	carrega,
	e(Bat1, Pos, Sujas, Carr, Dim),
	1
	):- member(Pos,Carr),
		Bat1 is 7.
		
%Ação cima
tr(
	e(Bat, (X, Y), Sujas, Carr, (N, M)),
	cima,
	e(Bat1, (X, Y1), Sujas, Carr, (N, M)),
	1
	) :-Bat > 0,
		Y > 0,
		Bat1 is Bat - 1,
    	Y1 is Y - 1.

%Ação direita
tr(
	e(Bat, (X, Y), Sujas, Carr, (N, M)),
	direita,
	e(Bat1, (X1, Y), Sujas, Carr, (N, M)),
	1
	) :-Bat > 0,
		Bat1 is Bat - 1, 
		X1 is X + 1,
		X1 < N.

%Ação baixa
tr(
	e(Bat, (X, Y), Sujas, Carr, (N, M)),
	baixo,
	e(Bat1, (X, Y1), Sujas, Carr, (N, M)),
	1
	) :-Bat > 0,
		Bat1 is Bat - 1,
		Y1 is Y + 1,
    	Y1 < M.

%Ação esquerda
tr(
	e(Bat, (X, Y), Sujas, Carr, (N, M)),
	esquerda,
	e(Bat1, (X1, Y), Sujas, Carr, (N, M)),
	1
	) :-Bat > 0,
		Bat1 is Bat - 1,
		X > 0,
    	X1 is X - 1.
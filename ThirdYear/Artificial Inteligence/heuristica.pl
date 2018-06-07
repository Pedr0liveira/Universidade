%
%Calcula a próxima casa suja mais próxima e verifica se através desta se consegue chegar a um carregador.
%Se sim, avança para ela, e repete.
%
heuristica(e(BAT, POS, SSUJAS, CARR, _), VAL):-
	distSuja(POS, SSUJAS, X, POSX),
	X1 is X + 1,
	distCarr(POSX, CARR, X2),
	X2 = X2 + X1,
	X2 =< BAT,
	VAL is X2.
heuristica(e(_,_,_,_,_), _):- heuristica(e(_,_,_,_,_), 7).

%
%Distância para a próxima sala suja.
%
distSuja(_, [], _, _).
distSuja(POS, [CAB|LISTA], RESULT, L) :-
	manhattan(POS, CAB, COISA),
	(nonvar(RESULT);write(RESULT),min(COISA, RESULT, MIN),
	RESULT is MIN),
	RESULT == COISA,
	L is CAB,
	distSuja(POS,LISTA, RESULT,L).
distSuja(POS, [_|LISTA], RESULT, L):- distSuja(POS, LISTA, RESULT, L).
	
%
%Distância entre a próxima sala suja e um carregador.
%
distCarr(_, [], _).
distCarr(POSINI, [CAB|LISTA], DISTCARR):-
	manhattan(POSINI, CAB, COISA2),
	(nonvar(DISTCARR);min(COISA2, DISTCARR, MIN),
	DISTCARR is MIN),
	DISTCARR == COISA2,
	distCarr(POSINI, LISTA, DISTCARR).
distCarr(POSINI, [_|LISTA], DISTCARR):- distCarr(POSINI, LISTA, DISTCARR).

%
%algoritmo de pequisa manhattan
%
manhattan((X,Y),(EndX,EndY),Val):- 
	CurrX is EndX - X,
	changeSignal(CurrX,CurrX2),
	
	CurrY is EndY - Y,
	changeSignal(CurrY,CurrY2),
	
	Val is CurrX2 + CurrY2.

% muda o sinal se for negativo, caso contraria nao altera
changeSignal(N,M):- ((N < 0) -> M is N*(-1); M is N ).	
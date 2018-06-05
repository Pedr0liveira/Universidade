
%option yylineno

%{
	#include <stdlib.h>
	#include <string.h>
	#include "parser.h"

	int line = 0;
	int column = 0;
	#define INC_RET(x, y) column += x; return(y)
	#define INC_COL(x)	column += x
	#define INC_LINE line++; column = 0

%}

LINT [0-9]+
ID [a-zA-Z][a-zA-Z0-9_]*
LFLOAT [0-9]*\.[0-9]+([eE]([\-])?[0-9]+)?
LSTRING \"[^\"]*\"
COMMENT \%[^\n]*\n

%%


"\""	{INC_RET(1, ASP); }

"{"		{INC_RET(1, LCBRACE); }
"}"		{INC_RET(1, RCBRACE); }
"["		{INC_RET(1, LSBRACE); }
"]"		{INC_RET(1, RSBRACE); }
"("		{INC_RET(1, LPAR); }
")"		{INC_RET(1, RPAR); }

"="		{INC_RET(1, ASSIGN); }
";"		{INC_RET(1, SEMI); }
"."		{INC_RET(1, DOT); }
","		{INC_RET(1, COMMA); }
":"		{INC_RET(1, DPOINTS); }


"+"		{INC_RET(1, ADD); }
"-" 	{INC_RET(1, SUB); }
"/"		{INC_RET(1, DIV); }
"*"		{INC_RET(1, MUL); }
"^"		{INC_RET(1, POW); }
"mod"	{INC_RET(3, MOD); }

"<"		{INC_RET(1, LESS); }
">"		{INC_RET(1, BIGGER); }
"=="	{INC_RET(2, EQUALS); }
"!="	{INC_RET(2, NOTEQU); }
"<="	{INC_RET(2, LESSEQU); }
">="	{INC_RET(2, BIGGEREQU); }


"and"	{INC_RET(3, AND); }
"or" 	{INC_RET(2, OR); }
"not"	{INC_RET(3, NOT); }

"int"	{INC_RET(3, INT); }
"float" {INC_RET(5, FLOAT); }
"string" {INC_RET(6, STRING); }
"bool"	{INC_RET(4, BOOL); }
"void"	{INC_RET(4, VOID); }

"define" {INC_RET(6, DEFINE); }
"if"	{INC_RET(2, IF); }
"then"	{INC_RET(4, THEN); }
"else"	{INC_RET(4, ELSE); }
"while"	{INC_RET(5, WHILE); }
"do"	{INC_RET(2, DO); }

"return" {INC_RET(6, RETURN); }
"break"	{INC_RET(5, BREAK); }
"next"	{INC_RET(4, NEXT); }

"print"	{INC_RET(5, PRINT); }
"input"	{INC_RET(5, INPUT); }

[ \t]+	{INC_COL(strlen(yytext)); } //ignora espaços e tabs.

"true"	{yylval.boolean = 1; INC_RET(4, BOOLLIT); }
"false"	{yylval.boolean = 0; INC_RET(5, BOOLLIT); }

{LINT}		{yylval.integer = atoi(yytext); INC_RET(strlen(yytext), INTEGER); }
{LFLOAT}	{yylval.floater = atof(yytext); INC_RET(strlen(yytext), FLOATER); }
{LSTRING}	{yylval.string = strdup(yytext); INC_RET(strlen(yytext), LSTRING); }
{ID}		{yylval.id = strdup(yytext); return ID; }

\n 		{INC_LINE; }
.		{printf("Erro lexical na linha: %d", line); }

{COMMENT}		{INC_LINE; }

%%

int yywrap() {return 1; }
%{
	#include <stdio.h>
	#include <string.h>

	int yylex(void);
	void yyerror(const char *);

%}

%union{
	
	int integer;
	float floater;
	char *string;
	char *id;
	int boolean;
}

%token <integer>	INTEGER
%token <floater>	FLOATER
%token <string>		LSTRING
%token <id>			ID
%token <boolean>	BOOLLIT

%token  ASP
%nonassoc LCBRACE RCBRACE LSBRACE RSBRACE LPAR RPAR
%token DOT DPOINTS
%token INT FLOAT STRING BOOL VOID
%token DEFINE IF THEN ELSE WHILE DO
%token RETURN BREAK NEXT

%right  ASSIGN

%token PRINT INPUT
%left SEMI COMMA

%left OR
%left AND  
%left NOT

%nonassoc EQUALS LESS BIGGER LESSEQU BIGGEREQU NOTEQU

%left ADD SUB
%left DIV MUL MOD
%right POW


%%

program:	decls
			;


decls:		decl
		|	decl decls
			;

decl: 		ids DPOINTS type SEMI
		|	ids DPOINTS	type ASSIGN exp SEMI
		|	ID LPAR RPAR DPOINTS type LCBRACE stms RCBRACE SEMI
		|	ID LPAR argdefs RPAR DPOINTS type LCBRACE stms RCBRACE SEMI
		|	DEFINE ID type	SEMI
			;

type:		INT
		|	FLOAT
		|	STRING
		|	BOOL
		|	type LPAR exp RPAR
		|	VOID
			;

ids:
			ID
		|	ID COMMA ids
			;

stms:		decls
		|	ID exp SEMI
		|	IF exp THEN LCBRACE stms RCBRACE SEMI
		|	IF exp THEN LCBRACE stms RCBRACE ELSE LCBRACE stms RCBRACE SEMI
		|	WHILE exp DO LCBRACE stms RCBRACE SEMI
		|	RETURN exp SEMI
		|	NEXT SEMI
		|	BREAK SEMI
		|	PRINT LPAR ids RPAR SEMI
		|	PRINT LPAR STRING RPAR SEMI
		|	PRINT LPAR ID exp RPAR SEMI
		|	INPUT LPAR ID RPAR SEMI
			;

argdefs:	argdef
		|	argdef COMMA argdefs
			;

argdef:		ID DPOINTS type
			;

exp:		ID
		|	INTEGER
		|	FLOATER
		|	LSTRING
		|	BOOLLIT

		|	exp ADD exp
		|	exp SUB exp
		|	exp MUL	exp
		|	exp DIV	exp
		|	exp POW	exp
		| 	MOD exp

		|	exp AND exp
		|	exp OR exp

		|	exp EQUALS exp
		|	exp NOTEQU exp

		|	exp LESS exp
		|	exp BIGGER exp
		|	exp LESSEQU exp
		|	exp	BIGGEREQU exp

		|	NOT exp
		|	SUB exp

		|	LPAR exp RPAR
		|	ID ASSIGN exp
			;

%%


void yyerror(const char *msg)
{
	extern int yylineno;
	fprintf(stderr, "ERROR: %s\n", msg);
	fprintf(stderr, "ERROR LINE: %d\n", yylineno);
}

int main(void)
{
	return yyparse();
}
%{
	#include <stdio.h>
	#include <string.h>
	#include "ini.h"

	int yylex(void);
	void yyerror(const char *);
	char *lastFunc;
	struct hashTable *st;

%}

%union{
	
	int integer;
	float floater;
	char *string;
	char *id;
	int boolean;

	struct decls *decls;
	struct decl *decl;
	struct type *type;
	struct ids *ids;
	struct stm *stm;
	struct argdefs *argdefs;
	struct argdef *argdef;
	struct exp *exp;
	struct stms *stms;

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

%type <decls>	decls;
%type <decl> decl;
%type <type> type;
%type <ids> ids;
%type <stm> stm;
%type <argdefs> argdefs;
%type <argdef> argdef;
%type <exp> exp;
%type <stms> stms;

%%

program:	decls 			{newProgram($1, st); }
			;

decls:		decl			{$$ = newDecls(decl_, $1); }
		|	decls decl		{$$ = newDeclDecls(declDecls_, $2, $1); }
			;

decl: 		ids DPOINTS type SEMI		{$$ = newDeclType(declNoArgs_, $1, $3); createNodeIds($1, $3, st); }
		|	ids DPOINTS	type ASSIGN exp SEMI	{$$ = newDeclExp(declExp_, $1, $3, $5); createNodeIds($1, $3, st); }
		|	ID LPAR RPAR DPOINTS type LCBRACE stms RCBRACE SEMI		{lastFunc = strdup($1); $$ = newDeclStm(declStm_, $1, $5, $7); createNode( $1, $5, st); }
		|	ID LPAR argdefs RPAR DPOINTS type LCBRACE stms RCBRACE SEMI		{ $$ = newDeclArgdefs(declArgdef_, $1, $3, $6, $8); createNodeArgdefs($3, $6, st, $1); }
		|	DEFINE ID type	SEMI	{$$ = newDeclDefine(declDefine_, $2, $3); createNode($2, $3, st); }
			;

type:		INT 	{$$ = newTypeTypes(int_); }
		|	FLOAT 	{$$ = newTypeTypes(float_); }
		|	STRING 	{$$ = newTypeTypes(string_); }
		|	BOOL 	{$$ = newTypeTypes(bool_); }
		|	type LPAR exp RPAR 	{$$ = newTypeExp(typeExp_, $1, $3); }
		|	VOID 	{$$ = newTypeTypes(void_); }
			;

ids:		ID 		{$$ = newId(idsId_, $1); }
		|	ID COMMA ids 	{$$ = newIdIds(idsIdIds_, $1, $3); }
			;

stms:		stm stms 		{$$ = stmsStmStms($1, $2); }
		|	stm 			{$$ = stmsStm($1); }
		;

stm:		decls 			{$$ = stmDecls(stmDecls_, $1); }
		|	ID exp SEMI		{$$ = stmIdExp(stmIdExp_, $1, $2); }
		|	IF exp THEN LCBRACE stms RCBRACE SEMI		{$$ = stmIf(stmIf_, $2, $5); }
		|	IF exp THEN LCBRACE stms RCBRACE ELSE LCBRACE stms RCBRACE SEMI		{$$ = stmIfElse(stmIfElse_, $2, $5, $9); }
		|	WHILE exp DO LCBRACE stms RCBRACE SEMI		{$$ = stmWhile(stmWhile_, $2, $5); }
		|	RETURN exp SEMI		{$$ = stmReturn(stmReturn_, $2); }
		|	NEXT SEMI		{$$ = stmSingle(stmNext_); }
		|	BREAK SEMI		{$$ = stmSingle(stmBreak_); }
		|	PRINT LPAR exp RPAR SEMI		{$$ = stmPrintExp(stmPrintExp_, $3); }
		|	INPUT LPAR ID RPAR SEMI			{$$ = stmInput(stmInput_, $3); }
		|	ID ASSIGN exp SEMI 			{$$ = stmAssign(stmAssign_, $1, $3); }
			;

argdefs:	argdef 					{$$ = argdefsArgdef(argdef_, $1); }
		|	argdef COMMA argdefs 	{$$ = argdefsArgdefs(argdefs_,  $1, $3); }
			;

argdef:		ID DPOINTS type 		{$$ = newArgdef($1, $3); }
			;

exp:		ID 					{$$ = expID(expID_, $1); }
		|	INTEGER 			{$$ = expInt(expInt_, $1); }
		|	FLOATER 			{$$ = expFloater(expFloater_, $1); }
		|	LSTRING  			{$$ = expString(expString_, $1); }
		|	BOOLLIT 			{$$ = expBool(expBool_, $1); }

		|	exp ADD exp 		{$$ = expOp(expSum_, $1, $3); }
		|	exp SUB exp 		{$$ = expOp(expSub_, $1, $3); }
		|	exp MUL	exp 		{$$ = expOp(expMul_, $1, $3); }
		|	exp DIV	exp 		{$$ = expOp(expDiv_, $1, $3); }
		|	exp POW	exp 		{$$ = expOp(expPow_, $1, $3); }
		| 	MOD exp 			{$$ = expSingle(expMod_, $2); }

		|	exp AND exp 		{$$ = expOp(expAnd_, $1, $3); }
		|	exp OR exp 			{$$ = expOp(expOr_, $1, $3); }

		|	exp EQUALS exp 		{$$ = expOp(expEquals_, $1, $3); }
		|	exp NOTEQU exp 		{$$ = expOp(expNotEqu_, $1, $3); }

		|	exp LESS exp 		{$$ = expOp(expLess_, $1, $3); }
		|	exp BIGGER exp 		{$$ = expOp(expBigger_, $1, $3); }
		|	exp LESSEQU exp 	{$$ = expOp(expLessEqu_, $1, $3); }
		|	exp	BIGGEREQU exp 	{$$ = expOp(expBiggerEqu_, $1, $3); }

		|	NOT exp 			{$$ = expSingle(expNot_, $2); }
		|	SUB exp 			{$$ = expSingle(expNeg_, $2); }

		|	LPAR exp RPAR 		{$$ = expSingle(expPar_, $2); }
		|	ID LPAR exp RPAR	{$$ = expTry(try_, $1, $3); }
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
	st = newST();
	lastFunc = "";
	return yyparse();
}
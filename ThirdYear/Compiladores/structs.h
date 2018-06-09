#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum declsKind {decl_, declDecls_} declsKind;
typedef enum declKind {declNoArgs_, declExp_, declStms_, declArgdef_, declDefine_} declKind;
typedef enum typeKind {int_, float_, string_, bool_, void_, typeExp_} typeKind;
typedef enum typeIds {idsId_, idsIdIds_} typeIds;
typedef enum stmsKind {stmsDecls_, stmsIdExp_, stmsIf_, stmsIfElse_, stmsWhile_, stmsReturn_, stmsNext_, stmsBreak_, stmsPrintIds_, stmsPrintString_, stmsPrintExp_, stmsInput_} stmsKind;
typedef enum argdefsKind {argdef_, argdefs_} argdefsKind;
typedef enum expKind {expID_, expInt_, expFloater_, expString_, expBool_, expSum_, expSub_, expMul_, expDiv_, expPow_, expMod_, expAnd_, expOr_, expEquals_, expNotEqu_, expLess_, expBigger_, expLessEqu_, expBiggerEqu_, expNot_, expNeg_, expPar_, expAssign_} expKind;

typedef struct program program;
typedef struct decls decls;
typedef struct decl decl;
typedef struct type type;
typedef struct ids ids;
typedef struct stms stms;
typedef struct argdefs argdefs;
typedef struct exp exp;


struct program
{
	decls *declarations;
};

struct decls
{
	declsKind kind;
	decl *declaration;
	decls *declarations;
};


struct decl
{
	declKind kind;

	union
	{
		ids *id;
		char *identifier;
		
	}u1;

	union
	{
		type *types;
		argdefs *argDefines;
	}u2;

	union
	{
		exp *expression;
		stms *statements1;
		type *types;
	}u3;

	union
	{
		stms *statements2;
	}u4;
};

struct type
{
	typeKind kind;
	type *types;
	exp *expression;
};

struct ids
{
	idsKind kind;

	char *identifier;
	ids *id;
};

struct stms
{
	stmsKind kind;

	union
	{
		decls *declarations;
		char *identifier;
		exp *expression1;
		ids *id;
		char *string;
	}u1;

	union
	{
		exp *expression2;
		stms *statments1;
	}u2;

	stms *statements2;
};

struct argdefs
{
	argdefsKind kind;

	argdef *argDefine;
	argdefs *argDefines;
};

struct argdef
{
	char *identifier;
	type *types;
};

struct exp
{
	expKind kind;
	union
	{
		char *identifier;
		int integer;
		float floater;
		char *string;
		bool boolean;
		exp *expression1;
	}u1;

	exp *expression2;
};

//função inicial.
program *newProgram(decls *declarations);

//funções para declarações múltiplas.
decls *newDecls(declsKind kind, decl *declaration);
decls *newDeclDecls(declsKind kind, decl *declaration, decls *declarations);

//funções para definição de declarações.
decl *newDeclType(declKind kind, ids *id, type *types);
decl *newDeclExp(declKind kind, ids *id, type *types, exp *expression);
decl *newDeclStms(declKind kind, char *identifier, type *types, stms *statements1);
decl *newDeclArgdefs(declKind kind, char *identifier, argdefs *argDefines, type *types, stms *statements2);
decl *newDeclDefine(declKind kind, char *identifier, type *types);

//funções para definição de types.
type *newTypeTypes(typeKind kind);
type *newTypeExp(typeKind kind, type *types, exp *expression);

//funções para atribuição de ids.
ids *newId(idsKind kind, char *identifier);
ids *newIdIds(idsKind kind, char *identifier, ids *id);

//funções para statements.
stms *stmsDecls(stmsKind kind, decls *declarations);
stms *stmsIdExp(stmsKind kind, char *identifier, exp *expression2);
stms *stmsIf(stmsKind kind, exp *expression1, stms *statements1);
stms *stmsIfElse(stmsKind kind, exp *expression1, stms *statements1, stms *statements2);
stms *stmsWhile(stmsKind kind, exp *expression1, stms *statements1);
stms *stmsReturn(stmsKind kind, exp *expression1);
stms *stmsSingle(stmsKind kind);
stms *stmsPrintIds(stmsKind kind, ids *id);
stms *stmsPrintString(stmsKind kind, char *string);
stms *stmsPrintExp(stmsKind kind, char *identifier, exp *expression2);
stms *stmsInput(stmsKind kind, char *identifier);

//função para várias definições de argumentos.
argdefs *argdefsArgdef(argdefsKind kind, argdef *argDefine);
argdefs *argdefsArgdefs(argdefsKind kins, argdef *argDefine, argdefs *argDefines);

//função para definição de argumentos.
argdef *argdef(char *identifier, type *types);

//funções para Expressions.
exp *expID(expKind kind, char *identifier);
exp *expInt(expKind kind, int integer);
exp *expFloater(expKind kind, float floater);
exp *expString(expKind kind, char *identifier);
exp *expBool(expKind kind, bool boolean);
exp *expOp(expKind kind, exp *expression1, exp *expression2);
exp *expSingle(expKind kind, exp *expression1);
exp *expAssign(expKind kind, char *identifier, exp *expression2);
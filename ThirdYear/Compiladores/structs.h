#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum declsKind {decl_, declDecls_} declsKind;
typedef enum declKind {declNoArgs_, declExp_, declStm_, declArgdef_, declDefine_} declKind;
typedef enum typeKind {int_ = 0, float_, string_, bool_, void_, typeExp_} typeKind;
typedef enum idsKind {idsId_, idsIdIds_} idsKind;
typedef enum stmKind {stmAssign_, stmDecls_, stmIdExp_, stmIf_, stmIfElse_, stmWhile_, stmReturn_, stmNext_, stmBreak_, stmPrintIds_, stmPrintString_, stmPrintExp_, stmInput_} stmKind;
typedef enum argdefsKind {argdef_=1, argdefs_=2} argdefsKind;
typedef enum expKind {try_, expID_, expInt_, expFloater_, expString_, expBool_, expSum_, expSub_, expMul_, expDiv_, expPow_, expMod_, expAnd_, expOr_, expEquals_, expNotEqu_, expLess_, expBigger_, expLessEqu_, expBiggerEqu_, expNot_, expNeg_, expPar_} expKind;

typedef struct program program;
typedef struct decls decls;
typedef struct decl decl;
typedef struct type type;
typedef struct ids ids;
typedef struct stm stm;
typedef struct argdefs argdefs;
typedef struct argdef argdef;
typedef struct exp exp;
typedef struct stms stms;

struct stms
{
	stm *stm;
	stms *stms;
};

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

struct stm
{
	stmKind kind;

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
		stms *statements1;
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
		int boolean;
		exp *expression1;
	}u1;

	exp *expression2;
};


//funções para declarações múltiplas.
decls *newDecls(declsKind kind, decl *declaration);
decls *newDeclDecls(declsKind kind, decl *declaration, decls *declarations);

//funções para definição de declarações.
decl *newDeclType(declKind kind, ids *id, type *types);
decl *newDeclExp(declKind kind, ids *id, type *types, exp *expression);
decl *newDeclStm(declKind kind, char *identifier, type *types, stms *statements1);
decl *newDeclArgdefs(declKind kind, char *identifier, argdefs *argDefines, type *types, stms *statements2);
decl *newDeclDefine(declKind kind, char *identifier, type *types);

//funções para definição de types.
type *newTypeTypes(typeKind kind);
type *newTypeExp(typeKind kind, type *types, exp *expression);

//funções para atribuição de ids.
ids *newId(idsKind kind, char *identifier);
ids *newIdIds(idsKind kind, char *identifier, ids *id);

//funções para statement.
stm *stmDecls(stmKind kind, decls *declarations);
stm *stmIdExp(stmKind kind, char *identifier, exp *expression2);
stm *stmIf(stmKind kind, exp *expression1, stms *statements1);
stm *stmIfElse(stmKind kind, exp *expression1, stms *statements1, stms *statements2);
stm *stmWhile(stmKind kind, exp *expression1, stms *statements1);
stm *stmReturn(stmKind kind, exp *expression1);
stm *stmSingle(stmKind kind);
stm *stmPrintIds(stmKind kind, ids *id);
stm *stmPrintString(stmKind kind, char *string);
stm *stmPrintExp(stmKind kind, exp *expression1);
stm *stmInput(stmKind kind, char *identifier);
stm *stmAssign(stmKind kind, char *identifier, exp *expression2);

//função para várias definições de argumentos.
argdefs *argdefsArgdef(argdefsKind kind, argdef *argDefine);
argdefs *argdefsArgdefs(argdefsKind kins, argdef *argDefine, argdefs *argDefines);

//função para definição de argumentos.
argdef *newArgdef(char *identifier, type *types);

//funções para Expressions.
exp *expID(expKind kind, char *identifier);
exp *expInt(expKind kind, int integer);
exp *expFloater(expKind kind, float floater);
exp *expString(expKind kind, char *identifier);
exp *expBool(expKind kind, int boolean);
exp *expOp(expKind kind, exp *expression1, exp *expression2);
exp *expSingle(expKind kind, exp *expression1);

exp *expTry(expKind kind, char *identifier, exp *expression2);

//funções para stms
stms *stmsStmStms(stm *stm, stms *stms);
stms *stmsStm(stm *stm);
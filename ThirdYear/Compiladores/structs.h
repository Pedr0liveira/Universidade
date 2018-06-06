#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum declsKind {decl_, decl_decls} declsKind;
typedef enum declKind {declNoArgs, declExp, declStms, declArgdef, declDefine} declKind;
typedef enum typeKind {int_, float_, string_, bool_, void_, typeEsp_} typeKind;

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
	decls *decls;
};

struct decls
{
	declsKind kind;
	decl *decl;
	decls *decls;
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
		stms *stms1;
		type *types;
	}u3;

	union
	{
		stms *stms2;
	}u4;
};

struct type
{
	typeKind kind;
	type *types;
	exp *expression;
}

struct ids
{
	idsKind kind;

	char *identifier;
	ids *id;
}
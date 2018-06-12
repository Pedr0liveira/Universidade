#include "structs.h"

//funções para declarações múltiplas.
decls *newDecls(declsKind kind, decl *declaration)
{
	decls *new_ = malloc(sizeof(decls));

	new_ -> kind = kind;
	new_ -> declaration = declaration;

	return new_;
}

decls *newDeclDecls(declsKind kind, decl *declaration, decls *declarations)
{
	decls *new_ = malloc(sizeof(decls));

	new_ -> kind = kind;
	new_ -> declaration = declaration;
	new_ -> declarations = declarations;

	return new_;
}

//funções para definição de declarações.
decl *newDeclType(declKind kind, ids *id, type *types)
{
	decl *new_ = malloc(sizeof(decl));

	new_ -> kind = kind;
	new_ -> u1.id = id;
	new_ -> u2.types = types;

	return new_;
}

decl *newDeclExp(declKind kind, ids *id, type *types, exp *expression)
{
	decl *new_ = malloc(sizeof(decl));

	new_ -> kind = kind;
	new_ -> u1.id = id;
	new_ -> u2.types = types;
	new_ -> u3.expression = expression;

	return new_;
}

decl *newDeclStms(declKind kind, char *identifier, type *types, stms *statements1)
{
	decl *new_ = malloc(sizeof(decl));

	new_ -> kind = kind;
	new_ -> u1.identifier = identifier;
	new_ -> u2.types = types;
	new_ -> u3.statements1 = statements1;

	return new_;
}

decl *newDeclArgdefs(declKind kind, char *identifier, argdefs *argDefines, type *types, stms *statements2)
{
	decl *new_ = malloc(sizeof(decl));

	new_ -> kind = kind;
	new_ -> u1.identifier = strdup(identifier);
	new_ -> u2.argDefines = argDefines;
	new_ -> u3.types = types;
	new_ -> u4.statements2 = statements2;

	return new_;
}

decl *newDeclDefine(declKind kind, char *identifier, type *types)
{
	decl *new_ = malloc(sizeof(decl));

	new_ -> kind = kind;
	new_ -> u1.identifier = strdup(identifier);
	new_ -> u2.types = types;

	return new_;
}

//funções para definição de types.
type *newTypeTypes(typeKind kind)
{
	type *new_ = malloc(sizeof(type));

	new_ -> kind = kind;

	return new_;
}

type *newTypeExp(typeKind kind, type *types, exp *expression)
{
	type *new_ = malloc(sizeof(type));

	new_ -> kind = kind;
	new_ -> types = types;
	new_ -> expression = expression;

	return new_;
}

//funções para atribuição de ids.
ids *newId(idsKind kind, char *identifier)
{
	ids *new_ = malloc(sizeof(ids));

	new_ -> kind = kind;
	new_ -> identifier = strdup(identifier);

	return new_;
}

ids *newIdIds(idsKind kind, char *identifier, ids *id)
{
	ids *new_ = malloc(sizeof(ids));

	new_ -> kind = kind;
	new_ -> identifier = strdup(identifier);
	new_ -> id = id;

	return new_;
}

//funções para statements.
stms *stmsDecls(stmsKind kind, decls *declarations)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.declarations = declarations;

	return new_;
}

stms *stmsIdExp(stmsKind kind, char *identifier, exp *expression2)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.identifier = identifier;
	new_ -> u2.expression2 = expression2;

	return new_;
}

stms *stmsIf(stmsKind kind, exp *expression1, stms *statements1)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.expression1 = expression1;
	new_ -> u2.statements1 = statements1;

	return new_;
}

stms *stmsIfElse(stmsKind kind, exp *expression1, stms *statements1, stms *statements2)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.expression1 = expression1;
	new_ -> u2.statements1 = statements1;
	new_ -> statements2 = statements2;

	return new_;
}

stms *stmsWhile(stmsKind kind, exp *expression1, stms *statements1)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.expression1 = expression1;
	new_ -> u2.statements1 = statements1;

	return new_;
}

stms *stmsReturn(stmsKind kind, exp *expression1)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.expression1 = expression1;

	return new_;
}

stms *stmsSingle(stmsKind kind)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;

	return new_;
}

stms *stmsPrintIds(stmsKind kind, ids *id)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.id = id;

	return new_;
}

stms *stmsPrintString(stmsKind kind, char *string)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.string = strdup(string);

	return new_;
}

stms *stmsPrintExp(stmsKind kind, exp *expression1)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind;
	new_ -> u1.expression1 = expression1;

	return new_;
}

stms *stmsInput(stmsKind kind, char *identifier)
{
	stms *new_ = malloc(sizeof(stms));

	new_ -> kind = kind; 
	new_ -> u1.identifier = strdup(identifier);

	return new_;
}

//função para várias definições de argumentos.
argdefs *argdefsArgdef(argdefsKind kind, argdef *argDefine)
{
	argdefs *new_ = malloc(sizeof(argdefs));

	new_ -> kind = kind;
	new_ -> argDefine = argDefine;

	return new_;
}

argdefs *argdefsArgdefs(argdefsKind kind, argdef *argDefine, argdefs *argDefines)
{
	argdefs *new_ = malloc(sizeof(argdefs));

	new_ -> kind = kind;
	new_ -> argDefine = argDefine;
	new_ -> argDefines = argDefines;

	return new_;
}

//função para definição de argumentos.
argdef *newArgdef(char *identifier, type *types)
{
	argdef *new_ = malloc(sizeof(argdef));

	new_ -> identifier = strdup(identifier);
	new_ -> types = types;

	return new_;
}

//funções para Expressions.
exp *expID(expKind kind, char *identifier)
{
	exp *new_ =malloc(sizeof(exp));

	new_ -> kind = kind;
	new_ -> u1.identifier = strdup(identifier);

	return new_;
}

exp *expInt(expKind kind, int integer)
{
	exp *new_ = malloc(sizeof(exp));

	new_ -> kind = kind;
	new_ -> u1.integer = integer;

	return new_;
}

exp *expFloater(expKind kind, float floater)
{
	exp *new_ = malloc(sizeof(exp));

	new_ -> kind = kind;
	new_ -> u1.floater = floater;

	return new_;
}

exp *expString(expKind kind, char *identifier)
{
	exp *new_ = malloc(sizeof(exp));

	new_ -> kind = kind;
	new_ -> u1.identifier = strdup(identifier);

	return new_;
}

exp *expBool(expKind kind, int boolean)
{
	exp * new_ = malloc(sizeof(exp));

	new_ -> kind = kind;
	new_ -> u1.boolean = boolean;

	return new_;
}

exp *expOp(expKind kind, exp *expression1, exp *expression2)
{
	exp *new_ = malloc(sizeof(exp));

	new_ -> kind = kind;
	new_ -> u1.expression1 = expression1;
	new_ -> expression2 = expression2;

	return new_;
}

exp *expSingle(expKind kind, exp *expression1)
{
	exp *new_ = malloc(sizeof(exp));

	new_ -> kind = kind;
	new_ -> u1.expression1 = expression1;

	return new_;
}

exp *expAssign(expKind kind, char *identifier, exp *expression2)
{
	exp *new_ = malloc(sizeof(exp));

	new_ -> kind = kind;
	new_ -> u1.identifier = strdup(identifier);
	new_ -> expression2 = expression2;

	return new_;
}
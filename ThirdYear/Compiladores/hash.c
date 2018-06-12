#include <hash.h>

symbolTable *newSymbolTable()
{
	symbolTable *new_ = malloc(sizeof(symbolTable));

	new_ -> nodeArray = calloc(1000, sizeof(symbolTable));
	new_ -> size = 1000;

	return new_;
}

node *put(tipo tipo, char *name, char *func, symbolTable *newSymbolTable)
{
	node *new_ = malloc(sizeof(node));

	new_ -> tipo = tipo;
	new_ -> name = strdup(name);
	new_ -> func = strdup(func);
	new_ -> symbolTable = symbolTable;

	return new_;
}

node *get(char *name, symbolTable *newSymbolTable)
{
	node *new_ = malloc(sizeof(node));

	new_ -> name = strdup(name);
	new_ -> symbolTable = symbolTable;

	return new_;
}
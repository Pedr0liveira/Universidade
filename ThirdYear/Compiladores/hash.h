#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum tipo {int_, float_, bool_, string_} tipo;

typedef struct node node;
typedef struct ht ht;

struct node
{
	tipo tipo;
	char *name;
	char *func;
};

struct symbolTable
{
	node *nodeArray[];
	int size;
};

symbolTable *newSymbolTable();

node *put(tipo tipo, char *name, char *func, symbolTable *newSymbolTable);

node *get(char *name, symbolTable *newSymbolTable);
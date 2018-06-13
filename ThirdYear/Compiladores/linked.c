#include "linked.h"

//Cria 
void createNode(char *name, tipo type, symbolTable *symbolTable)
{
	int hash = (hash(name) % symbolTable -> size);
	while(symbolTable -> array[hash] != NULL)
	{
		hash++;
		hash %= symbolTable -> size;
	}

	symbolTable -> array[hash] = malloc(sizeof(node));

	strcy(symbolTable -> array[hash] -> name, name);
	symbolTable -> array[hash] -> type = type;
	symbolTable -> array[hash] -> next = NULL;
}

//Pesquisa pela linked list referente a cada função.
node *getNode(char *name, symbolTable *symbolTable)
{
	int hash = (hash(name) % symbolTable -> size);
	while(symbolTable -> array[hash] != NULL && strcmp(symbolTable -> array[hash] -> name, name) != 0)
	{
		hash++;
		hash %= symbolTable -> size;
	}

	return symbolTable -> array[hash];
}

void addNode(char *name, tipo type, char *nameFunc, symbolTable *symbolTable)
{
	int hash = (hash(nameFunc) % symbolTable -> size);
	while(symbolTable -> array[hash] != NULL && strcmp(symbolTable -> array[hash] -> name, nameFunc) != 0)
	{
		hash++;
		hash %= symbolTable -> size;
	}

	node *nextTemp = symbolTable -> array[hash] -> next;

	while(nextTemp != NULL)
	{
		nextTemp = nextTemp -> next;
	}

	nextTemp = malloc(sizeof(nextTemp));
	nextTemp -> name = name;
	nextTemp -> type = type;
	nextTemp -> next = NULL;
}

symbolTable *initialize()
{
	symbolTable *symbolTable = malloc(sizeof(symbolTable));

	symbolTable -> size = 1009;
	symbolTable -> array = calloc(1009, sizeof(node));

	return symbolTable;
}

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
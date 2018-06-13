#include "linked.h"

//djb2
unsigned long hashFunc(char *str)
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

//Cria o primeiro nó da linked list na hashtable.
void createNode(char *name, type *type, symbolTable *symbolTable)
{
	int hash = ((hashFunc(name) % symbolTable -> size));
	while(strcmp(symbolTable -> array[hash].name, "") != 0)
	{
		hash++;
		hash %= symbolTable -> size;
	}

	strcpy(symbolTable -> array[hash].name, name);
	symbolTable -> array[hash].type = type;
	symbolTable -> array[hash].next = NULL;
}

//Pesquisa pela linked list referente a cada função.
node getNode(char *name, symbolTable *symbolTable)
{
	int hash = (hashFunc(name) % symbolTable -> size);
	while(strcmp(symbolTable -> array[hash].name, name) != 0)
	{
		hash++;
		hash %= symbolTable -> size;
	}

	return symbolTable -> array[hash];
}

//Adicionar nós à linked list.
void addNode(char *name, type *type, char *nameFunc, symbolTable *symbolTable)
{
	int hash = (hashFunc(nameFunc) % symbolTable -> size);
	while(strcmp(symbolTable -> array[hash].name, nameFunc) != 0)
	{
		hash++;
		hash %= symbolTable -> size;
	}

	node *nextTemp = symbolTable -> array[hash].next;

	while(nextTemp != NULL)
	{
		nextTemp = nextTemp -> next;
	}

	nextTemp = malloc(sizeof(node));
	nextTemp -> name = strcpy(symbolTable -> array[hash].name, name);
	nextTemp -> type = type;
	nextTemp -> next = NULL;
}

//Inicializa a hash table.
symbolTable *initialize()
{
	symbolTable *symbolTable = malloc(sizeof(symbolTable));

	symbolTable -> size = 1009;
	symbolTable -> array = calloc(1009, sizeof(node));

	for(int i = 0; i < symbolTable -> size; i++)
	{
		symbolTable -> array[i].name = "";

	}

	return symbolTable;
}
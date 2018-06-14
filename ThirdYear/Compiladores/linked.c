#include "linked.h"

char *LastFunc;

//djb2
unsigned long hashFunc(char *str)
{
	//printf("%s\n", str);
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
	symbolTable -> array[hash].name = strdup(name);
	symbolTable -> array[hash].type = type -> types;
	symbolTable -> array[hash].next = NULL;
}

void createNodeIds(ids *id, type *type, symbolTable *symbolTable)
{
	ids *temp = id; 
	createNode(temp -> identifier, type, symbolTable);
	while((temp = temp -> id) != NULL)
	{
		createNode(temp -> identifier, type, symbolTable);
	}
	
}

void createNodeArgdefs(argdefs *argdefs, type *type1, symbolTable *symbolTable, char *lastFunc)
{
	struct argdefs *temp = argdefs;
	createNode(lastFunc, type1, symbolTable);
	while(temp -> kind == 2)
	{
		
		addNode(temp -> argDefine -> identifier, temp -> argDefine -> types, lastFunc, symbolTable);
		temp = temp -> argDefines;
	}
	/*
	while((temp = temp -> argDefines) != NULL)
	{
		addNode(temp -> argDefine -> identifier, type, lastFunc, symbolTable);
	}
	*/
	addNode(temp -> argDefine -> identifier, temp -> argDefine -> types, lastFunc, symbolTable);
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
	printf("%s\n", nameFunc);
	int hash = (hashFunc(nameFunc) % symbolTable -> size);
	while(strcmp(symbolTable -> array[hash].name, nameFunc) != 0)
	{
		//printf("%s\n", symbolTable -> array[hash].name);
		hash++;
		hash %= symbolTable -> size;
	}

	node *nextTemp = symbolTable -> array[hash].next;

	while(nextTemp != NULL)
	{
		nextTemp = nextTemp -> next;
	}

	nextTemp = malloc(sizeof(node));
	//printf("caso1.\n");
	nextTemp -> name = strdup(name);
	nextTemp -> type = type;
	nextTemp -> next = NULL;
}

//Inicializa a hash table.
symbolTable *newST()
{
	symbolTable *st = malloc(sizeof(symbolTable));

	st -> size = 1009;
	st -> array = calloc(1009, sizeof(node));

	for(int i = 0; i < st -> size; i++)
	{
		st -> array[i].name = "";

	}

	return st;
}
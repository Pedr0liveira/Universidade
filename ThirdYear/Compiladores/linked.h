#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

typedef struct node node;
typedef struct hashTable symbolTable;

struct node
{
	node *next;
	char *name;
	tipo type;
};

struct hashTable
{
	node *array;
	int size;
};

unsigned long hashFunc(char *str);
void createNode(char *name, typo *type, symbolTable *symbolTable); //Cria com nome da função e insere na hash table.
node getNode(char *name, symbolTable *symbolTable);	//encontra o nó "name".
void addNode(char *name, type *type, char *nameFunc, symbolTable *symbolTable);	//adiciona um nó de uma var à linked list da "func" expecífica.
symbolTable *initialize();	//inicializa a hashTable.

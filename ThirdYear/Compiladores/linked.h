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
	type *type;
};

struct hashTable
{
	node *array;
	int size;
};

unsigned long hashFunc(char *str);
void createNode(char *name, type *types, symbolTable *symbolTable); //Cria com nome da função e insere na hash table.
void createNodeIds(ids *id, type *types, symbolTable *symbolTable);
node getNode(char *name, symbolTable *symbolTable);	//encontra o nó "name".
void addNode(char *name, type *types, char *nameFunc, symbolTable *symbolTable);	//adiciona um nó de uma var à linked list da "func" expecífica.
symbolTable *newST();	//inicializa a hashTable.
void createNodeArgdefs(argdefs *argdefs, type *types, symbolTable *symbolTable, char *lastFunc);

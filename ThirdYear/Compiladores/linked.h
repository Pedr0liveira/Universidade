#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum tipo {int_, float_, bool_, string_, func_} tipo;
typedef struct node node;
typedef struct hashTable symbolTable;

struct node
{
	node *next;
	char *name;
	tipo type;
}

struct hashTable
{
	node *array;
	int size;
}

void createNode(char *name, tipo type, symbolTable *symbolTable); //Cria com nome da função e insere na hash table.
node *getNode(char *name, symbolTable *symbolTable);	//encontra o nó "name".
void addNode(char *name, tipo type, char *nameFunc, symbolTable *symbolTable);	//adiciona um nó de uma var à linked list da "func" expecífica.
symbolTable *initialize();	//inicializa a hashTable.
unsigned long hash(unsigned char *str);
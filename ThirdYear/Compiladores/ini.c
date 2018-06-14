#include "ini.h"

program *newProgram(decls *declarations, symbolTable *symbolTable)
{
	for(int i = 0; i < 1009; i++)
	{
		if(strcmp(symbolTable -> array[i].name, "") != 0)
		{
			node *temp = &symbolTable -> array[i];
			while(temp != NULL)
			{
				printf("%s, ", symbolTable -> array[i].name);
				/*
				switch(temp -> type -> kind)
				{
					case 0:
						printf("int\n");
						break;
					case 1:
						printf("float\n");
						break;

				}
				*/
				temp = temp -> next;
			}
			printf("\n");
		}
	}
}
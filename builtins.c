#include "PeraShell.h"


int	p_clear(char *buffer)
{
	if (strcmp(buffer, "clear\n") == 0)
	{
		printf("\033[2J\033[H");
		fflush(stdout);
		return 1;
	}
	return 0;
}




int p_history(void)
{
	//fai una copia di ogni stringa input che viene registrata
	//prima del parsing
	//
	//tienila in una tavola di riferimento ordinata da 1 a ....
	//
	//se utente preme su puo risalire alla stringa relativa
	//se poi viene premuto invio e siamo su quella stringa
	//viene data come input nuovamente alla funzione parse che triggera tutto 
	//esegue ecc.
	//
	return 1;
}




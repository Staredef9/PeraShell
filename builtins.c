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



void	init_hist_table(historyTab *table){
	
	table = malloc(sizeof(table) * 1);
	if (!table){
		table = NULL;
		exit(0);
	}
}

void	free_hist_table(historyTab *table){
	
	//TODO: codice per liberare la 
	//tavola della history

}




///custom allocatore di stringhe per rendere dinamica la table;
void	buffer_add_line(***buffer, int *size, int *capacity, char *newline){

	//scorri buffer fino a NULL
	//realloca
	//strudppa la linea
	//aumenta gli iteratori size e capacity	

}

char *retrieve_hist_line(historyTab *table){

	//TODO:percorri a ritroso la tavola fino a quando non e' null
	//ricordati a che punto e' il comando ogni volta che va in su con la freccia in alto la tastiera.	

}

void	print_table(historyTab *table){
		
	//printa tutta la storia dei comandi
	//se possibile con numerino allegato
}

int p_history(historyTab *table, char *buffer)
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
	if(!table)
		init_hist_table(table);
	
	//		




	return 1;
}




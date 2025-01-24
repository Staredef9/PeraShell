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
	
	if (table) {
		table->buffer = NULL;
	}
}

void	free_hist_table(historyTab *table){
	
	//TODO: codice per liberare la 
	//tavola della history
	if(table && table->buffer){
	for (int i = 0; table->buffer[i] != NULL; i++){
	
		free(table->buffer[i]);
	} 
	free(table->buffer);
	free(table);
	printf("history table correctyl freed\n");
	}
}

///custom allocatore di stringhe per rendere dinamica la table;
void	buffer_add_line(char ***buffer, int *size, int *capacity, char *newline){
	//scorri buffer fino a NULL
	//realloca
	//strudppa la linea
	//aumenta gli iteratori size e capacity	
	//
	
	if(!buffer || !size || !capacity || !newline)
		return;

	if(*size >= *capacity){
		
		*capacity = (*capacity == 0) ? 2 : *capacity * 2;
		
		*buffer = realloc(*buffer, (*capacity) * sizeof(char*));
		
		
		if (*buffer == NULL){
			exit(EXIT_FAILURE);
		}
	}

	(*buffer)[*size] = strdup(newline);
	if((*buffer)[*size] == NULL){
		exit(EXIT_FAILURE);
	}
	(*size)++;
	
	(*buffer)[*size] = NULL;

}

char *retrieve_hist_line(historyTab *table){

	//TODO:percorri a ritroso la tavola fino a quando non e' null
	//ricordati a che punto e' il comando ogni volta che va in su con la freccia in alto la tastiera.	
	return NULL;
}

void	print_hist_table(historyTab *table){
	//printa tutta la storia dei comandi
	//se possibile con numerino allegato
	if (table == NULL || table->buffer == NULL){
		printf("Non c'e' storia\n");
		exit(0);
	}

	for( int i = 0; table->buffer[i] != NULL; i++){
	printf("%s",  table->buffer[i]);
	}

}

int p_history(historyTab *table, char *buffer, int *size, int *capacity)
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
		return 0;
	if(!table->buffer)
		init_hist_table(table);
	//
	if (buffer)	
		buffer_add_line(&table->buffer, size, capacity, buffer);		
	return 1;
}




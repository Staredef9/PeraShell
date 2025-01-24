#include "PeraShell.h"


//copia envp come una matrice di righe
//usa la formula di PIPE della 42 per cercare 
//dove sono i comandi nelle variabii di ambiente
//e passali alle funzioni di esecuzione.
//

struct stat statbuf;


int size = 0; 
int capacity = 0;


int main(int argc, char **argv, char **envp)
{
historyTab *table = malloc(sizeof(historyTab));

if (!table) {
    perror("Failed to allocate history table");
    exit(1);
}
	if (stat("/usr/bin", &statbuf) != 0){
		printf("/usr/bin does not exist\n");
	}
	char *args[MAX_LINE/2 + 1];
	int should_run = 1;
	
	char buffer[BUFFER];
	char *cached_path = NULL;
	while(should_run){
		memset(buffer, 0, sizeof(buffer));
		printf("PShell>");
		fflush(stdout);
		ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER-1);
		
		if (bytesRead < 0)
		{
			perror("read");
			return 1;
		}
		
		if (bytesRead > 0){
			buffer[bytesRead] = '\0';
			printf("You endered: %s\n", buffer);
			
			//qui inizializzata 
			//ricordati di liberare appena chiudi 
			p_history(table, buffer, &size, &capacity);			

			//generalizza con unica funzione "check_cases"
			//per pulire qua
			if (strcmp(buffer, "exit\n") == 0){
				should_run = 0;
				printf("Program exited correctly\n");
				///TODO: PULISCI TUTTA LA MEMORIA PRIMA DI USCIRE
				break;
			}
			if(p_clear(buffer) == 1)
				continue;		
			if(strcmp(buffer, "history\n") == 0){
				print_hist_table(table);
		}


			//..aggiungi altri casi 
			//se tutto in linea normale, parsa il risultato ed esegui 
		CommandInfo *prova = parse_input(buffer);
		
		print_cmd_info(prova);
		
		cached_path = init_cached_path(envp, cached_path);
		
		char *cmd_path = find_cmd_in_path(prova->segments->cmd, cached_path, prova->segments->numArguments);
		
		if (cmd_path){
			printf("cmd exists at path: %s\n", cmd_path);
			
			//se tutto esiste, adesso e' il momento di creare un child e passare al child le cose 
			//fare una pipe 
			//aprire la comunicazione 
			//ricevere output del child e assicurarsi che muoia. 
			//printare output
			
			int id;
			int fd[2];
			int exitStatus;


			//devo fare in modo di generalizzare questa cosa con una funzione di modo che qualsiasi comando possa essere inserito cosi dentro un char **
			//poiche execve accetta le cosi in quel formato.
			char *args[] = {prova->segments[0].cmd,prova->segments[0].options[0],prova->segments[0].arguments[0],NULL};


			//Questo codice e' un sample di prova che funziona con un solo comando figlio.
			//Qua in realta' devo creare una logica che gestisca molteplici PIPES e molteplici return di output di ognuno  dei figli di modo 
			//che sia tutto molto malleabile. 
			pipe(fd);
			if (fd[0] == -1)
				return(1);
			id = fork();
			if (id == -1)
				return(4);
			if (id == 0){
				//figlio fa cose
				execve(cmd_path,args, envp);
				printf("execve failed");
				exit(1);
			} else {
				waitpid(id, & exitStatus, 0);
				if(WIFEXITED(exitStatus)){
					int status = WEXITSTATUS(exitStatus);
					printf("Child process exited with status %d\n", status);
				}
			}
		} else
			printf("%s It is not a valid cmd\n", prova->segments->cmd);
		free_cached_path(cached_path);
		free(cmd_path);
		free_commandInfo(prova);
				
		}			
	
	}
		free_hist_table(table);
		return 0;
}

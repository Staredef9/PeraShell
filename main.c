#include "PeraShell.h"


//copia envp come una matrice di righe
//usa la formula di PIPE della 42 per cercare 
//dove sono i comandi nelle variabii di ambiente
//e passali alle funzioni di esecuzione.
//

struct stat statbuf;

int main(int argc, char **argv, char **envp)
{
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
			

			//generalizza con unica funzione "check_cases"
			//per pulire qua
			if (strcmp(buffer, "exit\n") == 0){
				should_run = 0;
				printf("Program exited correctly\n");
				break;
			}
			if(p_clear(buffer) == 1)
				continue;		
		
			//..aggiungi altri casi 
			//se tutto in linea normale, parsa il risultato ed esegui 
		CommandInfo *prova = parse_input(buffer);
		
		print_cmd_info(prova);
		
		cached_path = init_cached_path(envp, cached_path);
		
		char *cmd_path = find_cmd_in_path(prova->segments->cmd, cached_path);
		
		//Buggerino over here ->se metto un non comando lo trova lo stesso.
		
		
		if (cmd_path)
			printf("cmd exists at path: %s\n", cmd_path);
		else
			printf("%s It is not a valid cmd\n", prova->segments->cmd);
		free_cached_path(cached_path);
		free(cmd_path);
		free_commandInfo(prova);
		}			

	}
		return 0;
}

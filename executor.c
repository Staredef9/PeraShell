#include "PeraShell.h"


char	*my_getenv(const char *name, char **envp)
{
	size_t len = strlen(name);
	for (int i = 0; i < len; i++){
		if(strncmp(envp[i], name, len) == 0 && envp[i][len] == '='){
			return envp[i] + len + 1;
		}
	}
	return NULL;
}

///////LE COSE CHE NON VANNO:
///SIZE TOBE DA METTERE UNA FLAG ANCHE PER LE OPZIONI 
///VANNO IMPLEMENTATI BENE I BUILTIN
///DEVO IMPLMENTARE LE STRUCT DI MODO CHE FUNZIONINO DA PASSARE A EXECVE PER BENE
///DEVO IMPLEMENTARE LA LOGICA DELLE PIPE MULTIPLE
///DEVO IMPLEMEMTARE LA PULIZIA GENERALE``




char *find_cmd_in_path(const char *command, char *cached_path, int numArguments)
{
	if (!cached_path){
		printf("there is no cached path\n");
		return NULL;
	}

	char 	*path_copy =  strdup(cached_path);
	char 	*dir = strtok(path_copy, ":");
	char 	*cmd_path = malloc(sizeof(char*) * 1024);
    	size_t 	size_tobe = 0;
	memset((cmd_path), '\0', 1024);
	
	while (dir != NULL) {
        //strcpy(cmd_path, dir);
        //strcat(cmd_path, "/");
        //strcat(cmd_path, command);

	if (strcmp("/System/Cryptexes/App/usr/bin", dir)== 0 || strcmp("/System", dir) == 0){
        dir = strtok(NULL, ":");
	}
	
	printf("Current dir: %s\n", dir);
	if (numArguments ==  0)
		size_tobe = strlen(dir) + strlen(command) + 1;
	else if (numArguments > 0)
		size_tobe = strlen(dir) + strlen(command) + 2;
		
	printf("dir length: %zu, command length: %zu, needed size: %zu\n", strlen(dir), strlen(command), size_tobe);
	snprintf(cmd_path, size_tobe, "%s/%s", dir, command);

        printf("Checking path: %s\n", cmd_path);
	
	//controlla se il path e' system o altre cartelle non accessibili

        if (access(cmd_path, X_OK) == 0) {
            printf("Command found: %s\n", cmd_path);
            free(path_copy);
            char *to_return = strdup(cmd_path);
	    free(cmd_path);
	    return (to_return);
        }

        perror("access");
        dir = strtok(NULL, ":");
    }
/*	while(dir != NULL){
		
		//strcpy(cmd_path, dir);
		printf("Checking path: %s\n", cmd_path);	
		if (access(cmd_path, X_OK) == 0){
			free(path_copy);
			printf("cmd path is: %s\n", cmd_path);
			return strdup(cmd_path);
		} else {
			perror("access");
			//printf("access not working\n");
		}
		dir = strtok(NULL, ":");
	}*/
	free(path_copy);
	printf("cmd not found\n");
	free(cmd_path);
	return NULL;
}

void	free_cached_path(char *cached_path)
{
	free(cached_path);
	cached_path = NULL;
	printf("cached path has been freed\n");
}

char	*init_cached_path(char **envp, char *cached_path)
{
	char *dummy = getenv("PATH");
	//printf("cached path found at %s", dummy);
	if (dummy){
		cached_path = strdup(dummy);
	//	printf("path has been copied %s\n", cached_path);
		return cached_path;
	}else
		return NULL;
}



int	execute_single_cmd(char *cmd_path,char *options,char **envp,  char **arguments, int *id, int *fd, int *exitStatus)
{
	pipe(fd);
			if (fd[0] == -1)
				return(0);
			*id = fork();
			if (*id == -1)
				return(2);
			if (*id == 0){
				//figlio fa cose
				execve(cmd_path, arguments, envp);
				printf("execve failed");
				exit(1);
			} else {
				waitpid(*id, exitStatus, 0);
				if(WIFEXITED(exitStatus)){
					int status = WEXITSTATUS(*exitStatus);
					printf("Child process exited with status %d\n", status);
				}
			}
	return 1;	
}

//TODO:
//crea e sostituisci nel main la gestione dgli argomenti del singolo comando, delle pipe multiple 
//e dei redirect 
//fare attenzione ai FREE
//chiudere ASAP





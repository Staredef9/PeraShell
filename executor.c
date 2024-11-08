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

//scrivere anche una che splitta la variabile path in base ai : e cerca le singole director

char *find_cmd_in_path(const char *command, char *cached_path)
{
	if (!cached_path){
		printf("there is no cached path\n");
		return NULL;
	}

	char *path_copy =  strdup(cached_path);
	char *dir = strtok(path_copy, ":");
	char cmd_path[1024];

	while(dir != NULL){
		snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir, command);
		
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
	}
	free(path_copy);
	printf("cmd not found\n");
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



int	execute_single_cmd(char *cmd, char *options, char *arguments)
{
	return 1;	
}

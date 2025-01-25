#ifndef PERA_SHELL_H
#define PERA_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define MAX_LINE 80
#define BUFFER 1000
#define MAX_ARGS 100


typedef struct {
	char *cmd;
} Command;


typedef struct {
	char 	**options;
	int	options_count;
} Options;

typedef struct {
	char 	**arguments;
	int	arguments_count;
} Arguments;

typedef struct {
	char 	*inputFile;
	char	*outputFile;
	int	append; //flag per distinguere >> da >
} IO_Redirection;

typedef struct {
	char	*pipeCommand;
	int	hasPipe;
} Pipe;

typedef struct {
	char		*cmd;
	char		**options;
	int		numOptions;
	char		**arguments;
	int		numArguments;

} SegmentInfo;

typedef struct {

	SegmentInfo	*segments;
	int		numSegments;
	IO_Redirection	ioRedirection;
	//Pipe pipeInfo;
	int 		isBackground;;

} CommandInfo;

typedef struct parseInfo
{
	char **args;
	//char *cmd;
	//char *options;
	//char *arguments;
	int  argument_count;
} parseInfo;


typedef struct historyTab{
	char **buffer;
} historyTab;


int		p_clear(char *buffer);
int		deallocParseInfo(parseInfo *parse);
int		p_history(historyTab *table, char *buffer, int *size, int *capacity);
parseInfo 	*parse(char *buffer);
CommandInfo	*parse_input(const char *input);


void		free_commandInfo(CommandInfo *cmdInfo);
void		print_cmd_info(CommandInfo *prova);
void		print_hist_table(historyTab *table);
void		free_hist_table(historyTab *table);




char		*my_getenv(const char *name, char **envp);

char		*find_cmd_in_path(const char *command, char *cached_path, int numArguments);
void		free_cached_path(char *cached_path);
char		*init_cached_path(char **envp, char *cached_path);

int	execute_single_cmd(char *cmd, char *options, char **envp, char **arguments, int *id, int *fd, int *exitStatus);
#endif

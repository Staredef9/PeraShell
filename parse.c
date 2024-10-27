#include "PeraShell.h"


/*
 * TODO:
 *	assicurarsi che funzioni la gestione dei token 
 *	procdere a implementare i builtin 
 *	procedere con la logica delle fork e dup per le pipe ecc
 *
 * */



CommandInfo *parse_input(const char *input){
	
	CommandInfo *cmdInfo = malloc(sizeof(CommandInfo));
	
	cmdInfo->segments = malloc(MAX_ARGS * sizeof(SegmentInfo));
	cmdInfo->numSegments = 0;
	cmdInfo->ioRedirection.inputFile = NULL;
	cmdInfo->ioRedirection.outputFile = NULL;
	cmdInfo->ioRedirection.append = 0;
	cmdInfo->isBackground = 0;

	
	char *input_copy = strdup(input);
	char *token = strtok(input_copy, " ");		

	SegmentInfo *currentSegment = &cmdInfo->segments[cmdInfo->numSegments];
	if((currentSegment->options = malloc(MAX_ARGS * sizeof(char*))) == NULL){
			printf("option allocation error\n");
			exit(1);
		};
	if((currentSegment->arguments = malloc(MAX_ARGS * sizeof(char*))) == NULL){
			printf("arguments allocation error\n");
			exit(1);
		};
		
	currentSegment->numOptions = 0;
	currentSegment->numArguments = 0;
		
	int isNewSegment = 1;
	
	while(token != NULL){

		if(strcmp(token, "|") == 0){
		
			cmdInfo->numSegments++;
			currentSegment = &cmdInfo->segments[cmdInfo->numSegments];
			currentSegment->options = malloc(MAX_ARGS * sizeof(char*));
			currentSegment->arguments = malloc(MAX_ARGS * sizeof(char*));
			currentSegment->numOptions = 0;
			currentSegment->numArguments = 0;
			isNewSegment = 1;
		}
		else if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0){
			cmdInfo->ioRedirection.append = (strcmp(token, ">>") == 0);
			token = strtok(NULL, " "); //parsa e prendi filename
			if (token != NULL){
				cmdInfo->ioRedirection.outputFile = strdup(token);
			}
		} else if (strcmp(token, "<") == 0) {
			token = strtok(NULL, " ");
			if (token != NULL){
				cmdInfo->ioRedirection.inputFile = strdup(token);
			}
		} else if (strcmp(token, "&") == 0){
			cmdInfo->isBackground = 1;
		}  else {
			if(isNewSegment){
				currentSegment->cmd = strdup(token);
				isNewSegment = 0;
			} else if (token[0] == '-'){
				currentSegment->options[currentSegment->numOptions++] = strdup(token);
			} else{
				currentSegment->arguments[currentSegment->numArguments++] = strdup(token);
			}

		}
		token = strtok(NULL, " ");
	}
	cmdInfo->numSegments++;
	//printf("cmdInfo is parsing %d segments\n", cmdInfo->numSegments);
	//printf("argument of segment is %s\n", cmdInfo->segments->arguments[1]);
	free(input_copy);
	return cmdInfo;
}
	
void	free_commandInfo(CommandInfo *cmdInfo){

	if (cmdInfo == NULL)
		return;

	for (int i = 0; i < cmdInfo->numSegments; i++){
	
		SegmentInfo *segment = &cmdInfo->segments[i];

		free(segment->cmd);
		
		for (int j = 0; j < segment->numOptions; j++)
			free(segment->options[j]);
		free(segment->options);
		
		for (int j = 0; j < segment->numArguments; j++)
			free(segment->arguments[j]);
		free(segment->arguments);
	}
	free(cmdInfo->segments);

	if(cmdInfo->ioRedirection.inputFile)
	{
		free(cmdInfo->ioRedirection.inputFile);
	}
	if(cmdInfo->ioRedirection.outputFile)
	{
		free(cmdInfo->ioRedirection.outputFile);
	}
	
	//free(cmdInfo->ioRedirection);
	free(cmdInfo);
}

void	print_cmd_info(CommandInfo *prova)
{
	for (int i = 0; i < prova->numSegments; i++){
	
		printf("cmd %d is %s\n",i , prova->segments[i].cmd);
		
	printf("Options number = %d\n", prova->segments[i].numOptions);
		
	if(prova->segments[i].numOptions > 0){
		for(int j = 0; j < prova->segments[i].numOptions; j++)
				printf("Options are:%s\n", prova->segments[i].options[j]);
	}
	printf("Arguments number = %d\n", prova->segments[i].numArguments);
		
	if(prova->segments[i].numArguments > 0)
	{
		for(int j = 0; j < prova->segments[i].numArguments; j++)
			printf("Arguments are:%s\n", prova->segments[i].arguments[j]);
	}
	printf("Total number of segments: %d\n", prova->numSegments);
	printf("Total number of pipes: %d\n", prova->numSegments -1);

	//free_commandInfo(prova);	
	}
}







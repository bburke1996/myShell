#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Test */

/* Function Declarations */
void myShell_cd(int argc, char *argv[]);
void myShell_echo(int argc, char *argv[]);
void myShell_help(int argc, char *argv[]);
int parseCommandLine(char *line, char *argv[], int maxArguments);
void myShellExecute(int argc, char *argv[]);

int main() {
	int i;
	while (1) {
		char *path;
		path = (char *) malloc(sizeof(char) * 1024);
		if (path == NULL) {
			fprintf(stderr, "Error allocating 1024 bytes using malloc in the main function.\n");
			exit(1);
		}
		path = getcwd(path, 1024);
		if (path == NULL) {
			fprintf(stderr, "Error using getcwd in the main function\n");
			exit(1);
		}
		printf("%s> ", path);
		//printf("prompt> ");
		
		/* Getting the command from stdin */

		/* line is a char pointer that will point to the string of characters that are given as input on the command line */
		char *line = NULL;
		/* maxInput is the maximum number of characters that can be in one line of input */
		size_t maxInput = 1024;
		/* Allocating line on the heap using malloc */
		line = (char *) malloc(sizeof(char) * maxInput);
		if (line == (char *) NULL) {
			fprintf(stderr, "Error allocating %d bytes using malloc in main function.\n", (int) maxInput);
			exit(1);
		}
		/* inputSize is the number of characters that are in the line of input. It is the return value of getline */
		ssize_t inputSize = getline(&line, &maxInput, stdin);
		if (inputSize == -1) {
			fprintf(stderr, "Error using getline in main function.\n");
			exit(1);
		}	

		/* Parsing the command and its arguments */
		
		/* For now, the shell will only be able to handle 10 arguments on each line */
		int maxArguments = 10;
		/* argv will be an array of size maxArguments + 1. After parsing, argv[0] will be the program name, and the rest of the elements of argv will be the arguments */
		char *argv[maxArguments + 1];
		/* After parsing, argc will contain the number of arguments (including the program name) on the command line */
		int argc;
		argc = parseCommandLine(line, argv, maxArguments);

		/* Printing line char array for debugging purposes */
		/*
		for (i = 0; i < argc; i++) {
			if (argv[i] != NULL) 
				printf("argv[%d] = %s\n", i, argv[i]);
		} */

		/* Call myShellExecute function to execute the command and arguments that were just parsed. */
		myShellExecute(argc, argv);
	}
}

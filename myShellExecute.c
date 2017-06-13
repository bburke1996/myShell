#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NUM_SHORT_PATH_COMMANDS 31
#define NUM_LONG_PATH_COMMANDS 38

/* shortPathCommands is an array of 31 strings. Each string in shortPathCommands corresponds to the name of a command that can be executed by "exec-ing" by using the path 
 * "/bin/<command>". 
 */
char *shortPathCommands[NUM_SHORT_PATH_COMMANDS] = {"cp", "bash", "cat", "chmod", "csh", "date", "dd", "df", "domainname", "ed", "expr", "hostname", "ksh", "launchctl", "link", "ln", "ls", "mkdir", "mv", "pax", "ps", "rm", "rmdir", "sh", "sleep", "stty", "sync", "tcsh", "unlink", "wait4path", "zsh"};

/* longPathCommands is an array of 38 strings. Each string in longPathCommands corresponds to the name of a command that can be executed by "exec-ing" by using the path
 * "/usr/bin/<command>"
 */
char *longPathCommands[NUM_LONG_PATH_COMMANDS] = {"c++", "cc", "c89", "c99", "clear", "calendar", "cal", "caffeinate", "compress", "curl", "java", "javac", "javadoc", "javah", "javap", "install", "host", "hexdump", "gzip", "gunzip", "git", "getopt", "emacs", "make", "man", "objdump", "open", "say", "python", "ssh", "tar", "uncompress", "zip", "unzip", "xxd", "wc", "vi", "vim"};

/* myShell_cd is a function that represents the builtin "cd" command. The first parameter, int argc, holds the number of arguments to the "cd" command (including the command
 * name itself). The second parameter, char *argv[], is an array of char pointers that each point to one of the arguments to the "cd" command. So, argv[0] == "cd". 
 * If argc is less than 1 or greater than 2, then an error is printed to the screen indicating that the number of arguments to "cd" was incorrect. If argc == 1, then the 
 * current directory of the shell process is changed to the root directory. Otherwise, arc == 2, and the current directory is changed to the directory indicated by argv[1], 
 * which must be in the current directory. myShell_cd() has no return value. 
 */
void myShell_cd(int argc, char *argv[]) {
	if (argc < 1 || argc > 2) {
		fprintf(stderr, "Error: Incorrect number of command line arguments to \"cd\" command\n");
	} else if (argc == 1) {
		/* Use chdir() to change the current directory to the root directory. */
	} else {
		if (chdir(argv[1]) != 0) {
			fprintf(stderr, "Error with chdir function in myShell_cd function\n");
		}
	}
}

void myShell_echo(int argc, char *argv[]) {
	int i;
	/* Verify that echo command was given the correct number of command line arguments */
	if (argc < 2) {
		printf("The echo command takes 2 or more arguments. The first argument is \"echo\", the name of the command. The rest of the commands are strings to be printed to stdout.\n");
		return;
	}
	for (i = 1; i < argc; i++) 
		fprintf(stdout, "%s ", argv[i]);
	fprintf(stdout, "\n");
}

/* myShell_help is a function that represents the builtin "help" command. The first parameter, int argc, holds the number of arguments to the "help" command (including the
 * command name itself). The second parameter, char *argv[], is an array of char pointers that each point to one of the arguments to the "help" command. So, argv[0] == "help".
 * This function simply prints two lines of output to the screen that describe this shell program. myShell_help() has no return value.
 */
void myShell_help(int argc, char *argv[]) {
	printf("This is Brian Burke's myShell program. The builtin functions for this shell are cd, echo, exit, and help.\nUse man pages to learn about how to use any other UNIX commands\n");
}

/* createShortPath() is a function that modifies argv[0] such that it is preceeded by "/bin/". This is necessary to run some commands that are not builtin to myShell. The first 
 * parameter, int argc, holds the number of arguments to the command (including the command name itself). The second parameter, char *argv[], is an array of char pointers that
 * each point to one of the arguments to the command. So, argv[0] points to the command name. For example, if argv[0] points to "ls" at the beginning of the function, then
 * argv[0] will point to "/bin/ls" at the end of the function. createShortPath() has no return value.
 */
void createShortPath(int argc, char *argv[]) {
	char *command, *path;
	int i, j;
	command = malloc(sizeof(char) * (strlen(argv[0]) + 1));
	strcpy(command, argv[0]);
	path = "/bin/";
	free(argv[0]);
	argv[0] = malloc(sizeof(char) * (strlen(command) + strlen(path) + 1));
	strncpy(argv[0], path, strlen(path));
	j = 0;
	for (i = strlen(path); i < strlen(path) + strlen(command); i++) {
		argv[0][i] = command[j];
		j++;
	}
	argv[0][i] = '\0';			
}

/* createLongPath() is a function that modifies argv[0] such that it is preceeded by "/usr/bin/". This is necessary to run some commands that are not builtin to myShell. The 
 * first parameter, int argc, holds the number of arguments to the command (including the command name itself). The second parameter, char *argv[], is an array of char pointers
 * that each point to one of the arguments to the command. So, argv[0] points to the command name. For example, if argv[0] points to "make" at the beginning of the function, 
 * then argv[0] will point to "/usr/bin/make" at the end of the function. createLongPath() has no return value.
 */
void createLongPath(int argc, char *argv[]) {
	char *command, *path;
	int i, j;
	command = malloc(sizeof(char) * (strlen(argv[0]) + 1));
	strcpy(command, argv[0]);
	path = "/usr/bin/";
	free(argv[0]);
	argv[0] = malloc(sizeof(char) * (strlen(command) + strlen(path) + 1));
	strncpy(argv[0], path, strlen(path));
	j = 0;
	for (i = strlen(path); i < strlen(path) + strlen(command); i++) {
		argv[0][i] = command[j];
		j++;
	}
	argv[0][i] = '\0';
}

/* isInShortPathCommands is a function that returns 1 (true) iff the given string is in the global shortPathCommands array and returns 0 (false) otherwise. The first and only 
 * parameter, char *str, is the string to be checked. 
 */
int isInShortPathCommands(char *str) {
	int i;
	for (i = 0; i < NUM_SHORT_PATH_COMMANDS; i++) {
		if (strcmp(str, shortPathCommands[i]) == 0) return 1;
	}
	return 0;
}

/* isInLongPathCommands is a function that returns 1 (true) iff the given string is in the global longPathCommands array and returns 0 (false) otherwise. The first and only 
 * parameter, char *str, is the string to be checked. 
 */
int isInLongPathCommands(char *str) {
	int i;
	for (i = 0; i < NUM_LONG_PATH_COMMANDS; i++) {
		if (strcmp(str, longPathCommands[i]) == 0) return 1;
	}
	return 0;
}
void myShellExecute(int argc, char *argv[]) {
	/* First, check if argv[0] is any of the builtin shell functions (cd, echo, exit, help). */
	if (strcmp(argv[0], "cd") == 0) 
		myShell_cd(argc, argv);
	else if (strcmp(argv[0], "echo") == 0) 
		myShell_echo(argc, argv); 
	else if (strcmp(argv[0], "exit") == 0) 
		exit(0);
	else if (strcmp(argv[0], "help") == 0) 
		myShell_help(argc, argv);
	else {
		pid_t pid, wpid;
		int status;
		int i;
		pid = fork();
		if (pid < 0) {							/* fork() Error */
			fprintf(stderr, "Error using fork()\n");
			exit(1);
		} else if (pid == 0) {						/* Child */
			argv[argc] = NULL;

			/* If the command is in the shortPathCommands array, then call createShortPath() function to set argv[0] to the correct path */
			if (isInShortPathCommands(argv[0])) 
				createShortPath(argc, argv);

			/* Else, if the command is in the longPathCommands array, then call createlongPath() function to set argv[0] to the correct path */
			else if (isInLongPathCommands(argv[0])) 
				createLongPath(argc, argv);

			/* Otherwise, this command is not supported by myShell */
			else {
				printf("The %s command is not supported by myShell\n", argv[0]);
				return;
			}

			/* Printing out argv for debugging purposes */
			/*
			for (i = 0; i < argc; i++) {
				if (argv[i] != NULL) 
					printf("argv[%d] = %s\n", i, argv[i]);
			}
			if (argv[i] == NULL) printf("argv[%d] = NULL\n", i);
			*/

			/* Printing out argv[0] for debugging purposes */
			/*
			printf("\nPath created\n\n");
			for (i = 0; i < strlen(argv[0]); i++) 
				printf("argv[0][%d] = %c\n", i, argv[0][i]);
			*/

			/* exec the command */
			execvp(argv[0], argv);
			/* If execvp ever returns, then there was an error with the execvp function call */
			perror("Error with execvp");
			exit(1);
		} else {							/* Parent */
			/* Wait for the child to finish */
			do {
				wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && ! WIFSIGNALED(status));
		}
	}
}

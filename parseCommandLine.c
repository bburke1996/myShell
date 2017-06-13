#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* For now, each argument will have a maximum number of 256 characters */
#define MAX_ARG_SIZE 256

/* onlySpaces is a function that takes a string as a parameter and returns 1 if the string only has spaces and returns 0 otherwise. The string to be checked is the first and
 * only parameter, char *str. 
 */
int onlySpaces(char *str) {
	int i;
	for (i = 0; i < strlen(str); i++) 
		if (!isspace(str[i])) return 0;
	return 1;
}

/* removeIthElement is a function that removes the ith element of an array by deleting the element and then shifting each element to the right of the deleted element to the 
 * left by one index.
 */
void removeIthElement(int argc, char *argv[], int i) {
	/* This for loop shifts all of the elements to the right of the element to be deleted to the left by one. */
	for (i = i + 1; i < argc; i++)
		strcpy(argv[i], argv[i + 1]);
	
	/* free the memory that was allocated for the last index of argc. Since one element was deleted and everything to its right was shifted to the left, there is an unused
	 * index at the end of argv. */
	free(argv[argc - 1]);
}

/* stripWhiteSpace is a function that strips the leading and trailing whitespace of a string. The first parameter, char *argv[], is an array of strings. The second parameter, 
 * int i, indicates the index of argv that is to be striped of its leading and trailing whitespace. 
 */
void stripWhiteSpace(char *argv[], int i) {
	int j, k;
	char currentChar;
	
	/* This for loop strips the leading whitespace from argv[i] */
	for (j = 0; j < strlen(argv[i]); j++) {
		currentChar = argv[i][j];
		/* If currentChar isn't a space, then break out of this loop */	
		if (!isspace(currentChar)) break;
	}

	/* Let's say that after the above for loop breaks, numSpaces is equal to j. Now, every character (starting from the character at index numSpaces) must be shifted to the
	 * left numSpaces times. This strips the leading whitespace */
	for (k = 0; j < strlen(argv[i]); j++, k++)
		argv[i][k] = argv[i][j];

	/* Append the shifted string with a '\0' */
	argv[i][k] = '\0';
		
	/* This for loop strips the trailing whitespace from argv[i] */
	for (j = strlen(argv[i]) - 1; j >= 0; j--) {
		currentChar = argv[i][j];
		/* If currentChar isn't a space, then break. Otherwise, continue. */
		if (!isspace(currentChar)) break;
	}
	
	/* The for loop broke when j was equal to the last index in argv[i] that isn't a space. So, setting the next character to '\0' will strip argv[i] of all of its trailing
	 * whitespace. */
	argv[i][j + 1] = '\0';
}

/* stripSpaces is a function that removes the elements of argv that are only spaces and strips all other elements of argv of their leading and trailing whitespace. The first
 * parameter of stripSpaces, int argc, is the number of elements in the argv array. The second parameter, char *argv[], is the array of char pointers. This function returns
 * the new number of elements of argv after the elements that are only whitespace have been removed. 
 */
int stripSpaces(int argc, char *argv[]) {
	int i;
	
	/* First, go thru argv array and delete any elements that are only spaces. */
	for (i = 0; i < argc; i++) {
		// If argv[i] is only spaces, then delete it from argv and move all of the elements to its right one index to the left.
		if (onlySpaces(argv[i])) {
			removeIthElement(argc, argv, i);
			argc--;
			i--;
		}
	}

	/* Now, go thru argv array and strip the leading and trailing whitespace from each element */
	for (i = 0; i < argc; i++)
		stripWhiteSpace(argv, i);
	
	return argc;
}

int parseCommandLine(char *line, char *argv[], int maxArguments) {
	int currentArg = 0, bufferSize = 0, i;
	int maxArgumentSize = MAX_ARG_SIZE;
	char *buffer;
	char currentChar;
	/* Allocate buffer on the heap so that it can be put into an array that is used by the calling function */
	buffer = (char *) malloc(sizeof(char) * maxArgumentSize);
	if (buffer == (char *) NULL) {
		fprintf(stderr, "Error allocating %d bytes using malloc in parseCommandLine function.\n", maxArgumentSize);
		exit(1);
	}
	for (i = 0; i < strlen(line); i++) {
		currentChar = line[i];
		// If currentChar is a space, then add buffer to argv and reset the buffer
		if (currentChar == ' ') {
			/* This if statement will allow for two arguments to be separated by multiple spaces without a change in the input line's interpretation */
			if (bufferSize == 0) continue;
			argv[currentArg] = buffer;
			currentArg++;
			if (currentArg > maxArguments) {
				fprintf(stderr, "Error: Too many arguments on the command line\n");
				exit(1);
			}
			/* Allocate another buffer on the heap for the next argument */
			buffer = (char *) malloc(sizeof(char) * maxArgumentSize);
			if (buffer == (char *) NULL) {
				fprintf(stderr, "Error allocating %d bytes using malloc in parseCommandLine function.\n", maxArgumentSize);
				exit(1);
			}
			bufferSize = 0;
		}

		/* If currentChar is a newline character, then break out of the for loop */
		else if (currentChar == '\n')
			break;

		// If currentChar isn't a space, then add currentChar to the buffer and increment bufferSize
		else {
			buffer[bufferSize] = currentChar;
			bufferSize++;
		}
	}

	argv[currentArg] = buffer;
	currentArg++;
	
	/* Call stripSpaces() function to strip leading and trailing whitespace from each element of argv and to delete any elements of argv that are only spaces. */
	currentArg = stripSpaces(currentArg, argv);

	/* Return currentArg, which is the next availale index of argv (and, more importantly, the number elements of argv) */
	return currentArg;
}

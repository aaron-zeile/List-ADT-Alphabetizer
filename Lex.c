/***************************************
**** Name: Aaron Zeile *****************
**** CruzID: 2091251 *******************
**** Assignment: pa1 *******************
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]) {
	// if not 2 command line arguments
	if (argc != 3) {
		fprintf(stderr, "Usage error. Must have exactly 2 command line arguments.\n");
		exit(EXIT_FAILURE);
	}
	
// CREATE ARRAY AND STORE LINES ------------------------------------------------------

	// declare necessary variables
	int line_count;
	char line[MAX_LEN];

	// open files for reading and writing
	FILE *in = fopen(argv[1], "r");
	if (!in) {
		printf("Couldn't open input file.\n");
		exit(1);
	}

	FILE *out = fopen(argv[2], "w");
	if (!out) {
		printf("Couldn't open output file.\n");
		exit(1);
	}

	// count lines in file
	line_count = 0;
	while (fgets(line, MAX_LEN, in)) {
		line_count++;
	}
	
	// allocate array of strings
	char **strings = (char **)calloc(line_count, sizeof(char*));
	if (!strings) {
		printf("Failed to allocate memory for array.\n");
		fclose(in);
		fclose(out);
		exit(1);
	}

	// go back to top of file	
	rewind(in);
	// declare iterator
	int i = 0;
	// fill array of strings
	while (fgets(line, MAX_LEN, in)) {
		// allocate memory for element
		strings[i] = (char *)calloc(strlen(line) + 1, sizeof(char));
		// if allocation fails
		if (strings[i] == NULL) {
			printf("Failed to allocate memory for array element.\n");
			fclose(in);
			fclose(out);
			exit(1);
		}
		// copy line into array
		strcpy(strings[i], line);
		i++;
	}
	
	// close input file
	fclose(in);

// CREATE LIST AND SORT THE STRINGS-----------------------------------------------------

	// create new list
	List A = newList();

	// append first element, since it is automatically considered sorted
	append(A, 0);
	// iterate over array and list, filling list
	for (int i = 1; i < line_count; i++) {
		// start at front list
		moveFront(A);
		char *current = strings[i];
		// iterate through list
		while (index(A) != -1) {
			// if current string in array goes
			// before current string in list
			if (strcmp(current, strings[get(A)]) < 0) {
				insertBefore(A, i);
				break;
			}
			moveNext(A);
		}
		// if we reached the end of the list,
		// append the current string
		if (index(A) == -1) {
			append(A, i);
		}
	}


// PRINT THE SORTED LIST INTO OUTPUT FILE------------------------------------------------	

	// start from front of list
	moveFront(A);

	// iterate through list, printing each
	// element to output file
	while (index(A) != -1) {
		fprintf(out, "%s", strings[get(A)]);
		moveNext(A);
	}

// FREE MEMORY AND CLOSE FILES----------------------------------------------------------

	// free list
	freeList(&A);

	// free array
	for (int i = 0; i < line_count; i++) {
		free(strings[i]);
	}
	free(strings);
	
	// close output file
	fclose(out);

 return 0;
}

# INTRODUCTION
For this project, I built an operable List ADT using a doubly linked list. This List ADT is then used to alphabetize words read in from an input file and printed into a separate output file.

# List.h
Header file for the list ADT. Contains all of the necessary function prototypes and typedefs. Also keeps the object members separate for privacy.

# List.c
Contains the bodies of every function for the List ADT and the struct for the nodes to be utilized in the list.

# Lex.c
Main function of the project. Loads buffers from input file into an array, puts the indices of these items into the list (in lexicographic order), and prints the ordered list of strings into an output file.

# Makefile
Used to quickly make the necessary files for running the program. Mostly provided code with slight alterations.

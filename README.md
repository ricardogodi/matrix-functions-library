# Matrix Manipulation and String Utility Library

## Overview
This project develops a comprehensive library in C for manipulating matrices and processing strings. The library offers dynamic memory management for matrices, various transformations, and string manipulation functions.

## Files Included
- **main.c**: Main source file that demonstrates the usage of matrix and string functions.
- **prog2.h**: Header file with declarations and specifications for all functions.
- **Makefile**: Simplifies compilation and cleaning up of object files and the executable.

## Matrix Functions
- **alloc_square_mtx(int n)**: Allocates a nxn matrix of characters.
- **free_square_mtx(char** m, int n)**: Deallocates memory allocated for the matrix.
- **pop_mtx_alpha(char** m, int n)**: Fills the matrix with random lowercase alphabets.
- **display_mtx(char** m, int n)**: Prints the matrix to the standard output.
- **swap_rows(char** m, int n, int r1, int r2)**: Swaps two specified rows in the matrix.
- **swap_cols(char** m, int n, int c1, int c2)**: Swaps two specified columns in the matrix.
- **rotate_right(char** m, int n)**: Rotates the matrix 90 degrees clockwise.
- **floating_boulders(char** m, int n, int nb)**: Randomly places 'boulders' represented by '#' in the matrix.
- **mountains(char** m, int n)**: Generates a random 'landscape' in the matrix.
- **sink(char** m, int n)**: Shifts all rows down by one, adding a row of 'air' at the top.
- **gravity(char** m, int n)**: Applies gravity, making all non-air elements fall to the bottom.

## String Functions
- **str_trim(char* s)**: Removes leading and trailing whitespace from the string.
- **str_search(char* s, char* pattern)**: Searches for a pattern in a string and returns the starting index of the first match.

## Compilation and Execution
To compile the program, use the provided Makefile:
```bash
make
```

To run the compiled program:
```bash
./program
```
